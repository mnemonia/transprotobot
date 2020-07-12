import logging
import json

class ThrottleControl():
    LOG = logging.getLogger('ThrottleControl')

    def __init__(self, gsl):
        self._gsl = gsl
        self._vel = 0

    def on(self):
        self.LOG.info('on')
        self.velocity(self._vel)

    def velocity(self, vel):
        self.LOG.info('velocity {}'.format(vel))
        self._vel = vel
        self._gsl.publish('pac/tc/velocity', vel)
        res = dict()
        res["command"] = "vil_adjust_velocity"
        res["value"] = self._vel
        self._gsl.publishToVehicle(res)

    def stop(self):
        self._gsl.publish('pac/tc/direction', 0)
        res = dict()
        res["command"] = "vil_adjust_direction"
        res["value"] = 0
        self._gsl.publishToVehicle(res)

    def fwd(self):
        self._gsl.publish('pac/tc/direction', 1)
        res = dict()
        res["command"] = "vil_adjust_direction"
        res["value"] = 1
        self._gsl.publishToVehicle(res)

    def bwd(self):
        self._gsl.publish('pac/tc/direction', 2)
        res = dict()
        res["command"] = "vil_adjust_direction"
        res["value"] = 2
        self._gsl.publishToVehicle(res)

