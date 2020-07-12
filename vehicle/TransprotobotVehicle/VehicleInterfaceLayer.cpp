#include "VehicleInterfaceLayer.h"

VehicleInterfaceLayer::VehicleInterfaceLayer():
   _drive()
{

}

void VehicleInterfaceLayer::on() {
  //Serial.println("VehicleInterfaceLayer on");
  this->_drive.on();
}

void VehicleInterfaceLayer::read() {
  // Serial.println("VehicleInterfaceLayer read vehicle data");
}

void VehicleInterfaceLayer::write() {
  // Serial.println("VehicleInterfaceLayer write vehicle data");
}

void VehicleInterfaceLayer::regulate() {
  // Serial.println("VehicleInterfaceLayer write vehicle data");
  _drive.regulate();
}

Drive* VehicleInterfaceLayer::drive() {
  return &this->_drive;
}
