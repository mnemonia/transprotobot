#include "SteeringControl.h"
SteeringControl::SteeringControl(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil):
   pGsl(gsl),
   pVil(vil)
{

}
void SteeringControl::on() {
  Serial.println("SteeringControl on");
}
