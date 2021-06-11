#ifndef Slider_h
#define Slider_h

#include "Arduino.h"
#include "HID-Project.h"

enum SliderMode : int8_t
{
  SLIDER_KEYBOARDKEY,
  SLIDER_MEDIAKEY,
};

class Slider
{
private:
  uint8_t _pin;
  SliderMode _mode;
  int _lastVal;
  int _lastState;
  double _deadBand = .1;
  bool _isReset = false;
  ConsumerKeycode _upConsumerKey;
  ConsumerKeycode _downConsumerKey;
  KeyboardKeycode _upKey;
  KeyboardKeycode _downKey;
  void reset(boolean direction);

public:
  Slider(uint8_t pin);
  Slider(uint8_t pin, ConsumerKeycode upKey, ConsumerKeycode downKey);
  Slider(uint8_t pin, KeyboardKeycode upKey, KeyboardKeycode downKey);
  void update();
};

#endif