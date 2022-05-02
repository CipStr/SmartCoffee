#include "MakingTask.h"
#include <Arduino.h>

MakingTask::MakingTask(){    
}
  
void MakingTask::init(int period){
  Task::init(period);
  state = MAKING;    
}

void MakingTask::setBeverage(int beverage){
  this->beverage = beverage;
}

void MakingTask::tick(){
    switch(state){
        case MAKING:
          Serial.println("Making a ");
          Serial.println(beverage);
        break;
  }
}