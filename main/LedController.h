#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>
#include "library/Adafruit_PWMServoDriver.h"

class LedController {
  public:
    LedController(int p, Adafruit_PWMServoDriver* pwm);
    void demo();
    void off();
    void tick(int delta);

    int getBrightness();
    int getFadeTarget();

    void setBrightness(bool save = true);
    void setBrightness(int b, bool save = true);

    void fade();
    void fade(int t);

  private:
    unsigned long last;

    int pin;
    int brightness;
    int target;

    bool direction;

    Adafruit_PWMServoDriver* driver;
};

#endif
