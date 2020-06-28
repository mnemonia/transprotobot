#include "SensorInterfaceLayer.h"
SensorInterfaceLayer::SensorInterfaceLayer() {
}
void SensorInterfaceLayer::on() {
  Serial.println("SensorInterfaceLayer on");
}

void SensorInterfaceLayer::read() {
  Serial.println("SensorInterfaceLayer read in all sensor values");
}
