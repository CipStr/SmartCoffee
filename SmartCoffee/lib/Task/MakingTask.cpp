#include "MakingTask.h"
#include "Utils.h"
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
          singleton.lcd.print("Making a ");
          singleton.lcd.print(beverage);
        break;
  }
}