#include "MakingTask.h"
#include "Utils.h"
#include <Arduino.h>
#include <Servo.h>
#define SERVO_PIN 9
#define delta 9

MakingTask::MakingTask(){    
  
}

void MakingTask::init(int period, ServoMotor* servo,Sonar* sonar){
  Task::init(period);
  position = 0;
  this->servo = servo;
  this->sonar = sonar;
  this->sonar->init();
  //servo->on();
  //servo->setPosition(0);
  state = MAKING;    
}


void MakingTask::setBeverage(int beverage){
  this->beverage = beverage;
}

void MakingTask::tick(){
    switch(state){
        case MAKING:
          if(!timer.isStarted()){
            timer.startTimer();
          }
          //servo->setPosition(position);
          //position += delta;
          checkMovement();
          singleton.lcd.setCursor(0,0);
          singleton.lcd.clear();
          singleton.lcd.print("Making a ");
          singleton.lcd.print(beverage);
          singleton.lcd.print("...");
        break;
        case READY:
          if(!timer.isStarted()){
            timer.startTimer();
          }
          singleton.lcd.setCursor(0,0);
          singleton.lcd.clear();
          singleton.lcd.print("The ");
          singleton.lcd.print(beverage);
          singleton.lcd.print(" is ready!");
          timeoutOrRemoved();
        break;
  }
}
void MakingTask::checkMovement() {
  if(timer.checkExpired(500)) {
    if(position<180) {
      position += delta;
    }
    else {
      servo->setPosition(0);
      state = READY;
    }
    timer.startTimer();
  }
}
void MakingTask::timeoutOrRemoved(){
  if(timer.checkExpired(5000) || sonar->getDistance()>0.40){
    singleton.lcd.setCursor(0,0);
    singleton.lcd.clear();
    singleton.lcd.print("Coffee removed!");
    delay(5000);
    this->setActive(false);
  }
}