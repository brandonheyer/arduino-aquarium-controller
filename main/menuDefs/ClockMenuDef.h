#ifndef CLOCK_MENU_DEF_H
#define CLOCK_MENU_DEF_H

#include "../library/menu.h"
#include "../LCDMenuDisplay.h"

#include "../library/screens/ClockScreen.h"

class ClockMenuDef {
  public:
    static void add(Menu* menu, LCDMenuDisplay* lcd) {
      Menu *menuSetup;

      menuSetup = new Menu("Clock");
      menu->addItem(menuSetup);

      menuSetup->addItem(
        new ClockScreen(
          lcd->getLiquidCrystal(),
          "Clock"
        )
      );
    }
};

#endif
