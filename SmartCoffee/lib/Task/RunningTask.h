#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "MakingTask.h"
#include "ButtonImpl.h"
#include "Pot.h"
#include "Utils.h"
class MakingTask;

class RunningTask: public Task {
 
    enum{
        BOOTING,
        IDLE, 
        CHECKING, 
        MAKE,
    } state;

  public:
    RunningTask();
    void init(int period,Button* buttonUP,Button* buttonDOWN,Button* buttonMAKE,Pot* sugarPot);
    void tick();
    void addMakingTask(MakingTask* makingTask);
    void resetState();

  private:
    int coffeeType_array[3];
    Button* buttonUP;
    Button* buttonDOWN;
    Button* buttonMAKE;
    Pot* sugarPot;
    int selectedCoffeeType;
    void msgChecking();
    CustomTimer timer;
    bool readyFlag;
    int sugar;
};
#endif
