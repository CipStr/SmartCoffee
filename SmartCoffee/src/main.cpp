#include <Arduino.h>
#include <Task.h>
#include <RunningTask.h>
#include <Scheduler.h>
#include <ButtonImpl.h>
#include <Pot.h>

#define BUP 2
#define BDOWN 3
#define BMAKE 4
#define POT A0

Scheduler scheduler;
Button* buttonUP;
Button* buttonDOWN;
Button* buttonMAKE;
Pot* sugarPot;


void setup() {
  buttonUP = new ButtonImpl(BUP);
  buttonDOWN = new ButtonImpl(BDOWN);
  buttonMAKE = new ButtonImpl(BMAKE);
  sugarPot = new Pot();
  Serial.begin(9600);
  Serial.println("Starting...");
  scheduler.init(100);
  RunningTask* running = new RunningTask();
  running->init(100, buttonUP, buttonDOWN, buttonMAKE, sugarPot);
  scheduler.addTask(running);
}

void loop() {
  scheduler.schedule();
  // put your main code here, to run repeatedly:
}