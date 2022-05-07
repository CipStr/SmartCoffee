#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "MakingTask.h"
#include "ButtonImpl.h"
#include "Pot.h"
#include "Utils.h"
#include "Pir.h"
class MakingTask;

class RunningTask: public Task {
 
    enum{
        BOOTING,
        IDLE, 
        CHECKING, 
        MAKE,
        SLEEP,
    } state;

  public:
    RunningTask();
    void init(int period,Button* buttonUP,Button* buttonDOWN,Button* buttonMAKE,Pot* sugarPot, Pir* pir);
    void tick();
    void addMakingTask(MakingTask* makingTask);
    void resetState();
    void checkMovement();

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
