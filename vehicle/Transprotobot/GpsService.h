#ifndef GPSSERVICE_H
#define GPSSERVICE_H
#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "GlobalServicesLayer.h"

class GpsService {
  private:
   GlobalServicesLayer* _gsl;
   uint32_t _timer;
   Adafruit_GPS* _gps;
    
  public:
    GpsService(GlobalServicesLayer* gsl, SoftwareSerial* serial, Adafruit_GPS* gps);
    ~GpsService();
    void on();
    void read();
};
#endif
