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
     void connect();

  public:
    MqttService();
    void on();
    void subscribe(char* topicName);
    void publishDouble(char* topicName, double value);
};
#endif
