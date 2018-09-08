#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DS3232RTC.h>

#include "library/menu.h"
#include "ClockMenu.h"
#include "library/Clock.h"

ClockMenu::ClockMenu(
  LiquidCrystal* lcd,
  String l = ""
) : Menu(l, false) {
  display = lcd;
}

void ClockMenu::draw() {
  Clock::drawDate(0, 0, display);
  Clock::drawTime(0, 1, display);
}

void ClockMenu::tick(int delta) {
  lastUpdate += delta;

  if (lastUpdate > 250) {
    draw();
    lastUpdate = 0;
  }
}

bool ClockMenu::handleRemote(unsigned long value) {
  return false;
}
