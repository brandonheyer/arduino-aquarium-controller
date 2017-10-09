#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

class Menu {
  public:
    Menu(String l);
    Menu(String l, bool isM);

    virtual void draw();
    virtual bool handleRemote(unsigned long value);

    void addItem(Menu *item);

    Menu* getItem(int index);

    bool isMenu;
    int numItems;
    String label;
    Menu* parent;

  private:
    Menu *items[16];
};

#endif
