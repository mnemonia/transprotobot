#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

class MqttService {
  private:
     WiFiClient client;
     Adafruit_MQTT_Client mqtt;
     Adafruit_MQTT_Publish topicA;

  public:
    MqttService();
    void on();
    Adafruit_MQTT_Publish& with(char* topicName);
};
#endif
