#ifndef LCDMENUDISPLAY_H
#define LCDMENUDISPLAY_H

#include <LiquidCrystal.h>
#include "menu.h"

class LCDMenuDisplay {
  public:
    LCDMenuDisplay(Menu* m);

    void drawNavigation();
    void drawMenu();
    void clear();
    void draw();
    void redraw();

    bool handleRemote(unsigned long value);

    bool enterMenu();
    bool leaveMenu();
    bool navigateUp();
    bool navigateDown();

    LiquidCrystal* getLiquidCrystal();

    int currMenuItem;

  private:
    Menu* activeMenu;
    LiquidCrystal* lcd;
    Menu* menu;
};

#endif
