#include <LiquidCrystal.h>

#include "LCDMenuDisplay.h"
#include "library/menu.h"
#include "library/characters.h"

const int LCD_NUM_LINES = 2;

/**
 * PIN MAPPING FOR LCD MODULE
 */
const int PIN_BACKLIGHT = 24;
const int PIN_RS = 25;
const int PIN_E = 26;

const int PIN_D4 = 27;
const int PIN_D5 = 28;
const int PIN_D6 = 29;
const int PIN_D7 = 30;

const char UP_ARROW = char(5);
const char DOWN_ARROW = char(6);

LCDMenuDisplay::LCDMenuDisplay(Menu* m) {
  pinMode(PIN_BACKLIGHT, OUTPUT);
  digitalWrite(PIN_BACKLIGHT, HIGH);

  menu = m;
  activeMenu = m;

  lcd = new LiquidCrystal(
    PIN_RS,
    PIN_E,
    PIN_D4,
    PIN_D5,
    PIN_D6,
    PIN_D7
  );

  lcd->begin(16, 2);
  lcd->createChar(1, lineOne);
  lcd->createChar(2, lineTwo);
  lcd->createChar(3, lineThree);
  lcd->createChar(4, lineFour);
  lcd->createChar(5, upArrow);
  lcd->createChar(6, dnArrow);

  timeout = 0;
}

void LCDMenuDisplay::drawNavigation() {
  if (activeMenu->currMenuItem > 1) {
    lcd->setCursor(15, 0);
    lcd->print(UP_ARROW);
  }

  if (activeMenu->currMenuItem < activeMenu->numItems - ((activeMenu->numItems % 2) + 2) && activeMenu->numItems > LCD_NUM_LINES) {
    lcd->setCursor(15, 1);
    lcd->print(DOWN_ARROW);
  }
}

void LCDMenuDisplay::drawMenu() {
  int j = 0;
  int i;

  for (i = activeMenu->currMenuItem - (activeMenu->currMenuItem % LCD_NUM_LINES), j = 0; j < LCD_NUM_LINES && i < activeMenu->numItems; i++, j++) {
    lcd->setCursor(0, j);

    if (i == activeMenu->currMenuItem) {
      lcd->print('>');
    } else {
      lcd->print(' ');
    }

    lcd->print(activeMenu->getItem(i)->label);
  }
}

void LCDMenuDisplay::clear() {
  lcd->clear();
}

void LCDMenuDisplay::draw() {
  drawMenu();
  drawNavigation();
}

void LCDMenuDisplay::redraw() {
  clear();

  if (activeMenu->isMenu) {
    draw();
  } else {
    activeMenu->draw();
  }
}

bool LCDMenuDisplay::navigateUp() {
  if (activeMenu->currMenuItem < activeMenu->numItems - 1) {
    activeMenu->currMenuItem++;

    return true;
  }

  return false;
}

bool LCDMenuDisplay::navigateDown() {
  if (activeMenu->currMenuItem > 0) {
    activeMenu->currMenuItem--;

    return true;
  }

  return false;
}

bool LCDMenuDisplay::enterMenu() {
  if (activeMenu->getItem(activeMenu->currMenuItem)->numItems) {
    activeMenu = activeMenu->getItem(activeMenu->currMenuItem);

    if (activeMenu->numItems == 1 && !activeMenu->getItem(0)->isMenu) {
      activeMenu = activeMenu->getItem(0);
    }

    return true;
  }

  return false;
}

bool LCDMenuDisplay::leaveMenu() {
  if (!activeMenu->isMenu) {
    activeMenu = activeMenu->parent;
  }

  if (activeMenu->parent) {
    activeMenu = activeMenu->parent;

    return true;
  }

  return false;
}

bool LCDMenuDisplay::siblingMenu() {
  bool result = leaveMenu();

  if (result) {
    navigateUp() || (activeMenu->currMenuItem = 0);

    return enterMenu();
  }

  return false;
}

bool LCDMenuDisplay::handleRemote(unsigned long value) {
  lcd->display();
  timeout = 0;
  digitalWrite(PIN_BACKLIGHT, HIGH);

  if (activeMenu->handleRemote(value)) {
    return true;
  }

  switch(value) {
    case 0xFFE01F:
      return navigateUp();

    case 0xFF906F:
      return navigateDown();

    case 0xFF02FD:
      return enterMenu();

    case 0xFF9867:
      return leaveMenu();

    case 0xFFE21D:
      return siblingMenu();
  }

  return false;
}

void LCDMenuDisplay::tick(int delta) {
  timeout += delta;
  activeMenu->tick(delta);

  if (timeout > 10000) {
    lcd->noDisplay();
    digitalWrite(PIN_BACKLIGHT, LOW);
  }
}

LiquidCrystal* LCDMenuDisplay::getLiquidCrystal() {
  return lcd;
}
