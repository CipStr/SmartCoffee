#ifndef __MESSAGETASK__
#define __MESSAGETASK__

#include "Task.h"
#include "Utils.h"
#include "MakingTask.h"
#include "AssistanceTask.h"
#include "RunningTask.h"
class RunningTask;
class AssistanceTask;
class MakingTask;

class MessageTask: public Task {

  enum {MESSAGE} state;

public:

  MessageTask();  
  void init(int period);
  void tick();
  void addTasks(RunningTask* runningTask,AssistanceTask* assistanceTask,MakingTask* makingTask);
  void updateQuantity(int coffee,int tea,int chocolate);
  void updateState(String state);
  void updateCheckCount(int count);
  
private:
    int coffeeQauntity;
    int teaQuantity;
    int chocolateQuantity;
    String currentState;
    int checkCount;
    bool printFlag;
};

#endif