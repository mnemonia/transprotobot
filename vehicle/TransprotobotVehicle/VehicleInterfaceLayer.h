#ifndef VEHICLEINTERFACELAYER_H
#define VEHICLEINTERFACELAYER_H
#include <Arduino.h>
#include "Drive.h"

class VehicleInterfaceLayer {
  private:
    Drive _drive;
    
  public:
    VehicleInterfaceLayer();
    void on();
    void read();
    void write();
    void regulate();
    Drive* drive();
};
#endif
