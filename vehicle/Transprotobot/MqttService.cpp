#include "MqttService.h"

MqttService::MqttService(Adafruit_MQTT_Client* mmqtt, Adafruit_MQTT_Subscribe* vs, Adafruit_MQTT_Subscribe* ds):
mqtt(mmqtt),
velocitySubscription(vs),
directionSubscription(ds),
func(),
callbackDirectionFunc()
{
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MqttService::connect() {
  int8_t ret;

  // Stop if already connected.
  if (this->mqtt->connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = this->mqtt->connect()) != 0) { // connect will return 0 for connected
       Serial.println(this->mqtt->connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       this->mqtt->disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
void MqttService::on() {
  Serial.println("MqttService on");
  connect();
}

void MqttService::subscribeVelocity(SubscriptionCallbackDouble* f) {
  Serial.print("Subscribe to velocity");
  this->func = f;
}
void MqttService::subscribeDirection(SubscriptionCallbackDouble* f) {
  Serial.print("Subscribe to direction");
  this->callbackDirectionFunc = f;
}

void MqttService::publishDouble(char* topicName, double value){
  Adafruit_MQTT_Publish p = Adafruit_MQTT_Publish(mqtt, topicName);
  if (!p.publish(value)) {
      Serial.println(F("Publish failed"));
  } else {
      Serial.println(F("Publish OK!"));
  }
}

void MqttService::tick() {
    Serial.println("MqttService tick ...");
    connect();
    mqtt->processPackets(20);
    if(! this->mqtt->ping()) {
       this->mqtt->disconnect();
    }
    Serial.println("MqttService tick done");
}

void MqttService::callbackVelocity(double value) {
  Serial.print("MqttService::callbackVelocity ");
  Serial.println(value);
  func->handle(0, value);
}

void MqttService::callbackDirection(double value) {
  Serial.print("MqttService::callbackDirection ");
  Serial.println(value);
  callbackDirectionFunc->handle(1, value);
}
