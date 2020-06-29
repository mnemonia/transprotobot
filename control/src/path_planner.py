import logging

class PathPlanner():
    LOG = logging.getLogger('PathPlanner')

    def __init__(self, gsl, tc, sc):
        self._gsl = gsl
        self._tc = tc
        self._sc = sc

    def on(self):
        self.LOG.info('on')
        self._sc.angle(0)
        self._tc.velocity(0.5)

