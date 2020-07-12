#ifndef TRANSPROTOBOTVEHICLE_H
#define TRANSPROTOBOTVEHICLE_H
#include <Arduino.h>
#include "VehicleInterfaceLayer.h"
#include "SensorInterfaceLayer.h"
#include "GlobalServicesLayer.h"
#include "PlanningAndControlLayer.h"
#include "Tickable.h"

class TransprotobotVehicle: public Tickable {
  
  private:
    GlobalServicesLayer _gsl;
    VehicleInterfaceLayer _vil;
    SensorInterfaceLayer _sil;
    PlanningAndControlLayer _pcl;
    
  public:
    TransprotobotVehicle();
    void on();
    virtual void tick();
    GlobalServicesLayer* gsl();
    void read();
    void regulate();
};
#endif
