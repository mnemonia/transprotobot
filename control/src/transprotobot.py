from global_services import GlobalServices
from planning_and_control_layer import PlanningAndControlLayer
from sensor_interface_layer import SensorInterfaceLayer
import logging
import time

class Transprotobot():
    LOG = logging.getLogger("Transprotobot")

    def __init__(self):
        self._gsl = GlobalServices()
        self._sil = SensorInterfaceLayer(self._gsl)
        self._pcl = PlanningAndControlLayer(self._gsl)

    def on(self):
        self.LOG.info('Transprotobot on')
        self._gsl.on()
        self._sil.on()
        self._pcl.on()

    def tick(self):
        self._sil.read()


def main():
    bot = Transprotobot()
    bot.on()
    while(True):
        bot.tick()
        time.sleep(4)


if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s %(levelname)s %(name)s %(filename)s %(lineno)d %(message)s', level=logging.DEBUG)
    _formatTime = logging.Formatter.formatTime
    def formatTime(*args):
        return _formatTime(*args).replace(",", ".")
    logging.Formatter.formatTime = formatTime
    main()


