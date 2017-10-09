#include <Arduino.h>

#include "menu.h"

Menu::Menu(String l) {
  label = l;
  numItems = 0;
  isMenu = true;
}

Menu::Menu(String l, bool isM) {
  label = l;
  numItems = 0;
  isMenu = isM;
}

void Menu::addItem(Menu *item) {
  items[numItems] = item;
  item->parent = this;
  numItems++;
}

Menu* Menu::getItem(int index) {
  if (index < numItems) {
    return items[index];
  }

  return 0;
}

void Menu::draw() {

}

bool Menu::handleRemote(unsigned long  value) {
  return false;
}
