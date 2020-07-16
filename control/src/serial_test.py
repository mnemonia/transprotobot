import logging
import serial
import json
import platform
import time

class GlobalServices():
    LOG = logging.getLogger('GlobalServices')

    def on(self):
        self.LOG.info('Starting GlobalServices')

        if platform.system() == 'Linux':
            self._ser = serial.Serial('/dev/ttyACM0',baudrate=9600,timeout=1)
        else:
            self._ser = serial.Serial('COM5',baudrate=9600,timeout=1,parity=serial.PARITY_NONE,bytesize=serial.EIGHTBITS,rtscts=1)

        self.LOG.info('USB-port: {}'.format(self._ser.name))

    def readFromVehicle(self):
        self.LOG.info('readFromVehicle')
        if not self._ser.in_waiting:
            return None
        return self._ser.readline().rstrip()

    def publishToVehicle(self, message):
        self.LOG.info('publishToVehicle {}'.format(message))
        msg = bytearray(json.dumps(message) + '\n', encoding='utf-8')
        self._ser.write(msg)
        self._ser.flush()


def main():
    bot = GlobalServices()
    bot.on()
    while(True):
        res = bot.readFromVehicle()
        while(res != None):
            logging.info(res)
            res = bot.readFromVehicle()

        time.sleep(2)


if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s %(levelname)s %(name)s %(filename)s %(lineno)d %(message)s', level=logging.DEBUG)
    _formatTime = logging.Formatter.formatTime
    def formatTime(*args):
        return _formatTime(*args).replace(",", ".")
    logging.Formatter.formatTime = formatTime
    main()


