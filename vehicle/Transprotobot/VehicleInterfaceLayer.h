#ifndef VEHICLEINTERFACELAYER_H
#define VEHICLEINTERFACELAYER_H
#include <Arduino.h>
class VehicleInterfaceLayer {
  private:
    boolean isToggle;
    
  public:
    VehicleInterfaceLayer();
    void on();
    void read();
    void write();    
};
#endif
