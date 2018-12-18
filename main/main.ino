#include <Wire.h>
#include <DS3232RTC.h>
#include <LiquidCrystal.h>

#include "IRremote.h"
#include "menu.h"
#include "LCDMenuDisplay.h"
#include "LedController.h"

#include "menuDefs/ClockMenuDef.h"
#include "menuDefs/LEDMenuDef.h"

#define BUFF_MAX 128

const int NUM_LED = 1;
const int PIN_RECEIVER = 2;
const int IR_REPEAT_TIMEOUT = 500;
const int CLOCK_TIMEOUT = 1000;

int brightness = 0;

bool direction = true;

long last = 0;
long repeatIR = 0;
unsigned long lastIR = 0;

long clockUpdate = 0;

int lastDig = HIGH;

LedController* lc;

Menu mainMenu = Menu("main");

LCDMenuDisplay* lcd;

IRrecv irrecv(PIN_RECEIVER);
decode_results results;

void setupMenu() {
  Menu *menuSetup;
  Menu *subMenu;

  lcd = new LCDMenuDisplay(&mainMenu);

  ClockMenuDef::add(&mainMenu, lcd);
  LEDMenuDef::add(&mainMenu, lcd);

  menuSetup = new Menu("Feeder Status");
  mainMenu.addItem(menuSetup);

  lcd->draw();
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(' ');
  Serial.print(day());
  Serial.print(' ');
  Serial.print(month());
  Serial.print(' ');
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(':');

  if(digits < 10) {
    Serial.print('0');
  }

  Serial.print(digits);
}

void setupClock() {
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
}

void setupIR() {
  irrecv.enableIRIn();
}

void setupPWM() {
  pwm.begin();
  pwm.setPWMFreq(1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);

  Wire.begin();

  setupClock();
  setupIR();
  setupMenu();
  setupPWM();
}

void loop() {
  bool redraw = false;
  long curr = millis();
  int digRead;

  lcd->tick(curr - last);

  repeatIR = repeatIR + (curr - last);
  clockUpdate = clockUpdate + (curr - last);

  last = curr;

  if (irrecv.decode(&results)) {
    Serial.print("Code: ");
    Serial.print(results.value);
    Serial.print("\t Buffer Length: ");
    Serial.print(results.rawlen);
    Serial.print("\t Repeat: ");
    Serial.print(repeatIR);
    Serial.println();

    if (results.value == 0xFFFFFFFF) {
      if (repeatIR > IR_REPEAT_TIMEOUT) {
        redraw = lcd->handleRemote(lastIR);
      }
    } else {
      redraw = lcd->handleRemote(results.value);
      lastIR = results.value;
      repeatIR = 0;
    }

    irrecv.resume();
  }

  if (redraw) {
    lcd->redraw();
  }

  if (clockUpdate > 5000) {
    // if (lastDig == LOW) {
    //   lastDig = HIGH;
    // } else {
    //   lastDig = LOW;
    // }
    //
    // digitalWrite(53, lastDig);

    clockUpdate = 0;
  }
}
