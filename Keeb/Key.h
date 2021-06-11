#ifndef KEY__H
#define KEY__H

#include "Arduino.h"
#include "HID-Project.h"

typedef void (*KeyCallback)();

enum KeyMode : int8_t
{
  KEY_KEYBOARDKEY,
  KEY_MEDIAKEY,
  KEY_MACRO,
  KEY_NULL
};

class Key
{
private:
  KeyMode _mode;
  KeyboardKeycode _key;
  ConsumerKeycode _mediaKey;
  KeyCallback _callback;

public:
  Key();
  Key(KeyboardKeycode key);
  Key(ConsumerKeycode key);
  Key(KeyCallback macro);
  void execute();
};

#endif