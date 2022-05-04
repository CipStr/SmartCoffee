#include "utils.h"
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <string.h>

CustomTimer::CustomTimer() {
  initialTime = 0;
}
void CustomTimer::startTimer() {
  initialTime = millis();
}
bool CustomTimer::isStarted() {
  return initialTime != 0;
}
bool CustomTimer::checkExpired(int t) {
  if(millis() - initialTime >= t) {
    return true;
  }
  return false;
}

PCI & PCI::getInstance() {
  static PCI instance;
  return instance;
}

PCI &singleton {PCI::getInstance()};
