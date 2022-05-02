#include "Pot.h"
#include <Arduino.h>
#define POT A0

Pot::Pot(){
}

int Pot::getValue(int low, int high){
  return map(analogRead(POT), 0, 1023, low, high);
}