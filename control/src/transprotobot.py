from global_services import GlobalServices
from planning_and_control_layer import PlanningAndControlLayer
from sensor_interface_layer import SensorInterfaceLayer
from vehicle_interface_layer import VehicleInterfaceLayer
import logging
import time

class Transprotobot():
    LOG = logging.getLogger("Transprotobot")

    def __init__(self):
        self._gsl = GlobalServices()
        self._sil = SensorInterfaceLayer(self._gsl)
        self._vil = VehicleInterfaceLayer(self._gsl)
        self._pcl = PlanningAndControlLayer(self._gsl, self._sil, self._vil)

    def on(self):
        self.LOG.info('Transprotobot on')
        self._gsl.on()
        self._sil.on()
        self._vil.on()
        self._pcl.on()

    def tick(self):
        self._sil.read()
        self._vil.read()
        self._pcl.tick()


def main():
    bot = Transprotobot()
    bot.on()
    while(True):
        bot.tick()
        time.sleep(2)

if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s %(levelname)s %(name)s %(filename)s %(lineno)d %(message)s', level=logging.DEBUG)
    _formatTime = logging.Formatter.formatTime
    def formatTime(*args):
        return _formatTime(*args).replace(",", ".")
    logging.Formatter.formatTime = formatTime
    main()


