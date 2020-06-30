#ifndef THROTTLECONTROL_H
#define THROTTLECONTROL_H
#include <Arduino.h>
#include "GlobalServicesLayer.h"
#include "VehicleInterfaceLayer.h"
#include "SubscriptionCallbackDouble.h"

class ThrottleControl: public SubscriptionCallbackDouble {
  private:
    GlobalServicesLayer* pGsl;
    VehicleInterfaceLayer* pVil;
    void changeVelocity (const double val);
    void changeDirection (const int direction); // 0: stop, 1: fwd, 2: bwd
    
  public:
    ThrottleControl(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil);
    void on();
    virtual void handle(const double value);
};
#endif
