#include "Matrix.h"

#include "Arduino.h"
#include "ArduinoSTL.h"

Matrix::Matrix(std::vector<Key> keyList,
               std::vector<int> colPins,
               std::vector<int> rowPins)
{
  _keyCount = keyList.size();
  _colCount = colPins.size();
  _rowCount = rowPins.size();
  _keys = keyList;
  _colPins = colPins;
  _rowPins = rowPins;

  for (int i = 0; i < _keyCount; i++) {
    _keyStates.push_back(0);
  }
}

std::vector<int>
Matrix::scanKeys()
{
  std::vector<int> newStates;
  for (int c = 0; c < _colCount; c++) {
    int colPin = _colPins[c];

    digitalWrite(colPin, LOW);
    for (int r = 0; r < _rowCount; r++) {
      newStates.push_back(!digitalRead(_rowPins[r]));
    }
    digitalWrite(colPin, HIGH);
  }
  return newStates;
}

void
Matrix::update()
{
  std::vector<int> newStates = this->scanKeys();

  for (int i = 0; i < _keyCount; i++) {
    // Serial.print(_keyStates[i]);
    // Serial.print(" ");
    // Serial.println(newStates[i]);
    if (newStates[i] != _keyStates[i]) {
      if (newStates[i]) {
        _keys[i].execute();
      }
    }
  }
  _keyStates = newStates;
}

void
Matrix::setup()
{
  for (int pin : _colPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  for (int pin : _rowPins) {
    pinMode(pin, INPUT_PULLUP);
  }
}
