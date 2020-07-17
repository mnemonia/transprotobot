import logging

class TopLevelControl():
    LOG = logging.getLogger('TopLevelControl')

    def __init__(self, gsl, sil, tc, sc):
        self._gsl = gsl
        self._sil = sil
        self._tc = tc
        self._sc = sc
        self._velocity = 0
        self._angle = 0
        self._direction = 0

    def on(self):
        self.LOG.info('on')

    def tick(self):
        self.LOG.info('tick')
        if self._sil.gps()._rc_direction != self._direction:
            self._direction = self._sil.gps()._rc_direction
            if self._direction == 0:
                self._tc.stop()
            if self._direction == 1:
                self._tc.fwd()
            if self._direction == 2:
                self._tc.bwd()
        if self._sil.gps()._rc_velocity != self._velocity:
            self._velocity = self._sil.gps()._rc_velocity
            self._tc.velocity(self._velocity)
        if self._sil.gps()._rc_angle != self._angle:
            self._angle = self._sil.gps()._rc_angle
            self._sc.angle(self._angle)

