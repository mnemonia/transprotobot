import logging

class ThrottleControl():
    LOG = logging.getLogger('ThrottleControl')

    def __init__(self, gsl):
        self._gsl = gsl
        self._vel = 0

    def on(self):
        self.LOG.info('on')
        self.velocity(self._vel)

    def velocity(self, vel):
        self.LOG.info('velocity')
        self._vel = vel
        self._gsl.publish('pac/tc/velocity', vel)

    def stop(self):
        self._gsl.publish('pac/tc/direction', 0)

    def fwd(self):
        self._gsl.publish('pac/tc/direction', 1)

    def bwd(self):
        self._gsl.publish('pac/tc/direction', 2)

