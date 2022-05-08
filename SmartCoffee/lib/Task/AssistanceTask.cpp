#include "AssistanceTask.h"
#include "Utils.h"
#include <Arduino.h>
#include <ServoTimer2.h>
#define delta 10
#define TCHECK 180000

RunningTask* run;
AssistanceTask::AssistanceTask(){    

}

void AssistanceTask::init(int period, ServoMotor* servo){
  Task::init(period);
  this->servo = servo;
  direction = true;
  motorChecked = false;
  position = 0;
}

void AssistanceTask::addRunningTask(RunningTask* runningTask){
  run = runningTask;
}
void AssistanceTask::resetState(){
  this->setActive(true);
  position = 0;
  servo->setPosition(0);
  direction = true;
  motorChecked = false;
  state = CHECK;
}
void AssistanceTask::tick(){
    switch(state){
        case CHECK:
            if(!timer.isStarted()){
                timer.startTimer();
            }
            if(timer.checkExpired(TCHECK)){
                if(!motorChecked){
                    checkMotor();
                }
                else{
                    state = ASSISTANCE;
                }
            }
        break;
        case ASSISTANCE:
            motorChecked = false;
            state = CHECK;
        break;
  }
}
void AssistanceTask::checkMotor(){
    if(direction){
        servo->setPosition(position);
        position += delta;
        if(position > 180){
            direction = false;
        }
    }else{
        servo->setPosition(position);
        position -= delta;
        if(position < 0){
            direction = true;
            motorChecked = true;
            timer.startTimer();
        }
    }   
}