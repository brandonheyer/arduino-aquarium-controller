#ifndef CLOCK_H
#define CLOCK_H

#include <LiquidCrystal.h>
#include <DS3232RTC.h>

class Clock {
  public:
    static void drawDigit(int digit, LiquidCrystal* display) {
      if (digit < 10) {
        display->print("0");
      }

      display->print(digit);
    }

    static void drawTime(int x, int y, LiquidCrystal* display) {
      display->setCursor(x, y);

      Clock::drawDigit(hour(), display);
      display->print(":");

      Clock::drawDigit(minute(), display);
      display->print(":");

      Clock::drawDigit(second(), display);
    }

    static void drawDate(int x, int y, LiquidCrystal* display) {
      display->setCursor(x, y);

      display->print(month());
      display->print("/");

      display->print(day());
      display->print("/");

      display->print(year());
    }
};

#endif
