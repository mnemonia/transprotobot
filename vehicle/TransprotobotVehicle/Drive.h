#ifndef DRIVE_H
#define DRIVE_H
#include <Arduino.h>
#include <Servo.h>

class Drive {
  private:
    double _velocity;
    double _angle;
    boolean _isFwd;
    int _motorPinA1;
    int _motorPinA2;
    int _speedPinA;
    Servo _steeringServo;
    
  public:
    Drive();
    void on();
    void angle(double a);
    void velocity(double v);
    void fwd();
    void bwd();
    void stop();
    void regulate();
};
#endif
