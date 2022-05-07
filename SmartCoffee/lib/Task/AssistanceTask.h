#ifndef __ASSISTANCETASK__
#define __ASSISTANCETASK__

#include "Task.h"
#include "Utils.h"
#include "RunningTask.h"

class RunningTask;

class AssistanceTask: public Task {

  enum {CHECK,ASSISTANCE} state;

public:

  AssistanceTask();  
  void init(int period, ServoMotor* servo);
  void tick();
  void addRunningTask(RunningTask* runningTask);
  void resetState();
  void checkMotor();
  
private:
  ServoMotor* servo;
  CustomTimer timer;
  int position;
  bool direction;
  bool motorChecked;
};
#endif  