import logging

class PathPlanner():
    LOG = logging.getLogger('PathPlanner')

    def __init__(self, gsl, sil, vil, tc, sc):
        self._gsl = gsl
        self._sil = sil
        self._vil = vil
        self._tc = tc
        self._sc = sc

    def on(self):
        self.LOG.info('on')
        self._sc.angle(0)
        self._tc.stop()
        self._tc.velocity(0)

    def tick(self):
        self.LOG.info('latitude {}'.format(self._sil.gps()._latitude))
        self.LOG.info('longitude {}'.format(self._sil.gps()._longitude))
        self.LOG.info('heading {}'.format(self._sil.gps()._heading))
        self.LOG.info('motor velocity {}'.format(self._vil._velocity))
        self.LOG.info('steering angle {}'.format(self._vil._angle))
        self._tc.fwd()
        self._tc.velocity(0.5)
        self._sc.angle(0.8)



