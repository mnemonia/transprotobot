#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include "Transprotobot.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "test.mosquitto.org"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

#define TX_PIN 13
#define RX_PIN 12
SoftwareSerial mySerial(TX_PIN, RX_PIN);
//Adafruit_GPS GPS(&Wire);
Adafruit_GPS GPS(&mySerial);

WiFiClient client = WiFiClient();
Adafruit_MQTT_Client mqtt = Adafruit_MQTT_Client(&client, AIO_SERVER, AIO_SERVERPORT);
Adafruit_MQTT_Subscribe velocitySubscription = Adafruit_MQTT_Subscribe(&mqtt, "/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/pac/tc/velocity", MQTT_QOS_1);
Adafruit_MQTT_Subscribe directionSubscription = Adafruit_MQTT_Subscribe(&mqtt, "/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/pac/tc/direction", MQTT_QOS_1);
Transprotobot bot = Transprotobot(&mqtt, &velocitySubscription, &directionSubscription, &mySerial, &GPS);

void Mqtt_callbackVelocityFn_wrapper(double v)
{
//   bot.gsl().mqtt()->callbackVelocity(v);
}
void Mqtt_directionSubscriptionFn_wrapper(double v)
{
//   bot.gsl().mqtt()->callbackDirection(v);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Starting Transprotobot");
  velocitySubscription.setCallback(Mqtt_callbackVelocityFn_wrapper);
  mqtt.subscribe(&velocitySubscription);
  directionSubscription.setCallback(Mqtt_directionSubscriptionFn_wrapper);
  mqtt.subscribe(&directionSubscription);

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  //GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  // Ask for firmware version
  //mySerial.println(PMTK_Q_RELEASE);
  bot.init();
}
 
void loop() {
   char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (c){
    //Serial.println(c);
  }
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.print("NMEA "); Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
    GPS.parse(GPS.lastNMEA());
    Serial.print("\nTime: ");
      if (GPS.hour < 10) { Serial.print('0'); }
      Serial.print(GPS.hour, DEC); Serial.print(':');
      if (GPS.minute < 10) { Serial.print('0'); }
      Serial.print(GPS.minute, DEC); Serial.print(':');
      if (GPS.seconds < 10) { Serial.print('0'); }
      Serial.print(GPS.seconds, DEC); Serial.print('.');
      if (GPS.milliseconds < 10) {
        Serial.print("00");
      } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
        Serial.print("0");
      }
      Serial.println(GPS.milliseconds);
      Serial.print("Date: ");
      Serial.print(GPS.day, DEC); Serial.print('/');
      Serial.print(GPS.month, DEC); Serial.print("/20");
      Serial.println(GPS.year, DEC);
      Serial.print("Fix: "); Serial.print((int)GPS.fix);
      Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
     // if (GPS.fix) {
          Serial.print("Location: ");
          //Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
          Serial.print(GPS.latitudeDegrees);
          Serial.print(", ");
          //Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
          Serial.println(GPS.longitudeDegrees);
          Serial.print("Speed (knots): "); Serial.println(GPS.speed);
          Serial.print("Angle: "); Serial.println(GPS.angle);
          Serial.print("Altitude: "); Serial.println(GPS.altitude);
          Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
     // }
  }
  bot.tick();
  delay(15);
}
