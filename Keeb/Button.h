#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "HID-Project.h"

enum ButtonMode : int8_t
{
  BUTTON_KEYBOARDKEY,
  BUTTON_MEDIAKEY,
  BUTTON_MACRO,
  BUTTON_NULL
};

typedef void (*ButtonCallback)();

class Button
{
private:
  int _pin;
  unsigned long _delay = 10;
  unsigned long _lastDebounceTime = 0;
  unsigned long _lastChangeTime = 0;
  int _lastStateBtn = HIGH;
  ButtonCallback _callback = NULL;
  KeyboardKeycode _key;
  ConsumerKeycode _consumerKey;
  ButtonMode _mode;
  void debounce(int pin);
  bool isTimeToUpdate();

public:
  Button();
  Button(int pin, KeyboardKeycode key);
  Button(int pin, ConsumerKeycode key);
  Button(int pin, ButtonCallback macro);
  Button(KeyboardKeycode key);
  Button(ConsumerKeycode key);
  Button(ButtonCallback macro);
  void update();
  void update(int pin);
  int state();
  void setCallback(ButtonCallback);
  ButtonMode getMode();
};

#endif // Button_h