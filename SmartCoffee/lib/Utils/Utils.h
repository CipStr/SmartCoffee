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

class PCI {

  public:
    PCI(const PCI &) = delete;
    PCI &operator=(const PCI &) = delete;
    static PCI &getInstance();
    LiquidCrystal_I2C lcd;

  private:
    PCI() : lcd(0x27,20,4) {}

};

extern PCI &singleton;

#endif