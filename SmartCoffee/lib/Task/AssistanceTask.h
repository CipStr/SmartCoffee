#ifndef __ASSISTANCETASK__
#define __ASSISTANCETASK__

#include "Task.h"
#include "Utils.h"
#include "RunningTask.h"
#include "ServoMotorImpl.h"
#include "TemperatureSensor.h"

class RunningTask;

class AssistanceTask: public Task {

  enum {CHECK,ASSISTANCE,TEMP} state;

public:

  AssistanceTask();  
  void init(int period, ServoMotor* servo, TemperatureSensor* temperatureSensor);
  void tick();
  void addRunningTask(RunningTask* runningTask);
  void resetState();
  void checkMotor();
  void goToAssistance();
  
private:
  ServoMotor* servo;
  CustomTimer timer;
  CustomTimer tempTimer;
  TemperatureSensor* temperatureSensor;
  int position;
  bool direction;
  bool motorChecked;
};
#endif  