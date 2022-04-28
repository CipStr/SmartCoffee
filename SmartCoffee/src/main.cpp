#include <Arduino.h>
#include <Task.h>
#include <RunningTask.h>
#include <Scheduler.h>

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(100);
  Task* running = new RunningTask();
  running->init(100);
  scheduler.addTask(running);
}

void loop() {
  scheduler.schedule();
  // put your main code here, to run repeatedly:
}