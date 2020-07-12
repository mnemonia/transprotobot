#ifndef SENSORINTERFACELAYER_H
#define SENSORINTERFACELAYER_H
#include <Arduino.h>
#include "GlobalServicesLayer.h"

class SensorInterfaceLayer {
  private:
    boolean isDirty;
    float distance_front_in_m;
    
  public:
    SensorInterfaceLayer(GlobalServicesLayer* gsl);
    void on();
    void read();
    void write();
};
#endif
