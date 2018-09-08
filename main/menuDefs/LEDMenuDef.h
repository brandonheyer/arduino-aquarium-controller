#ifndef LED_MENU_DEF_H
#define LED_MENU_DEF_H

#include "../library/Adafruit_PWMServoDriver.h"

#include "../library/menu.h"
#include "../LCDMenuDisplay.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

class LEDMenuDef {
  public:
    static void add(Menu* menu, LCDMenuDisplay* lcd) {
      Menu *menuSetup;
      Menu *subMenu;

      menuSetup = new Menu("LED Controls");
      menu->addItem(menuSetup);

      subMenu = new Menu("RGB 1");
      subMenu->addItem(
        new RGBLedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          3, 2, 1,
          "RGB 1"
        )
      );
      menuSetup->addItem(subMenu);

      subMenu = new Menu("White 1");
      subMenu->addItem(
        new LedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          0,
          "White 1"
        )
      );
      menuSetup->addItem(subMenu);

      subMenu = new Menu("White 2");
      subMenu->addItem(
        new LedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          1,
          "White 2"
        )
      );
      menuSetup->addItem(subMenu);

      subMenu = new Menu("White 3");
      subMenu->addItem(
        new LedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          2,
          "White 3"
        )
      );
      menuSetup->addItem(subMenu);

      subMenu = new Menu("White 4");
      subMenu->addItem(
        new LedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          3,
          "White 4"
        )
      );
      menuSetup->addItem(subMenu);

      subMenu = new Menu("Grow 1");
      subMenu->addItem(
        new LedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          4,
          "Grow 1"
        )
      );
      menuSetup->addItem(subMenu);

      subMenu = new Menu("Grow 2");
      subMenu->addItem(
        new LedControlMenu(
          lcd->getLiquidCrystal(),
          &pwm,
          5,
          "Grow 2"
        )
      );
      menuSetup->addItem(subMenu);
    }
};

#endif
