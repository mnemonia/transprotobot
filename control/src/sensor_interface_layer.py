import logging

class SensorInterfaceLayer():
    LOG = logging.getLogger('PathPlanner')

    def __init__(self, gsl):
        self._gsl = gsl