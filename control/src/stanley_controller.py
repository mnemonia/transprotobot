"""

Path tracking simulation with Stanley steering control and PID speed control.

author: Atsushi Sakai (@Atsushi_twi)

Ref:
    - [Stanley: The robot that won the DARPA grand challenge](http://isl.ecst.csuchico.edu/DOCS/darpa2005/DARPA%202005%20Stanley.pdf)
    - [Autonomous Automobile Path Tracking](https://www.ri.cmu.edu/pub_files/2009/2/Automatic_Steering_Methods_for_Autonomous_Automobile_Path_Tracking.pdf)

"""
import logging
import numpy as np
#import matplotlib.pyplot as plt
import cubic_spline_planner
from sensor_interface_layer import GpsMath

class State(object):
    LOG = logging.getLogger('StanleyState')
    """
    Class representing the state of a vehicle.

    :param x: (float) x-coordinate
    :param y: (float) y-coordinate
    :param yaw: (float) yaw angle
    :param v: (float) speed
    """

    def __init__(self, x=0.0, y=0.0, yaw=0.0, v=0.0):
        """Instantiate the object."""
        super(State, self).__init__()
        self.x = x
        self.y = y
        self.yaw = yaw
        self.v = v
        self.max_steer = np.radians(30.0)  # [rad] max steering angle
        self.L = 0.29
        self.dt = 0.1

    def normalize_angle(self, angle):
        """
        Normalize an angle to [-pi, pi].

        :param angle: (float)
        :return: (float) Angle in radian in [-pi, pi]
        """
        while angle > np.pi:
            angle -= 2.0 * np.pi

        while angle < -np.pi:
            angle += 2.0 * np.pi

        return angle

    def update(self, acceleration, delta):
        """
        Update the state of the vehicle.

        Stanley Control uses bicycle model.

        :param acceleration: (float) Acceleration
        :param delta: (float) Steering
        """
        delta = np.clip(delta, -self.max_steer, self.max_steer)

        self.x += self.v * np.cos(self.yaw) * self.dt
        self.y += self.v * np.sin(self.yaw) * self.dt
        self.yaw += self.v / self.L * np.tan(delta) * self.dt
        self.yaw = self.normalize_angle(self.yaw)
        self.v += acceleration * self.dt
        self.LOG.info("velocity: {}, angle: {}°".format(self.v, np.rad2deg(self.yaw)))

class StandleyController():
    LOG = logging.getLogger('StandleyController')

    def __init__(self, initialState):
        self.k = 0.5  # control gain
        self.Kp = 1.0  # speed proportional gain
        self.dt = 0.1  # [s] time difference
        self.L = 0.29  # [m] Wheel base of vehicle
        self.max_steer = np.radians(30.0)  # [rad] max steering angle
        self.show_animation = True
        gpsMath = GpsMath()

        ax = [4300738.591950053, 4300735.762529756, 4300731.881422988, 4300725.061867644, 4300716.428532064]
        ay = [687530.1153441871, 687527.1996543248, 687525.1935662497, 687519.4075912425, 687510.02154688]
        ax = list(map(lambda x: gpsMath.locationToPoint(x, 9.083533, 480)["x"], [47.031944, 47.031745, 47.031807, 47.031965, 47.031944]))
        ay = list(map(lambda x: gpsMath.locationToPoint(47.031944, x, 480)["y"], [9.083533, 9.083629, 9.083816, 9.083692, 9.083533]))
        #ax = [4300796.650611158, 4300812.637012742, 4300812.637012742, 4300794.963600908, 4300796.650611158]
        #ay = [687608.2953105057, 687615.5013634935, 687615.5013634935, 687620.2303347178, 687608.2953105057]
        print(ax)
        print(ay)

        ds = 0.1

        self.cx, self.cy, self.cyaw, self.ck, self.s = cubic_spline_planner.calc_spline_course(
            ax, ay, ds=ds)

        self.target_speed = 3.0 / 3.6  # [m/s]

        self.max_simulation_time = 100.0

        # Initial state
        self.state = initialState

        self.last_idx = len(self.cx) - 1
        self.target_idx, _ = self.calc_target_index(self.state, self.cx, self.cy)
        self.time = 0.0
        self.x = [self.state.x]
        self.y = [self.state.y]
        self.yaw = [self.state.yaw]
        self.v = [self.state.v]
        self.t = [0.0]
        self.LOG.info("on {}/{}".format(self.x, self.y))

    def tick(self):
        ai = self.pid_control(self.target_speed, self.state.v)
        di, target_idx = self.stanley_control(self.state, self.cx, self.cy, self.cyaw, self.target_idx)
        self.state.update(ai, di)

        self.time += self.dt

        self.x.append(self.state.x)
        self.y.append(self.state.y)
        self.yaw.append(self.state.yaw)
        self.v.append(self.state.v)
        self.t.append(self.time)

        self.LOG.info("cx: {}".format(self.x))

        """ if self.show_animation:  # pragma: no cover
            plt.cla()
            # for stopping simulation with the esc key.
            plt.gcf().canvas.mpl_connect('key_release_event',
                                         lambda event: [exit(0) if event.key == 'escape' else None])
            plt.plot(self.cx, self.cy, ".r", label="course")
            #plt.plot(self.x, self.y, "-b", label="trajectory")
            #plt.plot(self.cx[target_idx], self.cy[target_idx], "xg", label="target")
            plt.axis("equal")
            plt.grid(True)
            plt.title("Speed[km/h]:" + str(self.state.v * 3.6)[:4] + ", Angle[rad]:" + str(np.rad2deg(self.state.yaw))[:4])
            plt.pause(0.1) """

    def isFinished(self):
        return self.target_idx >= self.last_idx

    def pid_control(self, target, current):
        """
        Proportional control for the speed.

        :param target: (float)
        :param current: (float)
        :return: (float)
        """
        return self.Kp * (target - current)


    def stanley_control(self, state, cx, cy, cyaw, last_target_idx):
        """
        Stanley steering control.

        :param state: (State object)
        :param cx: ([float])
        :param cy: ([float])
        :param cyaw: ([float])
        :param last_target_idx: (int)
        :return: (float, int)
        """
        current_target_idx, error_front_axle = self.calc_target_index(state, cx, cy)

        if last_target_idx >= current_target_idx:
            current_target_idx = last_target_idx

        # theta_e corrects the heading error
        theta_e = self.normalize_angle(cyaw[current_target_idx] - state.yaw)
        # theta_d corrects the cross track error
        theta_d = np.arctan2(self.k * error_front_axle, state.v)
        # Steering control
        delta = theta_e + theta_d

        return delta, current_target_idx


    def normalize_angle(self, angle):
        """
        Normalize an angle to [-pi, pi].

        :param angle: (float)
        :return: (float) Angle in radian in [-pi, pi]
        """
        while angle > np.pi:
            angle -= 2.0 * np.pi

        while angle < -np.pi:
            angle += 2.0 * np.pi

        return angle


    def calc_target_index(self, state, cx, cy):
        """
        Compute index in the trajectory list of the target.

        :param state: (State object)
        :param cx: [float]
        :param cy: [float]
        :return: (int, float)
        """
        # Calc front axle position
        fx = state.x + self.L * np.cos(state.yaw)
        fy = state.y + self.L * np.sin(state.yaw)

        # Search nearest point index
        dx = [fx - icx for icx in cx]
        dy = [fy - icy for icy in cy]
        d = np.hypot(dx, dy)
        target_idx = np.argmin(d)

        # Project RMS error onto front axle vector
        front_axle_vec = [-np.cos(state.yaw + np.pi / 2),
                          -np.sin(state.yaw + np.pi / 2)]
        error_front_axle = np.dot([dx[target_idx], dy[target_idx]], front_axle_vec)

        return target_idx, error_front_axle
