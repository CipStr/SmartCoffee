#include "AssistanceTask.h"
#include "Utils.h"
#include <Arduino.h>
#include <ServoTimer2.h>
#include "TemperatureSensor.h"
#define delta 10
#define TCHECK 180000
#define TTEMP 10000

RunningTask* run;
AssistanceTask::AssistanceTask(){    

}

void AssistanceTask::init(int period, ServoMotor* servo, TemperatureSensor* temperatureSensor){
  Task::init(period);
  this->servo = servo;
  this->temperatureSensor = temperatureSensor;
  direction = true;
  motorChecked = false;
  position = 0;
  state=CHECK;
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
                    tempTimer.startTimer();
                    state=TEMP;
                }
            }
        break;
        case TEMP:
            if(tempTimer.checkExpired(TTEMP)){
                double temp=temperatureSensor->getTemperature();
                if(temp>25 || temp<17){
                    Serial.println("Temperature is not ok");
                    run->setActive(false);
                    state=ASSISTANCE;
                }
                else{
                    Serial.println("Temperature is ok");
                    direction = true;
                    motorChecked = false;
                    timer.startTimer();
                    state=CHECK;
                }
            }
            
        break;
        case ASSISTANCE:
            singleton.lcd.clear();
            singleton.lcd.setCursor(0,0);
            singleton.lcd.print("Assistance is required");
        break;
  }
}
void AssistanceTask::goToAssistance(){
  run->setActive(false);
  state=ASSISTANCE;
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
        }
    }   
}