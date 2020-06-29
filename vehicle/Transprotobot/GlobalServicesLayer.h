#ifndef GLOBALSERVICESLAYER_H
#define GLOBALSERVICESLAYER_H
#include <Arduino.h>
#include "NetworkService.h"
#include "MqttService.h"

class GlobalServicesLayer {
  private:
    NetworkService ns;
    MqttService mqttService;

  public:
    GlobalServicesLayer();
    void on();
    void off();
    MqttService* mqtt();
};
#endif
