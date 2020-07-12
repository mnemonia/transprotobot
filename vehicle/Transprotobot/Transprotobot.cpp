#include "Transprotobot.h"
Transprotobot::Transprotobot(Adafruit_MQTT_Client* mqtt, Adafruit_MQTT_Subscribe* velocitySubscription, Adafruit_MQTT_Subscribe* directionSubscription, SoftwareSerial* serial, Adafruit_GPS* gps):
    _gsl(mqtt, velocitySubscription, directionSubscription),
    vil(),
    sil(&_gsl, serial, gps),
    pcl(&_gsl, &vil)
{
}
void Transprotobot::init() {
  Serial.println("Transprotobot init ...");
  this->_gsl.on();
  this->sil.on();  
  this->vil.on();
  this->pcl.on();
  Serial.println("Transprotobot init done");
}

void Transprotobot::tick() {
  Serial.println("tick");
  this->_gsl.mqtt()->tick();
  this->sil.read();
  this->vil.read();
  this->vil.write();
}

GlobalServicesLayer Transprotobot::gsl() {
  return _gsl;
}
