#include <LiquidCrystal.h>

#include "LCDMenuDisplay.h"
#include "menu.h"
#include "characters.h"

const int LCD_NUM_LINES = 2;
const char UP_ARROW = char(5);
const char DOWN_ARROW = char(6);

LCDMenuDisplay::LCDMenuDisplay(Menu* m) {
  menu = m;
  activeMenu = m;

  lcd = new LiquidCrystal(7, 8, 9, 10, 11, 12);

  currMenuItem = 0;

  lcd->begin(16, 2);
  lcd->createChar(1, lineOne);
  lcd->createChar(2, lineTwo);
  lcd->createChar(3, lineThree);
  lcd->createChar(4, lineFour);
  lcd->createChar(5, upArrow);
  lcd->createChar(6, dnArrow);
}

void LCDMenuDisplay::drawNavigation() {
  if (currMenuItem > 1) {
    lcd->setCursor(15, 0);
    lcd->print(UP_ARROW);
  }

  if (currMenuItem < activeMenu->numItems - ((activeMenu->numItems % 2) + 2) && activeMenu->numItems > LCD_NUM_LINES) {
    lcd->setCursor(15, 1);
    lcd->print(DOWN_ARROW);
  }
}

void LCDMenuDisplay::drawMenu() {
  int j = 0;
  int i;

  for (i = currMenuItem - (currMenuItem % LCD_NUM_LINES), j = 0; j < LCD_NUM_LINES && i < activeMenu->numItems; i++, j++) {
    lcd->setCursor(0, j);

    if (i == currMenuItem) {
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
  if (currMenuItem < activeMenu->numItems - 1) {
    currMenuItem++;

    return true;
  }

  return false;
}

bool LCDMenuDisplay::navigateDown() {
  if (currMenuItem > 0) {
    currMenuItem--;

    return true;
  }

  return false;
}

bool LCDMenuDisplay::enterMenu() {
  if (activeMenu->getItem(currMenuItem)->numItems) {
    activeMenu = activeMenu->getItem(currMenuItem);
    currMenuItem = 0;

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
    currMenuItem = 0;

    return true;
  }

  return false;
}

bool LCDMenuDisplay::handleRemote(unsigned long value) {
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
  }

  return false;
}

LiquidCrystal* LCDMenuDisplay::getLiquidCrystal() {
  return lcd;
}
