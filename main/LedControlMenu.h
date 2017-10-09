#ifndef LEDCONTROLMENU_H
#define LEDCONTROLMENU_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "menu.h"

class LedControlMenu : public Menu {
  public:
    LedControlMenu(LiquidCrystal* lcd, String l);

    void progress(int percent, char* bar);
    void drawIntensity();
    void drawLedStatus();
    void draw() override;

    bool handleRemote(unsigned long value) override;

  private:
    LiquidCrystal* display;

    int brightness;
};

#endif
