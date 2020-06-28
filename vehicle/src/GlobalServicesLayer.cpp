#include "GlobalServicesLayer.h"
GlobalServicesLayer::GlobalServicesLayer():
  ns(),
  mqttService()
{
  
}
void GlobalServicesLayer::on() {
  Serial.println("GlobalServicesLayer on");
  this->ns.on();
}

void GlobalServicesLayer::off() {
  Serial.println("GlobalServicesLayer off");
}
