#include "SensorInterfaceLayer.h"
SensorInterfaceLayer::SensorInterfaceLayer():
  gpss()
{
  
}
void SensorInterfaceLayer::on() {
  Serial.println("SensorInterfaceLayer on");
  this->gpss.on();
}

void SensorInterfaceLayer::read() {
  Serial.println("SensorInterfaceLayer read in all sensor values");
  this->gpss.read();
}
