#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
class timer{
    private:
       unsigned long initialTime;
       public:
       timer(); //constructor
       void startTimer();
       bool checkExpired(int t);
};

#endif