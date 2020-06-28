#include "NetworkService.h"
#include <ESP8266WiFi.h>

NetworkService::NetworkService() {
}
void NetworkService::on() {
  Serial.println("NetworkService on ");
  WiFi.begin(this->ssid, this->password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void NetworkService::off() {
  Serial.println("NetworkService off");
}
