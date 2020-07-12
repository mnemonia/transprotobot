#ifndef DRIVE_H
#define DRIVE_H
#include <Arduino.h>
#include <Adafruit_MotorShield.h>

class Drive {
  private:
    double _speed;
    double _angle;
    boolean _isFwd;
    Adafruit_MotorShield _afms;
    
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
