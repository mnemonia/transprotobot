#ifndef TRANSPROTOBOT_H
#define TRANSPROTOBOT_H
#include <Arduino.h>
#include "VehicleInterfaceLayer.h"
#include "SensorInterfaceLayer.h"
#include "GlobalServicesLayer.h"
#include "PlanningAndControlLayer.h"

class Transprotobot {
  
  private:
    GlobalServicesLayer gsl;
    VehicleInterfaceLayer vil;
    SensorInterfaceLayer sil;
    PlanningAndControlLayer pcl;
    
  public:
    Transprotobot();
    void init();
    void tick();
};
#endif
