#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H
#include <Arduino.h>
class NetworkService {
  
  private:
    const char* ssid = "mesmonet1";
    const char* password = "123getup";
    
  public:
    NetworkService();
    void on();
    void off();
};
#endif
