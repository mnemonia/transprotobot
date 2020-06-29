#include "VehicleInterfaceLayer.h"

VehicleInterfaceLayer::VehicleInterfaceLayer():
   drive()
{

}

void VehicleInterfaceLayer::on() {
  Serial.println("VehicleInterfaceLayer on");
  this->drive.on();
}

void VehicleInterfaceLayer::read() {
  Serial.println("VehicleInterfaceLayer read vehicle data");
}

void VehicleInterfaceLayer::write() {
  Serial.println("VehicleInterfaceLayer write vehicle data");
}

void VehicleInterfaceLayer::velocity(double v) {
  Serial.println("VehicleInterfaceLayer velocity");
  this->drive.velocity(v);
}

void VehicleInterfaceLayer::angle(double a) {
  Serial.println("VehicleInterfaceLayer angle");
  this->drive.angle(a);
}
