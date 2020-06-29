#include "SensorInterfaceLayer.h"
SensorInterfaceLayer::SensorInterfaceLayer(GlobalServicesLayer* gsl):
  _gpss(gsl)
{
  
}
void SensorInterfaceLayer::on() {
  Serial.println("SensorInterfaceLayer on");
  this->_gpss.on();
}

void SensorInterfaceLayer::read() {
  Serial.println("SensorInterfaceLayer read in all sensor values");
  this->_gpss.read();
}
