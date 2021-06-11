#include "Key.h"

#include "HID-Project.h"

Key::Key()
{
  _mode = KEY_NULL;
}
Key::Key(KeyCallback macro)
{
  _callback = macro;
  _mode = KEY_MACRO;
}
Key::Key(KeyboardKeycode key)
{
  _key = key;
  _mode = KEY_KEYBOARDKEY;
}
Key::Key(ConsumerKeycode key)
{
  _mediaKey = key;
  _mode = KEY_MEDIAKEY;
}

void
Key::execute()
{
  switch (this->_mode) {
    case KEY_MEDIAKEY:
      Consumer.write(this->_mediaKey);
      break;
    case KEY_KEYBOARDKEY:
      Keyboard.write(this->_key);
      break;
    case KEY_MACRO:
      this->_callback();
      break;
    default:
      break;
  }
}