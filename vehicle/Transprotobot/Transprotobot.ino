#include "Transprotobot.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "test.mosquitto.org"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

WiFiClient client = WiFiClient();
Adafruit_MQTT_Client mqtt = Adafruit_MQTT_Client(&client, AIO_SERVER, AIO_SERVERPORT);
Adafruit_MQTT_Subscribe velocitySubscription = Adafruit_MQTT_Subscribe(&mqtt, "/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/pac/tc/velocity", MQTT_QOS_1);
Adafruit_MQTT_Subscribe directionSubscription = Adafruit_MQTT_Subscribe(&mqtt, "/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/pac/tc/direction", MQTT_QOS_1);
Transprotobot bot = Transprotobot(&mqtt, &velocitySubscription, &directionSubscription);

void Mqtt_callbackVelocityFn_wrapper(double v)
{
  bot.gsl().mqtt()->callbackVelocity(v);
}
void Mqtt_directionSubscriptionFn_wrapper(double v)
{
  bot.gsl().mqtt()->callbackDirection(v);
}

void setup() {
  Serial.begin(115200);
  delay(100);
  velocitySubscription.setCallback(Mqtt_callbackVelocityFn_wrapper);
  mqtt.subscribe(&velocitySubscription);
  directionSubscription.setCallback(Mqtt_directionSubscriptionFn_wrapper);
  mqtt.subscribe(&directionSubscription);
  
  bot.init();
}
 
void loop() {
  bot.tick();
  delay(2000);
}
