#include "SensorInterfaceLayer.h"
SensorInterfaceLayer::SensorInterfaceLayer(GlobalServicesLayer* gsl, SoftwareSerial* serial, Adafruit_GPS* gps):
  _gpss(gsl, serial, gps)
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
