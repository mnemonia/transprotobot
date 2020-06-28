#ifndef GPSSERVICE_H
#define GPSSERVICE_H
#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

class GpsService {
  private:
   SoftwareSerial* serial;
   Adafruit_GPS* gps;
   uint32_t timer;
    
  public:
    GpsService();
    void on();
    void read();
};
#endif
