#ifndef GPSSERVICE_H
#define GPSSERVICE_H
#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "GlobalServicesLayer.h"

class GpsService {
  private:
   GlobalServicesLayer* _gsl;
   SoftwareSerial* serial;
   Adafruit_GPS* gps;
   uint32_t timer;
    
  public:
    GpsService(GlobalServicesLayer* gsl);
    void on();
    void read();
};
#endif
