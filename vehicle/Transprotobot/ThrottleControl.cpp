#include "ThrottleControl.h"
ThrottleControl::ThrottleControl(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil):
  pGsl(gsl),
  pVil(vil)
{

}

void ThrottleControl::on() {
  Serial.println("ThrottleControl on");
  this->pVil->velocity(1.0);
  this->pGsl->mqtt()->publishDouble("/transprotobot/sil/wheel/velocity", 0.75);
}
