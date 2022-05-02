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

lcd::lcd() {
  display.init();                      // initialize the lcd
  display.backlight();
}
void lcd::printMsg(char* msg) {
  display.setCursor(2, 1);
  display.print(msg);
}
