#ifndef Knob_h
#define Knob_h

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

typedef void (*KnobCallback)();
enum KnobMode : int8_t {
    KNOB_KEYBOARDKEY,
    KNOB_MEDIAKEY,
    KNOB_MACRO
};
class Knob {
   private:
    ConsumerKeycode _incConsumerKey;
    ConsumerKeycode _decConsumerKey;
    KeyboardKeycode _incKey;
    KeyboardKeycode _decKey;
    KnobMode _mode;

    int _oldPosition = 0;
    Encoder _enc;
    KnobCallback _incCallback = NULL;
    KnobCallback _decCallback = NULL;

   public:
    Knob(uint8_t pinA, uint8_t pinB);
    Knob(uint8_t pinA, uint8_t pinB, ConsumerKeycode upKey, ConsumerKeycode downKey);
    Knob(uint8_t pinA, uint8_t pinB, KeyboardKeycode upKey, KeyboardKeycode downKey);
    Knob(uint8_t pinA, uint8_t pinB, KnobCallback upCallback, KnobCallback downCallback);

    void update();
    void attachUpBehaviour(ConsumerKeycode key);
    void attachDownBehaviour(ConsumerKeycode key);
    void attachUpBehaviour(KeyboardKeycode key);
    void attachDownBehaviour(KeyboardKeycode key);
    void attachUpBehaviour(KnobCallback callback);
    void attachDownBehaviour(KnobCallback callback);
};

#endif  // Knob_h
