#ifndef RGBLEDCONTROLMENU_H
#define RGBLEDCONTROLMENU_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "library/Adafruit_PWMServoDriver.h"
#include "library/menu.h"

#include "LedController.h"
#include "LedControlMenu.h"

class RGBLedControlMenu : public LedControlMenu {
  public:
    RGBLedControlMenu(
      LiquidCrystal* lcd,
      Adafruit_PWMServoDriver* pwm,
      int rPin,
      int gPin,
      int bPin,
      String l
    );

    void draw() override;
    bool handleRemote(unsigned long value) override;
    void tick(int delta) override;

  protected:
    LedController* rlc;
    LedController* glc;
    LedController* blc;
    LedController* alc = rlc;

    int active = 0;
};

#endif
