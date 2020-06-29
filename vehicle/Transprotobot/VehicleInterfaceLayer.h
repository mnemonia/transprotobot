#ifndef VEHICLEINTERFACELAYER_H
#define VEHICLEINTERFACELAYER_H
#include <Arduino.h>
#include "Drive.h"

class VehicleInterfaceLayer {
  private:
    Drive drive;
    
  public:
    VehicleInterfaceLayer();
    void on();
    void read();
    void write();
    void velocity(double v);
    void angle(double a);
};
#endif
