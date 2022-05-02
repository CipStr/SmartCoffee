#ifndef __RUNNING_TASK__
#define __RUNNING_TASK__

#include "Task.h"
#include "ButtonImpl.h"
#include "Pot.h"
#include "Utils.h"


class RunningTask: public Task {
    enum{
        BOOTING,
        IDLE, 
        CHECKING, 
        SUGAR,
    } state;

  public:
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
