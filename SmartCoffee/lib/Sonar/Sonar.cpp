#include "Sonar.h"
#include <Arduino.h>
#define TRIG 7
#define ECHO 8

const float vs = 331.45 + 0.62*20; // speed of sound in cm/s

Sonar::Sonar(){
}

void Sonar::init(){
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

float Sonar::getDistance(){
  /* invio impulso */
    digitalWrite(TRIG,LOW);
    delayMicroseconds(3);
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIG,LOW);
    
    /* ricevi l’eco */
    float tUS = pulseIn(ECHO, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}