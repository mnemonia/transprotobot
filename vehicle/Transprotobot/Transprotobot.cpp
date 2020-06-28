#include "Transprotobot.h"
Transprotobot::Transprotobot():
    vil(),
    sil(),
    gsl()
{
}
void Transprotobot::init() {
  Serial.println("Transprotobot init ...");
  this->gsl.on();
  this->vil.on();
  this->sil.on();
  Serial.println("Transprotobot init done");
}

void Transprotobot::tick() {
  Serial.println("tick");
  this->sil.read();
  this->vil.read();
  this->vil.write();
}
