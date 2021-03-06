#include "Task.h"
#include "MakingTask.h"
#include "AssistanceTask.h"
#include "RunningTask.h"
#include "MessageTask.h"
#include <Arduino.h>
#include "./avr/sleep.h"
#include "./avr/power.h"
#include "ButtonImpl.h"
#include "Utils.h"

#define NMAX 3
#define TIDLE 60000
#define TBOOTING 10000
MakingTask* makingTask;
AssistanceTask* assistanceTask;
MessageTask* messageTask;

RunningTask::RunningTask(){
}

void wakeUp() {
  detachInterrupt(2);
}

void RunningTask::addMakingTask(MakingTask* task){
  makingTask = task;
  makingTask->setActive(false);
}

void RunningTask::addAssistanceTask(AssistanceTask* task){
  assistanceTask = task;
  assistanceTask->setActive(false);
}

void RunningTask::addMessageTask(MessageTask* task){
  messageTask = task;
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
  assistanceTask->resetState();
  assistanceTask->setActive(true);
  messageTask->updateState("IDLE");
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
        assistanceTask->setActive(true);
        messageTask->updateQuantity(coffeeType_array[0],coffeeType_array[1],coffeeType_array[2]);
        messageTask->updateState("IDLE");
        messageTask->setActive(true);
        state = IDLE;
      }
      break;
    case SLEEP:
      attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
      singleton.lcd.clear();
      singleton.lcd.setCursor(0,0);
      singleton.lcd.print("Sleeping...");
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
      sleep_enable();
      sleep_mode();
      sleep_disable();
      pirTimer.startTimer();
      assistanceTask->resetState();
      messageTask->updateState("IDLE");
      state = IDLE;
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
          messageTask->updateQuantity(coffeeType_array[0],coffeeType_array[1],coffeeType_array[2]);
          messageTask->updateState("MAKING");
          state=MAKE;
        }
        else {
          singleton.lcd.clear();
          singleton.lcd.print("Coffee type not available");
          if(coffeeType_array[0]==0 && coffeeType_array[1]==0 && coffeeType_array[2]==0) {
            assistanceTask->goToAssistance();
          }
        }
      }
      break;
    case MAKE:
      assistanceTask->setActive(false);
      makingTask->setBeverage(selectedCoffeeType);
      makingTask->resetState();
      this->setActive(false);
      break;
    }
}

void RunningTask::refill(){
  for(int i=0;i<3;i++) {
    coffeeType_array[i] = NMAX ;
  }
  messageTask->updateQuantity(coffeeType_array[0],coffeeType_array[1],coffeeType_array[2]);
}

void RunningTask::msgChecking() {
  if(timer.checkExpired(5000)) {
    readyFlag=true;
  }
}

void RunningTask::checkMovement() {
  int current = pir->getStatus();
  if (current==0) {
    if(pirTimer.checkExpired(TIDLE)) {
      assistanceTask->setActive(false);
      messageTask->updateState("SLEEP");
      state = SLEEP;
    }
  }
  else {
    pirTimer.startTimer();
  }
}

