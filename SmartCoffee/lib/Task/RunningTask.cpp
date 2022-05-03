#include "Task.h"
#include "MakingTask.h"
#include "RunningTask.h"
#include <Arduino.h>
#include "ButtonImpl.h"
#include "Utils.h"

#define NMAX 10

RunningTask::RunningTask(MakingTask* task){
  taskToBeControlled = task;
  taskToBeControlled->init(100);
  taskToBeControlled->setActive(false);
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

void RunningTask::tick() {
  switch (state) {
    case BOOTING:
      Serial.println("Booting...The smart coffee machine is ready!");
      //delay(5000);
      for(int i=0;i<3;i++) {
        coffeeType_array[i] = NMAX ;
      }
      Serial.println("I just filled the coffee machine with 10 cups of coffee for each type!");
      Serial.println("Coffee type: 1. Latte 2. Espresso 3. Cappuccino");
      state=IDLE;
      break;
    case CHECKING:
      break;
    case IDLE:
      sugar=sugarPot->getValue(0,10);
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
          Serial.println("Coffee type available");
          Serial.println("Select the amount of sugar to add:");
          state=MAKE;
        }
        else {
          Serial.println("Coffee type not available");
        }
      }
      break;
    case MAKE:
      Serial.println("Make");
      taskToBeControlled->setActive(true);
      taskToBeControlled->setBeverage(selectedCoffeeType);
      this->setActive(false);
      break;
    }
}

void RunningTask::msgChecking() {
  if(timer.checkExpired(5000)) {
    readyFlag=true;
  }
}

