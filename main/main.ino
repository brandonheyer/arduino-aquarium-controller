#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

#include "IRremote.h"
#include "menu.h"
#include "LedControlMenu.h"
#include "LedController.h"
#include "LCDMenuDisplay.h"
#include "Adafruit_PWMServoDriver.h"

const int NUM_LED = 1;
const int PIN_RECEIVER = 2;

int brightness = 0;
bool direction = true;

LedController* lc;
DS3231 clock;

Menu mainMenu = Menu("main");

LCDMenuDisplay* lcd;

IRrecv irrecv(PIN_RECEIVER);
decode_results results;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setupMenu() {
  Menu *menuSetup;
  Menu *subMenu;

  lcd = new LCDMenuDisplay(&mainMenu);

  menuSetup = new Menu("LED Controls");
  mainMenu.addItem(menuSetup);

  subMenu = new Menu("White 1");
  subMenu->addItem(new LedControlMenu(lcd->getLiquidCrystal(), "White 1"));
  menuSetup->addItem(subMenu);

  subMenu = new Menu("White 2");
  menuSetup->addItem(subMenu);

  subMenu = new Menu("White 3");
  menuSetup->addItem(subMenu);

  subMenu = new Menu("White 4");
  menuSetup->addItem(subMenu);

  subMenu = new Menu("Grow 1");
  menuSetup->addItem(subMenu);

  subMenu = new Menu("Grow 2");
  menuSetup->addItem(subMenu);

  menuSetup = new Menu("Feeder Status");
  mainMenu.addItem(menuSetup);

  lcd->draw();
}

void setupClock() {
  Serial.print(clock.getSecond(), DEC);
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

  Wire.begin();

  setupIR();
  setupClock();
  setupMenu();
  setupPWM();

  lc = new LedController(0, &pwm);
}

void loop() {
  bool redraw = false;

  if (irrecv.decode(&results)) {
    redraw = lcd->handleRemote(results.value);
    irrecv.resume();
  }

  if (redraw) {
    lcd->redraw();
  }

  lc->demo();

  // Serial.print("Minute: ");
  Serial.print(clock.getMinute(), DEC);

  Serial.print(":");
  Serial.println(clock.getSecond(), DEC);
}
