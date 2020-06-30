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
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/' + topic, message)
