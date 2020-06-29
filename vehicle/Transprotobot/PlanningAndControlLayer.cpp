#include "PlanningAndControlLayer.h"

PlanningAndControlLayer::PlanningAndControlLayer(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil):
   sc(gsl, vil),
   tc(gsl, vil)
{

}
void PlanningAndControlLayer::on() {
  Serial.println("PlanningAndControlLayer on");
  this->sc.on();
  this->tc.on();
}
