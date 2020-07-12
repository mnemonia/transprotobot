#include "TransprotobotVehicle.h"

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousTickMillis = 0;        // will store last time LED was updated
unsigned long previousSensorMillis = 0;        // will store last time LED was updated

// constants won't change:
const long tickInterval = 1000;           // interval at which to blink (milliseconds)
const long sensorInterval = 250;           // interval at which to blink (milliseconds)

TransprotobotVehicle bot = TransprotobotVehicle();

void setup() {
  Serial.begin(9600);  
  bot.on();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousSensorMillis >= sensorInterval) {
    // save the last time you blinked the LED
    previousSensorMillis = currentMillis;

    bot.read();
  }

  if (currentMillis - previousTickMillis >= tickInterval) {
    // save the last time you blinked the LED
    previousTickMillis = currentMillis;
    
    bot.tick();
  }
}
