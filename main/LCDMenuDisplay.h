#ifndef LCDMENUDISPLAY_H
#define LCDMENUDISPLAY_H

#include <LiquidCrystal.h>
#include "library/menu.h"

class LCDMenuDisplay {
  public:
    LCDMenuDisplay(Menu* m);

    void drawNavigation();
    void drawMenu();
    void clear();
    void draw();
    void redraw();
    void tick(int delta);

    bool handleRemote(unsigned long value);

    bool enterMenu();
    bool leaveMenu();
    bool navigateUp();
    bool navigateDown();
    bool siblingMenu();

    LiquidCrystal* getLiquidCrystal();

    int currMenuItem;

  private:
    Menu* activeMenu;
    LiquidCrystal* lcd;
    Menu* menu;

    int timeout;
};

#endif
