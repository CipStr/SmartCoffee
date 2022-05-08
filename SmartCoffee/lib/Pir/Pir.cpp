#include "Pir.h"
#include <Arduino.h>
#define PIR 2

Pir::Pir(){
    pinMode(PIR, INPUT);
}


int Pir::getStatus(){
  return digitalRead(PIR);
}