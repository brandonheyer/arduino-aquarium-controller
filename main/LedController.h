#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"

class LedController {
  public:
    LedController(int p, Adafruit_PWMServoDriver* pwm);
    void demo();
    void off();

  private:
    unsigned long last;

    int pin;
    int brightness;

    bool direction;

    Adafruit_PWMServoDriver* driver;
};

#endif
