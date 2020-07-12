#include "PlanningAndControlLayer.h"
#include <ArduinoJson.h>

PlanningAndControlLayer::PlanningAndControlLayer(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil):
  _gsl(gsl),
  _vil(vil),
  _isDirtyVelocity(true),
  _isDirtyAngle(true),
  _isDirtyDirection(true),
  _velocity(0.0),
  _angle(0.0),
  _direction(0)
{

}
void PlanningAndControlLayer::on() {
  //  Serial.println("PlanningAndControlLayer on");
  while (!Serial) continue;
}
void PlanningAndControlLayer::tick() {
  //  Serial.println("PlanningAndControlLayer tick");
  if(_isDirtyDirection) {
    switch(_direction) {
      case 1:
        _vil->drive()->fwd();
        break;
      case 2:
        _vil->drive()->bwd();
        break;
      case 0:
      default:
        _vil->drive()->stop();
    }
    _isDirtyDirection = false;
  }
  if(_isDirtyVelocity) {
    _vil->drive()->velocity(_velocity);
    _isDirtyVelocity = false;
  }
  if(_isDirtyAngle) {
    _vil->drive()->angle(_angle);
    _isDirtyAngle = false;
  }  
}

void PlanningAndControlLayer::read() {
  //  Serial.println("PlanningAndControlLayer read");

  if (Serial.available()) {
    StaticJsonDocument<300> doc;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, Serial); // {"command":"vil_adjust_angle","value":0}
    if (err == DeserializationError::Ok) {
      const char* command = doc["command"];
      if (strcmp(command, "vil_adjust_angle") == 0) {
        _angle = doc["value"];
        _isDirtyAngle = true;
        doc["command"] = "vil_update_angle";
        serializeJson(doc, Serial);
        Serial.println();
      } else if (strcmp(command, "vil_adjust_velocity") == 0) {
        _velocity = doc["value"];
        _isDirtyVelocity = true;
        doc["command"] = "vil_update_velocity";
        serializeJson(doc, Serial);
        Serial.println();
      } else if (strcmp(command, "vil_adjust_direction") == 0) {
        _direction = doc["value"];
        _isDirtyDirection = true;
        doc["command"] = "vil_update_direction";
        serializeJson(doc, Serial);
        Serial.println();
      }
      
    }
  }

}
