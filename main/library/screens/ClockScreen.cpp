#include <LiquidCrystal.h>

#include "../menu.h"
#include "../Clock.h"

#include "ClockScreen.h"

ClockScreen::ClockScreen(
  LiquidCrystal* lcd,
  String l = ""
) : Menu(l, false) {
  display = lcd;
}

void ClockScreen::draw() {
  Clock::drawDate(0, 0, display);
  Clock::drawTime(0, 1, display);
}

void ClockScreen::tick(int delta) {
  lastUpdate += delta;

  if (lastUpdate > 250) {
    draw();
    lastUpdate = 0;
  }
}

bool ClockScreen::handleRemote(unsigned long value) {
  return false;
}
