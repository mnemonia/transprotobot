import logging

class ThrottleControl():
    LOG = logging.getLogger('ThrottleControl')

    def __init__(self, gsl):
        self._gsl = gsl
        self._vel = 0

    def on(self):
        self.LOG.info('on')

    def velocity(self, vel):
        self.LOG.info('velocity')
        self._vel = vel
        self._gsl.publish('pac/tc/velocity', self._vel)

