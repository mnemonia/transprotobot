#include "MqttService.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "transprotobot"
#define AIO_KEY         "123transprotobot"

MqttService::MqttService():
client(),
mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY),
topicA(&mqtt, AIO_USERNAME "/feeds/photocell")
{
}
void MqttService::on() {
  Serial.println("MqttService on");
}
Adafruit_MQTT_Publish& MqttService::with(char* topicName) {
  return this->topicA;
  //Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&this->mqtt, AIO_USERNAME "/feeds/photocell");
  //return photocell;
}
