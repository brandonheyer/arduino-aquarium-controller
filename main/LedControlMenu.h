#ifndef LEDCONTROLMENU_H
#define LEDCONTROLMENU_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "library/Adafruit_PWMServoDriver.h"
#include "menu.h"

#include "LedController.h"

class LedControlMenu : public Menu {
  public:
    LedControlMenu(
      LiquidCrystal* lcd,
      Adafruit_PWMServoDriver* pwm,
      int pin,
      String l
    );

    virtual void draw() override;
    virtual bool handleRemote(unsigned long value) override;
    virtual void tick(int delta) override;

    void progress(int percent, char* bar);
    void drawIntensity();
    void drawLedStatus();

  protected:
    LiquidCrystal* display;
    LedController* lc;

    int brightness;
};

#endif
