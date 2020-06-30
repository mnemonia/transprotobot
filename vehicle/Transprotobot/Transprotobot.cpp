#include "Transprotobot.h"
Transprotobot::Transprotobot(Adafruit_MQTT_Client* mqtt, Adafruit_MQTT_Subscribe* velocitySubscription):
    _gsl(mqtt, velocitySubscription),
    vil(),
    sil(&_gsl),
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
