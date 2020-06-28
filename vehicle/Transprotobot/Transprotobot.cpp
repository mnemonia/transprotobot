#include "Transprotobot.h"
Transprotobot::Transprotobot():
    gsl(),
    vil(),
    sil()
{
}
void Transprotobot::init() {
  Serial.println("Transprotobot init ...");
  this->gsl.on();
  this->sil.on();  
  this->vil.on();
  Serial.println("Transprotobot init done");
}

void Transprotobot::tick() {
  Serial.println("tick");
  this->sil.read();
  this->vil.read();
  this->vil.write();
}
