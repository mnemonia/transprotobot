import logging
import numpy as np
from sensor_interface_layer import GpsMath
from stanley_controller import State, StandleyController

class PathPlanner():
    LOG = logging.getLogger('PathPlanner')

    def __init__(self, gsl, sil, vil, tc, sc):
        self._gsl = gsl
        self._sil = sil
        self._vil = vil
        self._tc = tc
        self._sc = sc
        self._lastTimestamp = 0.0
        self._toggle = False
        self.gpsMath = GpsMath()
        self._state = None
        self._controller = None



    def on(self):
        self.LOG.info('on')
        self._sc.angle(0)
        self._tc.stop()
        self._tc.velocity(0)
        self._tc.fwd()
        self._tc.velocity(0.0)
        self._sc.angle(0.8)
        # Initial state
        pt = self.gpsMath.locationToPoint(self._sil.gps()._latitude,
                                          self._sil.gps()._longitude,
                                          self._sil.gps()._altitude)
        self._state = State(x=pt["x"],
                            y=pt["y"],
                            yaw=np.radians(self._sil.gps()._heading),
                            v=0.0)
        self._controller = StandleyController(self._state)

    def tick(self):
        self.LOG.info('tick {}'.format(self._controller.isFinished()))
        if self._controller.isFinished():
            self._tc.stop()
        else:
            pt = self.gpsMath.locationToPoint(self._sil.gps()._latitude,
                                              self._sil.gps()._longitude,
                                              self._sil.gps()._altitude)
            self._state.x = pt["x"]
            self._state.y = pt["y"]
            self._state.yaw = np.deg2rad(self._sil.gps()._heading)
            self._controller.tick()
            self._tc.velocity(self._state.v)
            self._sc.angle(self._state.yaw)
