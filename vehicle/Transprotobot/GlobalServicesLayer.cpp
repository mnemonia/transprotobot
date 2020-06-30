#include "GlobalServicesLayer.h"
GlobalServicesLayer::GlobalServicesLayer(Adafruit_MQTT_Client* mqtt, Adafruit_MQTT_Subscribe* velocitySubscription):
  ns(),
  mqttService(mqtt, velocitySubscription)
{
  
}
void GlobalServicesLayer::on() {
  Serial.println("GlobalServicesLayer on");
  this->ns.on();
  this->mqttService.on();
}

void GlobalServicesLayer::off() {
  Serial.println("GlobalServicesLayer off");
}

MqttService* GlobalServicesLayer::mqtt() {
  return &this->mqttService;  
}
