#include "GpsService.h"

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

GpsService::GpsService(GlobalServicesLayer* gsl):
  _gsl(gsl),
  timer(millis())
{
  this->serial = new SoftwareSerial(8, 7);
  this->gps = new Adafruit_GPS(this->serial);
}

void GpsService::on() {
  Serial.println("GpsService on ");
  this->gps->begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  this->gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  this->gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  this->gps->sendCommand(PGCMD_ANTENNA);
}

void GpsService::read() {
  Serial.println("GpsService read");
  char c = this->gps->read();
  // if you want to debug, this is a good time to do it!
  if ((c) && (GPSECHO)){
    Serial.write(c);
  }
 // if a sentence is received, we can check the checksum, parse it...
  if (this->gps->newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!this->gps->parse(this->gps->lastNMEA())){   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
    }
  }
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - this->timer > 2000) {
    this->timer = millis(); // reset the timer
    // this->_gsl->mqtt()->publishDouble("/transprotobot/sil/wheel/velocity", 0.75);
    Serial.print("\nTime: ");
    if (this->gps->hour < 10) { Serial.print('0'); }
    Serial.print(this->gps->hour, DEC); Serial.print(':');
    if (this->gps->minute < 10) { Serial.print('0'); }
    Serial.print(this->gps->minute, DEC); Serial.print(':');
    if (this->gps->seconds < 10) { Serial.print('0'); }
    Serial.print(this->gps->seconds, DEC); Serial.print('.');
    if (this->gps->milliseconds < 10) {
      Serial.print("00");
    } else if (this->gps->milliseconds > 9 && this->gps->milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(this->gps->milliseconds);
    Serial.print("Date: ");
    Serial.print(this->gps->day, DEC); Serial.print('/');
    Serial.print(this->gps->month, DEC); Serial.print("/20");
    Serial.println(this->gps->year, DEC);
    Serial.print("Fix: "); Serial.print((int)this->gps->fix);
    this->_gsl->mqtt()->publishDouble("/transprotobot/sil/gps/fix", (double)this->gps->fix);
    Serial.print(" quality: "); Serial.println((int)this->gps->fixquality);
    if (this->gps->fix) {
      Serial.print("Location: ");
      Serial.print(this->gps->latitude, 4); Serial.print(this->gps->lat);
      Serial.print(", ");
      Serial.print(this->gps->longitude, 4); Serial.println(this->gps->lon);

      Serial.print("Speed (knots): "); Serial.println(this->gps->speed);
      Serial.print("Angle: "); Serial.println(this->gps->angle);
      Serial.print("Altitude: "); Serial.println(this->gps->altitude);
      Serial.print("Satellites: "); Serial.println((int)this->gps->satellites);
    }
  }
}
