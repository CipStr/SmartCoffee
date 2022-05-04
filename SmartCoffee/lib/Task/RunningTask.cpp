#include "Task.h"
#include "MakingTask.h"
#include "RunningTask.h"
#include <Arduino.h>
#include "ButtonImpl.h"
#include "Utils.h"

#define NMAX 10
MakingTask* makingTask;

RunningTask::RunningTask(){
}

void RunningTask::addMakingTask(MakingTask* task){
  makingTask = task;
  makingTask->setActive(false);
}
void RunningTask::init(int period,Button* buttonUP,Button* buttonDOWN,Button* buttonMAKE,Pot* sugarPot) {
  Task::init(period);
  selectedCoffeeType=0;
  this->buttonUP = buttonUP;
  this->buttonDOWN = buttonDOWN;
  this->buttonMAKE = buttonMAKE;
  this->sugarPot = sugarPot;
  state = BOOTING;
  readyFlag=true;
  sugar=0;
  for(int i=0;i<3;i++) {
    coffeeType_array[i] = 0;
  }
}

void RunningTask::resetState(){
  state = IDLE;
  readyFlag=true;
}

void RunningTask::tick() {
  switch (state) {
    case BOOTING:
      singleton.lcd.setCursor(0,0);
      singleton.lcd.print("Booting...");
      //delay(5000);
      for(int i=0;i<3;i++) {
        coffeeType_array[i] = NMAX ;
      }
      singleton.lcd.clear();
      singleton.lcd.print("I just refilled the coffee machine");
      singleton.lcd.print("Coffee type: 1. Latte 2. Espresso 3. Cappuccino");
      state=IDLE;
      break;
    case CHECKING:
      break;
    case IDLE:
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
        if(selectedCoffeeType>2) {
          selectedCoffeeType=1;
        }
        else {
          selectedCoffeeType++;
        }
        timer.startTimer();
        singleton.lcd.clear();
        singleton.lcd.setCursor(0,0);
        singleton.lcd.print("Selected coffee type:");
        singleton.lcd.print(selectedCoffeeType);
        singleton.lcd.print(" Sugar level: ");
        singleton.lcd.print(sugar);
      }
      if(buttonDOWN->isPressed()) {
        if(selectedCoffeeType<=1) {
          selectedCoffeeType=3;
        }
        else {
          selectedCoffeeType--;
        }
        timer.startTimer();
        singleton.lcd.clear();
        singleton.lcd.setCursor(0,0);
        singleton.lcd.print("Selected coffee type:");
        singleton.lcd.print(selectedCoffeeType);
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
      makingTask->setActive(true);
      makingTask->setBeverage(selectedCoffeeType);
      this->setActive(false);
      break;
    }
}

void RunningTask::msgChecking() {
  if(timer.checkExpired(5000)) {
    readyFlag=true;
  }
}

