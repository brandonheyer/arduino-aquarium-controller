#include <Arduino.h>
#include <LiquidCrystal.h>

#include "library/Adafruit_PWMServoDriver.h"

#include "LedControlMenu.h"
#include "RGBLedControlMenu.h"
#include "LedController.h"

RGBLedControlMenu::RGBLedControlMenu (
  LiquidCrystal* lcd,
  Adafruit_PWMServoDriver* pwm,
  int rPin,
  int gPin,
  int bPin,
  String l = ""
) : LedControlMenu(lcd, pwm, -1, l) {
  rlc = new LedController(rPin, pwm);
  glc = new LedController(gPin, pwm);
  blc = new LedController(bPin, pwm);

  active = 0;

  // brightness = lc->getBrightness();
}


void RGBLedControlMenu::draw() {
  display->setCursor(0, 0);
  display->print(" Red | Grn| Blue");

  display->setCursor(1, 1);
  display->print(rlc->getFadeTarget());

  display->setCursor(6, 1);
  display->print(glc->getFadeTarget());

  display->setCursor(12, 1);
  display->print(blc->getFadeTarget());

  if (active == 0) {
    display->setCursor(0, 0);
  } else if (active == 1) {
    display->setCursor(6, 0);
  } else {
    display->setCursor(11, 0);
  }

  display->print(">");
}

void RGBLedControlMenu::tick(int delta) {
  rlc->tick(delta);
  glc->tick(delta);
  blc->tick(delta);
}

bool RGBLedControlMenu::handleRemote(unsigned long value) {
  int val;
  int rVal;
  int gVal;
  int bVal;

  float rgRatio;
  float rbRatio;
  float grRatio;
  float gbRatio;
  float brRatio;
  float bgRatio;

  bool lcChange = false;
  bool valChange = false;

  val = alc->getBrightness();

  switch(value) {
    // Right
    case 0xFFC23D:
      active++;
      lcChange = true;
      break;

    case 0xFF22DD:
      active--;
      lcChange = true;
      break;

    case 0xFFE01F:
      if (val > 0) {
        val -= 5;
        valChange = true;
      }
      break;

    case 0xFF906F:
      if (val < 256) {
        val += 5;
        valChange = true;
      }
      break;

    case 0xFF6897:
      rVal = rlc->getBrightness();
      gVal = glc->getBrightness();
      bVal = blc->getBrightness();

      rbRatio = float(bVal) / float(rVal);
      rgRatio = float(gVal) / float(rVal);
      gbRatio = float(bVal) / float(gVal);
      grRatio = float(rVal) / float(gVal);
      bgRatio = float(gVal) / float(bVal);
      brRatio = float(rVal) / float(bVal);

      if (rVal > gVal && rVal > bVal) {
        rVal += 5;
        gVal = rgRatio * rVal;
        bVal = rbRatio * rVal;
      } else if (rVal < gVal) {
        gVal += 5;
        rVal = grRatio * gVal;
        bVal = gbRatio * gVal;
      } else {
        bVal += 5;
        gVal = bgRatio * bVal;
        rVal = brRatio * bVal;
      }

      rlc->fade(rVal);
      glc->fade(gVal);
      blc->fade(bVal);
      return true;

    case 0xFF30CF:
      rVal = rlc->getBrightness();
      gVal = glc->getBrightness();
      bVal = blc->getBrightness();

      rbRatio = float(bVal) / float(rVal);
      rgRatio = float(gVal) / float(rVal);
      gbRatio = float(bVal) / float(gVal);
      grRatio = float(rVal) / float(gVal);
      bgRatio = float(gVal) / float(bVal);
      brRatio = float(rVal) / float(bVal);

      if (rVal > gVal && rVal > bVal) {
        rVal -= 5;
        gVal = rgRatio * rVal;
        bVal = rbRatio * rVal;
      } else if (rVal < gVal) {
        gVal -= 5;
        rVal = grRatio * gVal;
        bVal = gbRatio * gVal;
      } else {
        bVal -= 5;
        gVal = bgRatio * bVal;
        rVal = brRatio * bVal;
      }

      rlc->fade(rVal);
      glc->fade(gVal);
      blc->fade(bVal);
      return true;
      return true;

    default:
      return false;
  }

  if (valChange) {
    if (val > 255) {
      val = 255;
    } else if (val < 0) {
      val = 0;
    }

    alc->fade(val);
  }

  if (lcChange) {
    if (active < 0) {
      active += 3;
    } else {
      active = active % 3;
    }

    if (active == 0) {
      alc = rlc;
    } else if (active == 1) {
      alc = glc;
    } else {
      alc = blc;
    }
  }

  return true;
}
