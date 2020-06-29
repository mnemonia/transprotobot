#ifndef PLANNINGANDCONTROLLAYER_H
#define PLANNINGANDCONTROLLAYER_H
#include <Arduino.h>
#include "GlobalServicesLayer.h"
#include "SteeringControl.h"
#include "ThrottleControl.h"

class PlanningAndControlLayer {
  private:
    SteeringControl sc;
    ThrottleControl tc;
    
  public:
    PlanningAndControlLayer(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil);
    void on();
};
#endif
