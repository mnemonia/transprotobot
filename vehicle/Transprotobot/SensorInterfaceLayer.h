#ifndef SENSORINTERFACELAYER_H
#define SENSORINTERFACELAYER_H
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include "GpsService.h"
#include "GlobalServicesLayer.h"

class SensorInterfaceLayer {
  private:
    GpsService _gpss;
    
  public:
    SensorInterfaceLayer(GlobalServicesLayer* gsl, SoftwareSerial* serial, Adafruit_GPS* gps);
    void on();
    void read();
};
#endif
