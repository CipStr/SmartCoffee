#include "MakingTask.h"
#include "Utils.h"
#include <Arduino.h>
#include <ServoTimer2.h>
#define delta 9

RunningTask* running;

MakingTask::MakingTask(){    
  
}

void MakingTask::init(int period, ServoMotor* servo,Sonar* sonar){
  Task::init(period);
  position = 0;
  this->servo = servo;
  this->sonar = sonar;
  this->sonar->init();
  this->servo->on();
  this->servo->setPosition(0);
  state = MAKING;    
}

void MakingTask::addRunningTask(RunningTask* runningTask){
  running = runningTask;
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
          checkMovement();
          singleton.lcd.setCursor(0,0);
          singleton.lcd.clear();
          singleton.lcd.print("Making a ");
          singleton.lcd.print(beverage+1);
          singleton.lcd.print("...");
        break;
        case READY:
          singleton.lcd.setCursor(0,0);
          singleton.lcd.clear();
          singleton.lcd.print("The ");
          singleton.lcd.print(beverage+1);
          singleton.lcd.print(" is ready!");
          timeoutOrRemoved();
        break;
  }
}

void MakingTask::resetState(){
  this->setActive(true);
  position = 0;
  state = MAKING;
}

void MakingTask::checkMovement() {
  if(timer.checkExpired(500)) {
    if(position<180) {
      servo->setPosition(position);
      position += delta;
      timer.startTimer();
    }
    else {
      timer.startTimer();
      state = READY;
    }
  }
}
void MakingTask::timeoutOrRemoved(){
  if(timer.checkExpired(5000) || sonar->getDistance()>0.40){
    singleton.lcd.setCursor(0,0);
    singleton.lcd.clear();
    singleton.lcd.print("Coffee removed!");
    servo->setPosition(0);
    running->resetState();
    this->setActive(false);
  }
}