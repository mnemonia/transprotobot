#include "MqttService.h"

#define AIO_SERVER      "test.mosquitto.org"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

MqttService::MqttService():
client(),
mqtt(&client, AIO_SERVER, AIO_SERVERPORT)
{
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MqttService::connect() {
  int8_t ret;

  // Stop if already connected.
  if (this->mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = this->mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(this->mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       this->mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
void MqttService::on() {
  Serial.println("MqttService on");
  connect();
}
void MqttService::subscribe(char* topicName) {
  Adafruit_MQTT_Subscribe* s = new Adafruit_MQTT_Subscribe(&this->mqtt, "/transprotobot/pac/tc/velocity"); // 
  this->mqtt.subscribe(s);
}
void MqttService::publishDouble(char* topicName, double value){
  Adafruit_MQTT_Publish p = Adafruit_MQTT_Publish(&this->mqtt, topicName);
  if (!p.publish(value)) {
      Serial.println(F("Failed"));
  } else {
      Serial.println(F("OK!"));
  }
}
