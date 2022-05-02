#include "utils.h"

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