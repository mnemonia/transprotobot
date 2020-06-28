#include "Transprotobot.h"

Transprotobot bot = Transprotobot();

void setup() {
  Serial.begin(115200);
  delay(100);
  bot.init();
}
 
void loop() {
  bot.tick();
  delay(1000);
}
