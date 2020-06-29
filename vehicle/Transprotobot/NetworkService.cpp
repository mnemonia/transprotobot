#include "NetworkService.h"
#include <ESP8266WiFi.h>

NetworkService::NetworkService() {
}
void NetworkService::on() {
  Serial.println("NetworkService on ");
  WiFi.begin(this->ssid, this->password);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (count > 10) {
        break;
    }
    count++;
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void NetworkService::off() {
  Serial.println("NetworkService off");
}
