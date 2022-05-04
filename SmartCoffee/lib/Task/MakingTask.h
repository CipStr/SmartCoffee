#ifndef __MAKINGTASK__
#define __MAKINGTASK__

#include "Task.h"
#include "ServoMotorImpl.h"
#include "Utils.h"
#include "Sonar.h"
#include "RunningTask.h"

class MakingTask: public Task {

  enum {MAKING,READY} state;

public:

  MakingTask();  
  void init(int period, ServoMotor* servo,Sonar* sonar);
  void setBeverage(int beverage);  
  void tick();
  
private:
  int beverage;
  ServoMotor* servo;
  Sonar* sonar;
  timer timer;
  void checkMovement();
  void timeoutOrRemoved();
  int position;
  float distance;
};

#endif
