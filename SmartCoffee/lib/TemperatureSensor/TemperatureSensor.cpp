#include "TemperatureSensor.h"
#include <Arduino.h>
#define TEMP A1

TemperatureSensor::TemperatureSensor(){
}


float TemperatureSensor::getTemperature(){
  int value=analogRead(TEMP);
  float mv = ( value/1024.0)*5000;
  float cel = mv/10;
  return cel;
}