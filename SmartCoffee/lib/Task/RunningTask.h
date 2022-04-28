#ifndef __RUNNING_TASK__
#define __RUNNING_TASK__

#include "Task.h"

class RunningTask: public Task {
    enum{
        BOOTING,
        IDLE, 
        CHECKING, 
    } state;

  public:
    void init(int period);
    void tick();
    
  private:
    int coffeeType_array[3];
};
#endif
