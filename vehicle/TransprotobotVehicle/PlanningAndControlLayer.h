#ifndef PLANNINGANDCONTROLLAYER_H
#define PLANNINGANDCONTROLLAYER_H
#include <Arduino.h>
#include "GlobalServicesLayer.h"
#include "VehicleInterfaceLayer.h"
#include "Tickable.h"

class PlanningAndControlLayer: public Tickable {
  private:
    GlobalServicesLayer* _gsl;
    VehicleInterfaceLayer* _vil;
    boolean _isDirtyVelocity;
    boolean _isDirtyAngle;
    boolean _isDirtyDirection;
    double _velocity;
    double _angle;
    int _direction;
    
  public:
    PlanningAndControlLayer(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil);
    void on();
    virtual void tick();
    void read();
};
#endif
