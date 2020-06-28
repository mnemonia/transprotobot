#ifndef SENSORINTERFACELAYER_H
#define SENSORINTERFACELAYER_H
#include <Arduino.h>
#include "GpsService.h"

class SensorInterfaceLayer {
  private:
    GpsService gpss;
    
  public:
    SensorInterfaceLayer();
    void on();
    void read();
};
#endif
