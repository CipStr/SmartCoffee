#include "TemperatureSensor.h"
#include <Arduino.h>
#define TEMP A1

TemperatureSensor::TemperatureSensor(){
}


double TemperatureSensor::getTemperature(){
  int value=analogRead(TEMP);
  int value_in_mV = 4.8876 * value; 

  /* value_in_C = value_in_mV / 10 (since we have 10 mV => 1 °C ) */

  double value_in_C = value_in_mV * 0.1;
  return value_in_C;
}