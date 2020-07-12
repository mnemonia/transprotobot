import logging
from path_planner import PathPlanner
from throttle_control import ThrottleControl
from steering_control import SteeringControl

class PlanningAndControlLayer():
    LOG = logging.getLogger('PlanningAndControlLayer')

    def __init__(self, gsl, sil, vil):
        self.LOG.info('init')
        self.tc = ThrottleControl(gsl)
        self.sc = SteeringControl(gsl)
        self.pp = PathPlanner(gsl, sil, vil, self.tc, self.sc)

    def on(self):
        self.LOG.info('on')
        self.tc.on()
        self.sc.on()
        self.pp.on()

    def tick(self):
        self.pp.tick()
