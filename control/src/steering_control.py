import logging

class SteeringControl():
    LOG = logging.getLogger('SteeringControl')

    def __init__(self, gsl):
        self._gsl = gsl
        self._angle = 0

    def on(self):
        self.LOG.info('on')

    def angle(self, a):
        self.LOG.info('angle')
        self._angle = a
        self._gsl.publish('pac/sc/angle', self._angle)

