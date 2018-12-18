#include <Arduino.h>
#include <EEPROM.h>

#include "library/Adafruit_PWMServoDriver.h"

#include "LedController.h"

const int FADE_TIMEOUT = 5;

LedController::LedController(int p, Adafruit_PWMServoDriver* pwm) {
  pin = p;
  direction = true;
  driver = pwm;
  target = -1;

  on();

  last = millis();
}

void LedController::demo() {
  if (millis() - last < FADE_TIMEOUT) {
    return;
  }

  if (direction) {
    brightness++;
  } else {
    brightness--;
  }

  if (brightness > 255) {
    brightness = 255;
    direction = false;
  } else if (brightness < 0) {
    brightness = 0;
    direction = true;
  }

  last = millis();

  setBrightness();
}

int LedController::getBrightness() {
  return brightness / 16;
}

void LedController::setBrightness(bool save) {
  if (brightness < 0) {
    brightness = 0;
    target = -1;
  } else if (brightness > 4080) {
    brightness = 4096;
    target = -1;
  }

  driver->setPin(pin, brightness);

  if (save) {
    EEPROM.write(pin, brightness / 16);
    Serial.println(brightness);
  }
}

void LedController::setBrightness(int b, bool save) {
  brightness = b * 16;

  setBrightness(save);
}

void LedController::fade() {
  int amount = 16;
  int diff;
  int direction = 1;

  if (target == -1 || last < FADE_TIMEOUT || target == brightness) {
    return;
  }

  last = 0;

  if (target > brightness) {
    diff = target - brightness;
  } else {
    diff = brightness - target;
    direction = -1;
  }

  if (diff < amount) {
    amount = diff;
  }

  brightness += (amount + (diff / 16)) * direction;

  setBrightness(false);
}

int LedController::getFadeTarget() {
  Serial.print("Target: ");
  Serial.print(target);
  Serial.print("\tBrightness: ");
  Serial.print(brightness);
  Serial.println();

  if (target == -1) {
    return getBrightness();
  }

  return target / 16;
}

void LedController::fade(int t) {
  target = t * 16;
  last = 0;
  EEPROM.write(pin, t);
}

void LedController::tick(int delta) {
  last += delta;

  fade();
}

void LedController::off() {
  setBrightness(0);
}

void LedController::on() {
  setBrightness(EEPROM.read(pin));
}
