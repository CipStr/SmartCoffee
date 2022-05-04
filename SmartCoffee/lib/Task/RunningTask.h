#ifndef __RUNNINGTASK__
#define __RUNNINGTASK__

#include "Task.h"
#include "ButtonImpl.h"
#include "MakingTask.h"
#include "Pot.h"
#include "Utils.h"


class RunningTask: public Task {
  MakingTask* taskToBeControlled;

    enum{
        BOOTING,
        IDLE, 
        CHECKING, 
        MAKE,
    } state;

  public:
    RunningTask(MakingTask* taskToBeControlled);
    void init(int period,Button* buttonUP,Button* buttonDOWN,Button* buttonMAKE,Pot* sugarPot);
    void tick();

  private:
    int coffeeType_array[3];
    Button* buttonUP;
    Button* buttonDOWN;
    Button* buttonMAKE;
    Pot* sugarPot;
    int selectedCoffeeType;
    void msgChecking();
    timer timer;
    bool readyFlag;
    int sugar;
};
#endif
