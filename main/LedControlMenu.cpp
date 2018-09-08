#include <Arduino.h>
#include <LiquidCrystal.h>

#include "library/Adafruit_PWMServoDriver.h"
#include "library/menu.h"

#include "LedControlMenu.h"
#include "LedController.h"

LedControlMenu::LedControlMenu(
  LiquidCrystal* lcd,
  Adafruit_PWMServoDriver* pwm,
  int pin,
  String l = ""
) : Menu(l, false) {
  display = lcd;

  if (pin != -1) {
    lc = new LedController(pin, pwm);
    brightness = lc->getBrightness();
  }
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

  progress((brightness * 100) / 255, bar);

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

void LedControlMenu::tick(int delta) {
  lc->tick(delta);
}

bool LedControlMenu::handleRemote(unsigned long value) {
  switch(value) {
    case 0xFFE01F:
      if (brightness > 0) {
        brightness -= 10;
      }
      break;

    case 0xFF906F:
      if (brightness < 256) {
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

  lc->fade(brightness);

  return true;
}
