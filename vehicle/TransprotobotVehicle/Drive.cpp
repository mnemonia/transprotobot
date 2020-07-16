#include "Drive.h"
Drive::Drive():
  _velocity(0),
  _angle(0),
  _isFwd(true),
  _motorPinA1(13),
  _motorPinA2(12),
  _speedPinA(10),
  _steeringServo()
{
  pinMode(_motorPinA1, OUTPUT);
  pinMode(_motorPinA2, OUTPUT);
  pinMode(_speedPinA, OUTPUT);
}
void Drive::on() {
//  Serial.println("Drive on");
  analogWrite(_speedPinA, _velocity);
  _steeringServo.attach(5);
  angle(0);
}

void Drive::angle(double a) {
//  Serial.println("Drive set angle");
  if (a == 0) {
    a = 90;
  } else if (a > 0) {
    a *= 100;
    a = map(a, 0, 100, 90, 180);
  } else {
    a *= 100;
    a = abs(a);
    a = 90.0 - map(a, 0, 100, 0, 90);
  }
  _steeringServo.write(a);
}

void Drive::velocity(double v) {
//  Serial.print("Drive set velocity ");
  _velocity = v;
  v *= 100;
  uint8_t vel = map(v, 0, 100, 0, 255);
  Serial.print("{\"command\":\"vil_status_motor_velocity\",\"value\":");Serial.print(vel);Serial.println("}");
  analogWrite(_speedPinA, vel);
}

void Drive::fwd() {
  //Serial.println("Drive set fwd");
  digitalWrite(_motorPinA1, HIGH);
  digitalWrite(_motorPinA2, LOW);
  _isFwd = true;
}

void Drive::bwd() {
  //Serial.println("Drive set bwd");
  digitalWrite(_motorPinA1, LOW);
  digitalWrite(_motorPinA2, HIGH);
  _isFwd = false;
}

void Drive::stop() {
  //Serial.println("Drive stop");
  digitalWrite(_motorPinA1, LOW);
  digitalWrite(_motorPinA2, LOW);
  _isFwd = false;
}

void Drive::regulate() {
  
}
