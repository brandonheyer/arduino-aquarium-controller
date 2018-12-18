#ifndef CLOCK_SCREEN_H
#define CLOCK_SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "../library/menu.h"

class ClockScreen : public Menu {
  public:
    ClockScreen(
      LiquidCrystal* lcd,
      String l
    );

    virtual void draw() override;
    virtual void tick(int delta) override;
    virtual bool handleRemote(unsigned long value) override;

  protected:
    LiquidCrystal* display;

  private:
    int lastUpdate;
};

#endif
