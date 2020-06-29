#include "Drive.h"
Drive::Drive():
  _speed(0),
  _angle(0),
  _isFwd(true),
  _afms()
{

}
void Drive::on() {
  Serial.println("Drive on");
}

void Drive::angle(double a) {
  Serial.println("Drive set angle");
}

void Drive::velocity(double v) {
  Serial.println("Drive set velocity");
  uint8_t vel = map(v, 0, 1.0, 0, 255);
  this->_afms.getMotor(1)->setSpeed(vel);
}

void Drive::fwd() {
  Serial.println("Drive set fwd");
  this->_afms.getMotor(1)->run(FORWARD);
}

void Drive::bwd() {
  Serial.println("Drive set bwd");
  this->_afms.getMotor(1)->run(BACKWARD);
}

void Drive::stop() {
  Serial.println("Drive stop");
  this->_afms.getMotor(1)->setSpeed(0);
  this->_afms.getMotor(1)->run(RELEASE);
}
