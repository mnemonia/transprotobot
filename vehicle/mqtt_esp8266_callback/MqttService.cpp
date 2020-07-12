#include "MqttService.h"

MqttService::MqttService()
{
  
}
void MqttService::handle(double x) {
  Serial.print("-----------------> Handle ");
  Serial.println(x);
  Serial.println("extHandle");
}
void MqttService::theCallback(double x) {
  Serial.print("Hey we're in a slider callback, the slider value is: ");
  Serial.println(x);
  Serial.println("extHandle");
}
