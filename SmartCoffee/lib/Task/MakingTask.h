#ifndef __MAKINGTASK__
#define __MAKINGTASK__

#include "Task.h"
#include "ServoMotorImpl.h"
#include "Utils.h"
#include "Sonar.h"
#include "RunningTask.h"
class RunningTask;

class MakingTask: public Task {

  enum {MAKING,READY} state;

public:

  MakingTask();  
  void init(int period, ServoMotor* servo,Sonar* sonar);
  void setBeverage(int beverage);  
  void tick();
  void addRunningTask(RunningTask* runningTask);
  void resetState();
  
private:
  int beverage;
  ServoMotor* servo;
  Sonar* sonar;
  CustomTimer timer;
  void checkMovement();
  void timeoutOrRemoved();
  int position;
  float distance;
};

#endif
