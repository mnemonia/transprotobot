import logging
from path_planner import PathPlanner
from throttle_control import ThrottleControl
from steering_control import SteeringControl
from top_level_control import TopLevelControl

class PlanningAndControlLayer():
    LOG = logging.getLogger('PlanningAndControlLayer')

    def __init__(self, gsl, sil, vil):
        self.LOG.info('init')
        self._sil = sil
        self.tc = ThrottleControl(gsl)
        self.sc = SteeringControl(gsl)
        self.tlc = TopLevelControl(gsl, sil, self.tc, self.sc)
        self.pp = PathPlanner(gsl, sil, vil, self.tc, self.sc)

    def on(self):
        self.LOG.info('on')
        self.tc.on()
        self.sc.on()
        self.tlc.on()
        self.pp.on()

    def tick(self):
        if (self._sil.gps()._rc_enable == 1):
            self.tlc.tick()
        else:
            self.pp.tick()
