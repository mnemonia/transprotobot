#ifndef STEERINGCONTROL_H
#define STEERINGCONTROL_H
#include <Arduino.h>
#include "GlobalServicesLayer.h"
#include "VehicleInterfaceLayer.h"

class SteeringControl {
  private:
    GlobalServicesLayer* pGsl;
    VehicleInterfaceLayer* pVil;
    
  public:
    SteeringControl(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil);
    void on();
};
#endif
