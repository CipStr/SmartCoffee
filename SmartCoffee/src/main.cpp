#include <Arduino.h>
#include <Task.h>
#include <RunningTask.h>
#include <Scheduler.h>

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  scheduler.init(5000);
  Task* running = new RunningTask();
  running->init(100);
  scheduler.addTask(running);
}

void loop() {
  scheduler.schedule();
  // put your main code here, to run repeatedly:
}