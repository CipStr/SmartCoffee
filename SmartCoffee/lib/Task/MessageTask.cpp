#include "MessageTask.h"
#include "Utils.h"
#include <Arduino.h>


RunningTask* runner;
AssistanceTask* assist;
MakingTask* make;

MessageTask::MessageTask(){

}

void MessageTask::init(int period){
  Task::init(period);
  currentState="";
  coffeeQauntity=0;
  teaQuantity=0;
  chocolateQuantity=0;
  checkCount=0;
  printFlag=false;
  state=MESSAGE;
}

void MessageTask::addTasks(RunningTask* runningTask,AssistanceTask* assistanceTask,MakingTask* makingTask){
  runner = runningTask;
  assist = assistanceTask;
  make = makingTask;
}

void MessageTask::tick(){
    switch(state){
        case MESSAGE:
        if(printFlag){
            Serial.println("Machine State: " + currentState+" Check Count: "+String(checkCount)+" Coffee: "+String(coffeeQauntity)+" Tea: "+String(teaQuantity)+" Chocolate: "+String(chocolateQuantity));
            printFlag=false;
        }
        break;
    }
}

void MessageTask::updateQuantity(int coffee,int tea,int chocolate){
  coffeeQauntity=coffee;
  teaQuantity=tea;
  chocolateQuantity=chocolate;
  printFlag=true;
}

void MessageTask::updateState(String state){
  currentState=state;
  printFlag=true;
}

void MessageTask::updateCheckCount(int count){
  checkCount=count;
  printFlag=true;
}
