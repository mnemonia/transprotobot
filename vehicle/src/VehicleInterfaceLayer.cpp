#include "VehicleInterfaceLayer.h"
VehicleInterfaceLayer::VehicleInterfaceLayer(): isToggle(false) {
  pinMode(0, OUTPUT);
}
void VehicleInterfaceLayer::on() {
  Serial.println("VehicleInterfaceLayer on");
}

void VehicleInterfaceLayer::read() {
  Serial.println("VehicleInterfaceLayer read vehicle data");
}

void VehicleInterfaceLayer::write() {
  Serial.println("VehicleInterfaceLayer write vehicle data");
  if (this->isToggle) {
     digitalWrite(0, HIGH);
  } else {
    digitalWrite(0, LOW);
  }
  this->isToggle = !this->isToggle; 
}
