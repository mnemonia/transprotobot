import logging
from mqtt_service import MqttService
import serial
import json
import platform

class GlobalServices():
    LOG = logging.getLogger('GlobalServices')

    def __init__(self):
        self.mqtt = MqttService()

    def on(self):
        self.LOG.info('Starting GlobalServices')
        self.mqtt.on()

        if platform.system() == 'Linux':
            self._ser = serial.Serial('/dev/ttyACM0',baudrate=9600,timeout=1)
        else:
            self._ser = serial.Serial('COM4',baudrate=9600,timeout=1,parity=serial.PARITY_NONE,bytesize=serial.EIGHTBITS,rtscts=1)

        self.LOG.info('USB-port: {}'.format(self._ser.name))

    def publish(self, topic, message):
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/' + topic, message)

    def readFromVehicle(self):
        self.LOG.info('readFromVehicle')
        if not self._ser.in_waiting:
            return None
        return self._ser.readline()

    def publishToVehicle(self, message):
        self.LOG.info('publishToVehicle {}'.format(message))
        msg = bytearray(json.dumps(message) + '\n', encoding='utf-8')
        self._ser.write(msg)
        self._ser.flush()
