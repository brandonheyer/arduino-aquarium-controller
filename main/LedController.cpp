#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"
#include "LedController.h"

LedController::LedController(int p, Adafruit_PWMServoDriver* pwm) {
  pin = p;
  brightness = 0;
  direction = true;
  driver = pwm;

  last = millis();
}

void LedController::demo() {
  if (millis() - last < 10) {
    return;
  }

  if (direction) {
    brightness += 16;
  } else {
    brightness -= 16;
  }

  if (brightness > 4096) {
    brightness = 4096;
    direction = false;
  } else if (brightness < 0) {
    brightness = 0;
    direction = true;
  }

  last = millis();

  driver->setPin(pin, brightness);
}

void LedController::off() {
  brightness = 0;
  driver->setPin(pin, brightness);
}
