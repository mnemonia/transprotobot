#ifndef THROTTLECONTROL_H
#define THROTTLECONTROL_H
#include <Arduino.h>
#include "GlobalServicesLayer.h"
#include "VehicleInterfaceLayer.h"

class ThrottleControl {
  private:
    GlobalServicesLayer* pGsl;
    VehicleInterfaceLayer* pVil;
    
  public:
    ThrottleControl(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil);
    void on();
};
#endif
