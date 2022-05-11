#ifndef __ASSISTANCETASK__
#define __ASSISTANCETASK__

#include "Task.h"
#include "Utils.h"
#include "RunningTask.h"
#include "MessageTask.h"
#include "ServoMotorImpl.h"
#include "TemperatureSensor.h"

class RunningTask;
class MessageTask;

class AssistanceTask: public Task {

  enum {CHECK,ASSISTANCE,TEMP} state;

public:

  AssistanceTask();  
  void init(int period, ServoMotor* servo, TemperatureSensor* temperatureSensor);
  void tick();
  void addTasks(RunningTask* runningTask,MessageTask* messageTask);
  void resetState();
  void checkMotor();
  void goToAssistance();
  void recover();
  void inputChecker();
  
private:
  ServoMotor* servo;
  CustomTimer timer;
  CustomTimer tempTimer;
  TemperatureSensor* temperatureSensor;
  int position;
  bool direction;
  bool motorChecked;
  int checkCount;
};
#endif  