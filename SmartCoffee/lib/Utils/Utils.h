#ifndef UTILS_H
#define UTILS_H
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class timer{
    private:
       unsigned long initialTime;
       public:
       timer(); //constructor
       void startTimer();
       bool checkExpired(int t);
};
class lcd{
    private:
         LiquidCrystal_I2C display = LiquidCrystal_I2C(0x27,20,4);
    public:
    lcd(); //constructor
    void printMsg(char* msg);
    void clear();
};
#endif