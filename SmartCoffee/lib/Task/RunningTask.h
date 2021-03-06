#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "MakingTask.h"
#include "AssistanceTask.h"
#include "MessageTask.h"
#include "ButtonImpl.h"
#include "Pot.h"
#include "Utils.h"
#include "Pir.h"
class MakingTask;
class AssistanceTask;
class MessageTask;

class RunningTask: public Task {
 
    enum{
        BOOTING,
        IDLE,  
        MAKE,
        SLEEP,
    } state;

  public:
    RunningTask();
    void init(int period,Button* buttonUP,Button* buttonDOWN,Button* buttonMAKE,Pot* sugarPot, Pir* pir);
    void tick();
    void addMakingTask(MakingTask* makingTask);
    void addAssistanceTask(AssistanceTask* assistanceTask);
    void addMessageTask(MessageTask* messageTask);
    void resetState();
    void checkMovement();
    void refill();

  private:
    int coffeeType_array[3];
    Button* buttonUP;
    Button* buttonDOWN;
    Button* buttonMAKE;
    Pot* sugarPot;
    Pir* pir;
    int selectedCoffeeType;
    void msgChecking();
    CustomTimer timer;
    CustomTimer pirTimer; 
    bool readyFlag;
    int sugar;
    bool detectedStatus;
};
#endif
