#ifndef SENSORINTERFACELAYER_H
#define SENSORINTERFACELAYER_H
#include <Arduino.h>
class SensorInterfaceLayer {
  public:
    SensorInterfaceLayer();
    void on();
    void read();
};
#endif
