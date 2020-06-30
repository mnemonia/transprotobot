#include "ThrottleControl.h"

ThrottleControl::ThrottleControl(GlobalServicesLayer* gsl, VehicleInterfaceLayer* vil):
  pGsl(gsl),
  pVil(vil)
{

}

void ThrottleControl::on() {
  Serial.println("ThrottleControl on");
  this->pGsl->mqtt()->subscribeVelocity(this);
  this->pGsl->mqtt()->subscribeDirection(this);
  this->changeDirection(0);
  this->changeVelocity(0.0);
}

void ThrottleControl::handle(const int mode, const double value) {
   Serial.println("ThrottleControl handle");
   switch(mode) {
      case 1:
          this->changeDirection(value);
          break;
      case 0:
      default:
          this->changeVelocity(value);
   }
}

void ThrottleControl::changeVelocity (const double val) {
  Serial.print("ThrottleControl changeVelocity to ");
  Serial.println(val);
  this->pVil->drive()->velocity(val);
  this->pGsl->mqtt()->publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/wheel/velocity", val);
}

void ThrottleControl::changeDirection(const int direction) {
  Serial.print("ThrottleControl changeDirection to ");
  Serial.println(direction);
  
  switch(direction) {
     case 1:
         this->pVil->drive()->fwd();
         break;
     case 2:
         this->pVil->drive()->bwd();
         break;
     case 0:
     default:
         this->pVil->drive()->stop();
  }

  this->pGsl->mqtt()->publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/wheel/direction", direction);
}
