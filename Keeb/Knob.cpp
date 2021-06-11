#include "Knob.h"

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

Knob::Knob(uint8_t pinA, uint8_t pinB) : _enc{pinA, pinB} {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

Knob::Knob(uint8_t pinA, uint8_t pinB, ConsumerKeycode upKey, ConsumerKeycode downKey) : _enc{pinA, pinB} {
    _mode = KNOB_MEDIAKEY;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    _incConsumerKey = upKey;
    _decConsumerKey = downKey;
}
Knob::Knob(uint8_t pinA, uint8_t pinB, KeyboardKeycode upKey, KeyboardKeycode downKey) : _enc{pinA, pinB} {
    _mode = KNOB_KEYBOARDKEY;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    _incKey = upKey;
    _decKey = downKey;
}
Knob::Knob(uint8_t pinA, uint8_t pinB, KnobCallback upCallback, KnobCallback downCallback) : _enc{pinA, pinB} {
    _mode = KNOB_MACRO;
    _incCallback = upCallback;
    _decCallback = downCallback;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

void Knob::update() {
    long newPosition = _enc.read();
    int ticks = (newPosition - _oldPosition) / 4;

    for (int i = 0; i < abs(ticks); i++) {
        switch (_mode) {
            case KNOB_MEDIAKEY:
                Consumer.write(ticks > 0 ? _incConsumerKey : _decConsumerKey);
                break;
            case KNOB_KEYBOARDKEY:
                Keyboard.write(ticks > 0 ? _incKey : _decKey);
                break;
            case KNOB_MACRO:
                ticks > 0 ? this->_incCallback() : this->_decCallback();
                break;
            default:
                break;
        }

        _oldPosition += ticks * 4;
    }
}

void Knob::attachUpBehaviour(ConsumerKeycode key) {
    _mode = KNOB_MEDIAKEY;
    _incConsumerKey = key;
}
void Knob::attachDownBehaviour(ConsumerKeycode key) {
    _mode = KNOB_MEDIAKEY;
    _decConsumerKey = key;
}
void Knob::attachUpBehaviour(KeyboardKeycode key) {
    _mode = KNOB_KEYBOARDKEY;
    _incKey = key;
}
void Knob::attachDownBehaviour(KeyboardKeycode key) {
    _mode = KNOB_KEYBOARDKEY;
    _decKey = key;
}
void Knob::attachUpBehaviour(KnobCallback callback) {
    _mode = KNOB_MACRO;
    _incCallback = callback;
}
void Knob::attachDownBehaviour(KnobCallback callback) {
    _mode = KNOB_MACRO;
    _decCallback = callback;
}
