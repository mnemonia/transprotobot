#ifndef SENSORINTERFACELAYER_H
#define SENSORINTERFACELAYER_H
#include <Arduino.h>
#include "GpsService.h"
#include "GlobalServicesLayer.h"

class SensorInterfaceLayer {
  private:
    GpsService _gpss;
    
  public:
    SensorInterfaceLayer(GlobalServicesLayer* gsl);
    void on();
    void read();
};
#endif
