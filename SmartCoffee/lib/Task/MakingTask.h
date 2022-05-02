#ifndef __MAKINGTASK__
#define __MAKINGTASK__

#include "Task.h"


class MakingTask: public Task {

  enum {MAKING} state;

public:

  MakingTask();  
  void init(int period);
  void setBeverage(int beverage);  
  void tick();
private:
  int beverage;
};

#endif
