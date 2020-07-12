#include "SensorInterfaceLayer.h"
#include <ArduinoJson.h>

SensorInterfaceLayer::SensorInterfaceLayer(GlobalServicesLayer* gsl):
  isDirty(true),
  distance_front_in_m(0.0)
{
  
}
void SensorInterfaceLayer::on() {
  // Serial.println("SensorInterfaceLayer on");
}

void SensorInterfaceLayer::read() {
  // Serial.println("SensorInterfaceLayer read in all sensor values");
  distance_front_in_m = 4.2;
}

void SensorInterfaceLayer::write() {
  // Serial.println("SensorInterfaceLayer read in all sensor values");
  if (isDirty) {
    StaticJsonDocument<200> doc;
    doc["command"] = "sil_update";
    doc["distance_front_in_m"] = distance_front_in_m;
    serializeJson(doc, Serial);
    Serial.println();
    
    isDirty = false;
  }
}
