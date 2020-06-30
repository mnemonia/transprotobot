#ifndef GLOBALSERVICESLAYER_H
#define GLOBALSERVICESLAYER_H
#include <Arduino.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "NetworkService.h"
#include "MqttService.h"

class GlobalServicesLayer {
  private:
    NetworkService ns;
    MqttService mqttService;

  public:
    GlobalServicesLayer(Adafruit_MQTT_Client* mqtt, Adafruit_MQTT_Subscribe* velocitySubscription);
    void on();
    void off();
    MqttService* mqtt();
};
#endif
