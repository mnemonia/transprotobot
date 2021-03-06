from mqtt_service import MqttService
import time

class Simulator():
    def on(self):
        self.mqtt = MqttService()
        self.mqtt.on()

    def rc(self):
        print("init rc")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/enable', 1)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 0)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 0)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', 0)
        time.sleep(2)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 1)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 1)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', 1)
        time.sleep(6)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 0)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', -1)
        time.sleep(6)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 1)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', 0)
        time.sleep(6)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 0)
        time.sleep(6)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 2)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 1)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', 0)
        time.sleep(6)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 0)

    def run(self):
        print("init")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/enable', 1)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/direction', 0)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/velocity', 0)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/uil/rc/angle', 0)

        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031944)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083533)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031891)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083556)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031844)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083570)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031798)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083597)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031745)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083629)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031766)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083707)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031788)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083771)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031807)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083816)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031860)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083771)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031910)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083729)
        time.sleep(2)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031965)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083692)
        time.sleep(2)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031962)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083610)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031950)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083551)
        time.sleep(2)
        print("pos")
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude', 47.031944)
        self.mqtt.publish('/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude', 9.083533)
        time.sleep(1)
        print("end")


s = Simulator()
s.on()
s.rc()
# s.autonomous()