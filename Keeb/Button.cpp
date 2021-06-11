#include "Button.h"

#include "Arduino.h"
#include "HID-Project.h"

Button::Button()
{
  _mode = BUTTON_NULL;
}

Button::Button(int pin, KeyboardKeycode key)
{
  pinMode(pin, INPUT_PULLUP);
  _mode = BUTTON_KEYBOARDKEY;
  _key = key;
  _pin = pin;
}
Button::Button(int pin, ConsumerKeycode key)
{
  pinMode(pin, INPUT_PULLUP);
  _mode = BUTTON_MEDIAKEY;
  _consumerKey = key;
  _pin = pin;
}
Button::Button(int pin, ButtonCallback macro)
{
  pinMode(pin, INPUT_PULLUP);
  _mode = BUTTON_MACRO;
  _callback = macro;
  _pin = pin;
}
Button::Button(KeyboardKeycode key)
{
  _mode = BUTTON_KEYBOARDKEY;
  _key = key;
}
Button::Button(ConsumerKeycode key)
{
  _mode = BUTTON_MEDIAKEY;
  _consumerKey = key;
}
Button::Button(ButtonCallback macro)
{
  _mode = BUTTON_MACRO;
  _callback = macro;
}

void
Button::debounce(int pin)
{
  int btnState = digitalRead(pin);
  if (btnState == this->_lastStateBtn) {
    this->_lastChangeTime = millis();
  } else if (millis() - this->_lastChangeTime > this->_delay) {
    this->_lastStateBtn = btnState;
    this->_lastChangeTime = millis();
    if (this->_lastStateBtn == LOW) {
      Serial.println("button Pressed");
      switch (this->_mode) {
        case BUTTON_MEDIAKEY:
          Consumer.write(this->_consumerKey);
          break;
        case BUTTON_KEYBOARDKEY:
          Keyboard.write(this->_key);
          break;
        case BUTTON_MACRO:
          this->_callback();
          break;
        default:
          break;
      }
    }
  }
}

void
Button::update(int pin)
{
  this->debounce(pin);
}

void
Button::update()
{
  this->update(_pin);
}

int
Button::state()
{
  return _lastStateBtn;
}

ButtonMode
Button::getMode()
{
  return _mode;
}
