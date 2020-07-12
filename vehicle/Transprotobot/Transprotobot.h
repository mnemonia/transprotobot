#ifndef TRANSPROTOBOT_H
#define TRANSPROTOBOT_H
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include "VehicleInterfaceLayer.h"
#include "SensorInterfaceLayer.h"
#include "GlobalServicesLayer.h"
#include "PlanningAndControlLayer.h"
#include "Tickable.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


class Transprotobot: public Tickable {
  
  private:
    GlobalServicesLayer _gsl;
    VehicleInterfaceLayer vil;
    SensorInterfaceLayer sil;
    PlanningAndControlLayer pcl;
    
  public:
    Transprotobot(Adafruit_MQTT_Client* mqtt, Adafruit_MQTT_Subscribe* velocitySubscription, Adafruit_MQTT_Subscribe* directionSubscription, SoftwareSerial* serial, Adafruit_GPS* gps);
    void init();
    virtual void tick();
    GlobalServicesLayer gsl();
};
#endif
