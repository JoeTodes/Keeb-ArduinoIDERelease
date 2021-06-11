#include "Slider.h"

#include "Arduino.h"
#include "HID-Project.h"

Slider::Slider(uint8_t pin)
{
  _pin = pin;
  _mode = SLIDER_MEDIAKEY;
  _upConsumerKey = MEDIA_VOLUME_UP;
  _downConsumerKey = MEDIA_VOLUME_DOWN;
}

Slider::Slider(uint8_t pin, ConsumerKeycode upKey, ConsumerKeycode downKey)
{
  _pin = pin;
  _mode = SLIDER_MEDIAKEY;
  _upConsumerKey = upKey;
  _downConsumerKey = downKey;
}
Slider::Slider(uint8_t pin, KeyboardKeycode upKey, KeyboardKeycode downKey)
{
  _pin = pin;
  _mode = SLIDER_KEYBOARDKEY;
  _upKey = upKey;
  _downKey = downKey;
}

void
Slider::update()
{
  int newVal = analogRead(_pin);
  double newValLin = pow(10.0, ((double)newVal) / 1023);
  double lastValLin = pow(10.0, ((double)_lastVal) / 1023);

  if (!_isReset) {
    if (newVal == 0) {
      this->reset(false);
    } else if (newVal == 1023) {
      this->reset(true);
    }
  }
  if (abs(newValLin - lastValLin) > _deadBand) {
    int newState = (newValLin - 1.0) * (100.0 / 9.0);

    int steps = (newState - _lastState) / 2;
    for (int i = 0; i < abs(steps); i++) {
      switch (_mode) {
        case SLIDER_MEDIAKEY:
          Consumer.write(steps > 0 ? _upConsumerKey : _downConsumerKey);
          break;
        case SLIDER_KEYBOARDKEY:
          Keyboard.write(steps > 0 ? _upKey : _downKey);
          break;
        default:
          break;
      }
    }
    _lastState += steps * 2;
    if ((_lastState > 5) || (_lastState < 95)) {
      _isReset = false;
    }

    _lastVal = newVal;
  }
}

void
Slider::reset(boolean direction)
{
  for (int i = 0; i < 50; i++) {
    switch (_mode) {
      case SLIDER_MEDIAKEY:
        Consumer.write(direction ? _upConsumerKey : _downConsumerKey);
        break;
      case SLIDER_KEYBOARDKEY:
        Keyboard.write(direction > 0 ? _upKey : _downKey);
        break;
      default:
        break;
    }
  }
  _lastState = direction ? 100 : 0;
  _lastVal = direction ? 1023 : 0;
  _isReset = true;
}