import paho.mqtt.client as mqtt

class Test():
    def __init__(self):
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message

    # The callback for when the client receives a CONNACK response from the server.
    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result code "+str(rc))

        # Subscribing in on_connect() means that if we lose the connection and
        # reconnect then subscriptions will be renewed.
        #client.subscribe("$SYS/#")
        self.client.subscribe("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/pac/tc/velocity")
        self.client.subscribe("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/pac/sc/angle")
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/fix')
        self.client.subscribe("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/wheel/velocity")
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/wheel/direction')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/altitude')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/speed')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/compass/heading')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/enable')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity')
        self.client.subscribe('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle')


    # The callback for when a PUBLISH message is received from the server.
    def on_message(self, client, userdata, msg):
        print(msg.topic+" "+str(msg.payload))

    def run(self):
        print("Connecting..")
        self.client.connect("test.mosquitto.org", 1883, 60)
        # client.connect("192.168.100.106", 1883, 60)
        print("Connected")
        self.client.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/enable', 1)
        self.client.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 0)
        self.client.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 0)
        self.client.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', 0)
        # Blocking call that processes network traffic, dispatches callbacks and
        # handles reconnecting.
        # Other loop*() functions are available that give a threaded interface and a
        # manual interface.
        print("Wait for messages")
        self.client.loop_forever()
        print("finishing")


t = Test()
t.run()