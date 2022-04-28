#include "Task.h"
#include "RunningTask.h"
#define NMAX 10

void RunningTask::init(int period) {
  Task::init(period);
  state = BOOTING;
  for(int i=0;i<3;i++) {
    coffeeType_array[i] = 0;
  }
}

void RunningTask::tick() {
  switch (state) {
    case BOOTING:
      Serial.println("Booting...The smart coffee machine is ready!");
      millis(5000);
      for(int i=0;i<3;i++) {
        coffeeType_array[i] = NMAX ;
      }
      Serial.println("I just filled the coffee machine with 10 cups of coffee!");
      state=IDLE;
      break;
    case CHECKING:
      break;
    case IDLE:
      Serial.println("Idle...");
      break;
  }
}
