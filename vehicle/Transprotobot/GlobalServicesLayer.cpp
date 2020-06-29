#include "GlobalServicesLayer.h"
GlobalServicesLayer::GlobalServicesLayer():
  ns(),
  mqttService()
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
