from global_services import GlobalServices
from planning_and_control_layer import PlanningAndExportLayer
import logging

class Transprotobot():
    LOG = logging.getLogger("Transprotobot")

    def __init__(self):
        self._gsl = GlobalServices()
        self._pcl = PlanningAndExportLayer(self._gsl)

    def on(self):
        self.LOG.info('Transprotobot on')
        self._gsl.on()
        self._pcl.on()

def main():
    bot = Transprotobot()
    bot.on()


if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s %(levelname)s %(name)s %(filename)s %(lineno)d %(message)s', level=logging.DEBUG)
    _formatTime = logging.Formatter.formatTime
    def formatTime(*args):
        return _formatTime(*args).replace(",", ".")
    logging.Formatter.formatTime = formatTime
    main()


