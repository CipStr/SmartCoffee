#include <Arduino.h>
#include <Task.h>
#include <RunningTask.h>
#include <Scheduler.h>
#include <ButtonImpl.h>
#include <Pot.h>
#include <Utils.h>
#include <string.h>
#include <MakingTask.h>


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
  singleton.lcd.init();
  singleton.lcd.backlight();
  singleton.lcd.setCursor(2,1);
  singleton.lcd.print("Smart Coffee Machine");
  Serial.begin(9600);
  scheduler.init(100);
  MakingTask* makingTask = new MakingTask();
  RunningTask* running = new RunningTask(makingTask);
  running->setActive(true);
  running->init(100, buttonUP, buttonDOWN, buttonMAKE, sugarPot);
  scheduler.addTask(running);
  scheduler.addTask(makingTask);
}

void loop() {
  scheduler.schedule();
  // put your main code here, to run repeatedly:
}