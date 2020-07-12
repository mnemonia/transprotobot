#include "TransprotobotVehicle.h"

TransprotobotVehicle::TransprotobotVehicle():
    _gsl(),
    _vil(),
    _sil(&_gsl),
    _pcl(&_gsl, &_vil)
{
}
void TransprotobotVehicle::on() {
  //Serial.println("TransprotobotVehicle init ...");
  this->_gsl.on();
  this->_sil.on();  
  this->_vil.on();
  this->_pcl.on();
  //Serial.println("TransprotobotVehicle init done");
}

void TransprotobotVehicle::tick() {
  //Serial.println("tick");
  // this->_pcl.write();
  _sil.write();
  _vil.write();
  _pcl.tick();
}

GlobalServicesLayer* TransprotobotVehicle::gsl() {
  return &_gsl;
}

void TransprotobotVehicle::read() {
  _pcl.read();
  _sil.read();
  _vil.read();  
}
