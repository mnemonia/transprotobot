#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "SubscriptionCallbackDouble.h"
#include "Tickable.h"

class MqttService: public Tickable {
  private:
     Adafruit_MQTT_Client* mqtt;
     Adafruit_MQTT_Subscribe* velocitySubscription;
     SubscriptionCallbackDouble* func;
     void connect();

  public:
    MqttService(Adafruit_MQTT_Client* mqtt, Adafruit_MQTT_Subscribe* velocitySubscription);
    void on();
    void subscribe2(char* topicName, SubscriptionCallbackDouble* func);
    void publishDouble(char* topicName, double value);
    virtual void tick();
    void callbackVelocity(double value);
};
#endif
