import logging
import paho.mqtt.client as mqtt

class GpsService():
    LOG = logging.getLogger('GpsService')
    def __init__(self, gsl):
        self._gsl = gsl
        self._latitude = 0
        self._longitude = 0
        self._heading = 0

    def on(self):
        self.LOG.info('GpsService on ...')
        client = mqtt.Client()

        def on_connect(client, userdata, flags, rc):
            self.LOG.info("Connected with result code " + str(rc))
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/milliseconds')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/fix')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/speed')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/angle')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/altitude')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/satellites')
            client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/compass/heading')

        def on_message(client, userdata, msg):
            self.LOG.info(msg.topic+" "+str(msg.payload))
            if(msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude'):
                self._latitude = float(msg.payload)
            elif(msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude'):
                self._longitude = float(msg.payload)
            elif(msg.topic == '/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/compass/heading'):
                self._heading = float(msg.payload)

        client.on_connect = on_connect
        client.on_message = on_message
        self.LOG.info('GpsService connect')
        client.connect("test.mosquitto.org", 1883, 60)
        self.LOG.info('GpsService start')
        client.loop_start()
        self.LOG.info('GpsService on done')

    def read(self):
        self.LOG.info('Read GPS')


class SensorInterfaceLayer():
    LOG = logging.getLogger('PathPlanner')

    def __init__(self, gsl):
        self._gsl = gsl
        self._gpsService = GpsService(gsl)

    def on(self):
        self._gpsService.on()

    def read(self):
        self._gpsService.read()