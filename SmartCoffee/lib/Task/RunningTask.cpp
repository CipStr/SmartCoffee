#include "Task.h"
#include "MakingTask.h"
#include "RunningTask.h"
#include <Arduino.h>
#include "ButtonImpl.h"
#include "Utils.h"

#define NMAX 10
#define TIDLE 5000
#define TBOOTING 10000
MakingTask* makingTask;

RunningTask::RunningTask(){
}

void RunningTask::addMakingTask(MakingTask* task){
  makingTask = task;
  makingTask->setActive(false);
}
void RunningTask::init(int period,Button* buttonUP,Button* buttonDOWN,Button* buttonMAKE,Pot* sugarPot, Pir* pir) {
  Task::init(period);
  selectedCoffeeType=0;
  this->buttonUP = buttonUP;
  this->buttonDOWN = buttonDOWN;
  this->buttonMAKE = buttonMAKE;
  this->sugarPot = sugarPot;
  this->pir = pir;
  state = BOOTING;
  readyFlag=true;
  detectedStatus=false;
  sugar=0;
  for(int i=0;i<3;i++) {
    coffeeType_array[i] = 0;
  }
}

void RunningTask::resetState(){
  this->setActive(true);
  timer.startTimer();
  pirTimer.startTimer();
  state = IDLE;
  readyFlag=true;
}

void RunningTask::tick() {
  switch (state) {
    case BOOTING:
      singleton.lcd.setCursor(0,0);
      singleton.lcd.print("Booting...");
      if(!pirTimer.isStarted()){
        pirTimer.startTimer();
      }
      for(int i=0;i<3;i++) {
        coffeeType_array[i] = NMAX ;
      }
      if(pirTimer.checkExpired(TBOOTING)){
        pirTimer.startTimer();
        state = IDLE;
      }
      break;
    case CHECKING:
      break;
    case SLEEP:
      singleton.lcd.clear();
      singleton.lcd.setCursor(0,0);
      singleton.lcd.print("Sleeping...");
      if(pir->getStatus()){
        pirTimer.startTimer();
        state = IDLE;
      }
      break;
    case IDLE:
      checkMovement();
      sugar=sugarPot->getValue(0,9);
      singleton.lcd.setCursor(3,2);
      singleton.lcd.print(" Sugar level: ");
      singleton.lcd.print(sugar);
      msgChecking();
      if(readyFlag) {
        singleton.lcd.clear();
        singleton.lcd.setCursor(2,1);
        singleton.lcd.print("Ready!");
        readyFlag=false;
      }
      if(buttonUP->isPressed()) {
        if(selectedCoffeeType>=2) {
          selectedCoffeeType=0;
        }
        else {
          selectedCoffeeType++;
        }
        timer.startTimer();
        singleton.lcd.clear();
        singleton.lcd.setCursor(0,0);
        singleton.lcd.print("Selected coffee type:");
        singleton.lcd.print(selectedCoffeeType+1);
        singleton.lcd.print(" Sugar level: ");
        singleton.lcd.print(sugar);
      }
      if(buttonDOWN->isPressed()) {
        if(selectedCoffeeType<1) {
          selectedCoffeeType=2;
        }
        else {
          selectedCoffeeType--;
        }
        timer.startTimer();
        singleton.lcd.clear();
        singleton.lcd.setCursor(0,0);
        singleton.lcd.print("Selected coffee type:");
        singleton.lcd.print(selectedCoffeeType+1);
        singleton.lcd.print(" Sugar level: ");
        singleton.lcd.print(sugar);
      }
      if(buttonMAKE->isPressed()) {
        if(coffeeType_array[selectedCoffeeType]>0) {
          coffeeType_array[selectedCoffeeType]--;
          singleton.lcd.clear();
          singleton.lcd.print("Coffee type available");
          state=MAKE;
        }
        else {
          singleton.lcd.clear();
          singleton.lcd.print("Coffee type not available");
        }
      }
      break;
    case MAKE:
      makingTask->setBeverage(selectedCoffeeType);
      makingTask->resetState();
      this->setActive(false);
      break;
    }
}


void RunningTask::msgChecking() {
  if(timer.checkExpired(5000)) {
    readyFlag=true;
  }
}

void RunningTask::checkMovement() {
  int current = pir->getStatus();
  Serial.println(pirTimer.isStarted());
  Serial.println(current);
  if (current==0) {
    if(pirTimer.checkExpired(TIDLE)) {
      state = SLEEP;
    }
  }
  else {
    pirTimer.startTimer();
  }
}

