#include "MqttService.h"

MqttService::MqttService(Adafruit_MQTT_Client* mmqtt, Adafruit_MQTT_Subscribe* vs):
mqtt(mmqtt),
velocitySubscription(vs),
func()
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

void MqttService::subscribe2(char* topicName, SubscriptionCallbackDouble* f) {
  Serial.print("Subscribe to "); Serial.println(topicName);
  this->func = f;
  //Adafruit_MQTT_Subscribe* s = new Adafruit_MQTT_Subscribe(mqtt, topicName, MQTT_QOS_1); //
 // s->setCallback(slidercallback);
  //slidercallback(99.9);
 // if(!mqtt->subscribe(velocitySubscription)) {
 //     Serial.println(F("Subscribe failed"));
 // } else {
 //     Serial.println(F("Subscribe OK!"));
 // }
  publishDouble(topicName, 0.33);
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
    mqtt->processPackets(10000);
    if(! this->mqtt->ping()) {
       this->mqtt->disconnect();
    }
    Serial.println("MqttService tick done");
}

void MqttService::callbackVelocity(double value) {
  Serial.print("MqttService::callbackVelocity ");
  Serial.println(value);
  func->handle(value);
}
