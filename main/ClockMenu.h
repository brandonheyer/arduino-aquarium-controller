#ifndef CLOCKMENU_H
#define CLOCKMENU_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "library/menu.h"

class ClockMenu : public Menu {
  public:
    ClockMenu(
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
