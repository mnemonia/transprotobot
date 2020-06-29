import logging
import paho.mqtt.client as mqtt

class MqttService():
    LOG = logging.getLogger('MqttService')

    def __init__(self):
        self.client = mqtt.Client()

    def on(self):
        self.LOG.info('connecting ...')
        self.client.connect("localhost", 1883, 60)
        self.LOG.info('connected')

    def publish(self, topic, message):
        self.client.publish(topic, message)

