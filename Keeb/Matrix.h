#ifndef MATRIX_H
#define MATRIX_H

#include "Arduino.h"
#include "Key.h"
#include <ArduinoSTL.h>

class Matrix
{
private:
  std::vector<Key> _keys;
  std::vector<int> _colPins;
  std::vector<int> _rowPins;
  std::vector<int> _keyStates;
  std::vector<int> scanKeys();
  int _keyCount;
  int _colCount;
  int _rowCount;

public:
  Matrix(std::vector<Key> keyList,
         std::vector<int> colPins,
         std::vector<int> rowPins);
  void setup();
  void update();
};

#endif
