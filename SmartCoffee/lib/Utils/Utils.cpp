#include "utils.h"
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <string.h>

timer::timer() {
}
void timer::startTimer() {
  initialTime = millis();
}
bool timer::checkExpired(int t) {
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
