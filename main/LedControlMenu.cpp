#include <Arduino.h>
#include <LiquidCrystal.h>
#include "menu.h"
#include "LedControlMenu.h"

LedControlMenu::LedControlMenu(LiquidCrystal* lcd, String l = "") : Menu(l, false) {
  display = lcd;
  brightness = 120;
}

void LedControlMenu::progress(int percent, char* bar) {
  int i = 0;

  while (percent >= 10) {
      bar[i] = char(255);
      percent -= 10;
      i++;
  }

  if (percent > 0) {
    percent = percent / 2;
    bar[i] = char(percent);
    i++;
  }

  bar[i] = char(0);
}

void LedControlMenu::drawIntensity() {
  char bar[11];

  progress(((255 - brightness) * 100) / 255, bar);

  display->setCursor(0, 1);
  display->print(bar);
}

void LedControlMenu::drawLedStatus() {
  display->setCursor(0, 0);
  display->print(label);
}

void LedControlMenu::draw() {
  drawLedStatus();
  drawIntensity();
}

bool LedControlMenu::handleRemote(unsigned long value) {
  switch(value) {
    case 0xFF906F:
      if (brightness > 25) {
        brightness -= 10;
      }
      break;

    case 0xFFE01F:
      if (brightness < 255) {
        brightness += 10;
      }
      break;

    default:
      return false;
  }

  if (brightness > 255) {
    brightness = 255;
  } else if (brightness < 0) {
    brightness = 0;
  }

  analogWrite(3, brightness);

  return true;
}
