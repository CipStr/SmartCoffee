#include <Arduino.h>
#include "Task.h"
#include "MakingTask.h"
#include "RunningTask.h"
#include "AssistanceTask.h"
#include "MessageTask.h"
#include "Scheduler.h"
#include "ButtonImpl.h"
#include "Pot.h"
#include "Utils.h"
#include "ServoMotorImpl.h"
#include "Sonar.h"
#include "Pir.h"
#include "TemperatureSensor.h"

#define BUP 5
#define BDOWN 3
#define BMAKE 4
#define POT A0
#define SERVO_PIN 9

Scheduler scheduler;
Button* buttonUP;
Button* buttonDOWN;
Button* buttonMAKE;
Pot* sugarPot;
ServoMotor* servo;
Sonar* sonar;
Pir* pir;
TemperatureSensor* temperatureSensor;


void setup() {
  buttonUP = new ButtonImpl(BUP);
  buttonDOWN = new ButtonImpl(BDOWN);
  buttonMAKE = new ButtonImpl(BMAKE);
  sugarPot = new Pot();
  servo = new ServoMotorImpl(SERVO_PIN);
  sonar = new Sonar();
  pir = new Pir();
  temperatureSensor = new TemperatureSensor();
  singleton.lcd.init();
  singleton.lcd.backlight();
  Serial.begin(9600);
  scheduler.init(100);
  MessageTask* messageTask = new MessageTask();
  messageTask->init(100);
  MakingTask* makingTask = new MakingTask();
  makingTask->init(100,servo,sonar);
  AssistanceTask* assistanceTask = new AssistanceTask();
  assistanceTask->init(100,servo,temperatureSensor);
  RunningTask* running = new RunningTask();

  running->setActive(true);
  running->init(100, buttonUP, buttonDOWN, buttonMAKE, sugarPot, pir);
  running->addMakingTask(makingTask);
  running->addAssistanceTask(assistanceTask);
  running->addMessageTask(messageTask);
  makingTask->addRunningTask(running);
  assistanceTask->addTasks(running,messageTask);
  messageTask->addTasks(running,assistanceTask,makingTask);
  messageTask->setActive(false); 
  scheduler.addTask(running);
  scheduler.addTask(makingTask);
  scheduler.addTask(assistanceTask);
  scheduler.addTask(messageTask);
}

void loop() {
  scheduler.schedule();
  //Serial.println("loop");
  //Serial.println("YOLO");
}