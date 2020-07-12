#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

class MqttService {
  public:
    MqttService();
    void handle(double value);
    static void theCallback(double value);
};
#endif
