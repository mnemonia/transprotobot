import logging
from mqtt_service import MqttService

class GlobalServices():
    LOG = logging.getLogger('GlobalServices')

    def __init__(self):
        self.mqtt = MqttService()

    def on(self):
        self.LOG.info('Starting GlobalServices')
        self.mqtt.on()

    def publish(self, topic, message):
        self.mqtt.publish('transprotobot/' + topic, message)
