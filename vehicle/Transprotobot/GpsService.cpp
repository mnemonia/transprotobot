#include "GpsService.h"

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

#define TX_PIN 15
#define RX_PIN 13
// Connect the GPS Power pin to 3.3V
// Connect the GPS Ground pin to ground
// Connect the GPS TX (transmit) pin to Digital 10
// Connect the GPS RX (receive) pin to Digital 7
//SoftwareSerial mySerial(TX_PIN, RX_PIN);
//Adafruit_GPS GPS(&mySerial);

GpsService::GpsService(GlobalServicesLayer* gsl, SoftwareSerial* serial, Adafruit_GPS* gps):
  _gsl(gsl),
  _timer(millis()),
  _gps(gps)
{
  // _serial = new SoftwareSerial(TX_PIN, RX_PIN);
  // _gps = new Adafruit_GPS(_serial);
}

GpsService::~GpsService() {
  // delete _gps;
  // delete _serial;
}

void GpsService::on() {
  Serial.println("GpsService on ");
  //_gps->begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  //_gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  // _gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  //_gps->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
  
  // Request updates on antenna status, comment out to keep quiet
 // _gps->sendCommand(PGCMD_ANTENNA);
 // delay(1000);
 // _serial->println(PMTK_Q_RELEASE);
}

void GpsService::read() {
  
   Serial.println("GpsService read");
  /* char c = _gps->read();
  // if you want to debug, this is a good time to do it!
  if ((c) && (GPSECHO)){
    Serial.print("Read "); Serial.write(c); Serial.println();
  }
 // if a sentence is received, we can check the checksum, parse it...
  if (_gps->newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.print("lastNMEA: ");Serial.println(_gps->lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!_gps->parse(_gps->lastNMEA())){   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
    }
  }
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - _timer > 2000) {
    _timer = millis(); // reset the timer
    // this->_gsl->mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/wheel/velocity", 0.75);
    Serial.print("\nTime: ");
    if (_gps->hour < 10) { Serial.print('0'); }
    Serial.print(_gps->hour, DEC); Serial.print(':');
    if (_gps->minute < 10) { Serial.print('0'); }
    Serial.print(_gps->minute, DEC); Serial.print(':');
    if (_gps->seconds < 10) { Serial.print('0'); }
    Serial.print(_gps->seconds, DEC); Serial.print('.');
    if (_gps->milliseconds < 10) {
      Serial.print("00");
    } else if (_gps->milliseconds > 9 && _gps->milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(_gps->milliseconds);
    Serial.print("Date: ");
    Serial.print(_gps->day, DEC); Serial.print('/');
    Serial.print(_gps->month, DEC); Serial.print("/20");
    Serial.println(_gps->year, DEC);
    Serial.print("Fix: "); Serial.print((int)_gps->fix);
    Serial.print(", Quality: "); Serial.println((int)_gps->fixquality);
    if (_gps->fix) {
      //this->_gsl->mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/milliseconds", (double)_gps->milliseconds);
      //this->_gsl->mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/fix", (double)_gps->fix);
      Serial.print("Location: ");
      Serial.print(_gps->latitude, 4); Serial.print(_gps->lat);
      //this._gsl.mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/latitude", (double)_gps->latitude);
      Serial.print(", ");
      Serial.print(_gps->longitude, 4); Serial.println(_gps->lon);
      //this._gsl.mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/longitude", (double)_gps->longitude);

      Serial.print("Speed (knots): "); Serial.println(_gps->speed);
      //this._gsl.mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/speed", (double)_gps->speed);
      Serial.print("Angle: "); Serial.println(_gps->angle);
      //this._gsl.mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/angle", (double)_gps->angle);
      Serial.print("Altitude: "); Serial.println(_gps->altitude);
      //this._gsl.mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/altitude", (double)_gps->altitude);
      Serial.print("Satellites: "); Serial.println((int)_gps->satellites);
      //this._gsl.mqtt().publishDouble("/654baff5-cd72-472a-859a-925afe5056f3/transprotobot/sil/gps/satellites", (double)_gps->satellites);
    }
  } */
}
