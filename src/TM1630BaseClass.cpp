#include "TM1630BaseClass.h"

TM1630BaseClass::TM1630BaseClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin) :
  TM1630BaseClass(dioPin, clkPin, &stbPin, 1) {
}

TM1630BaseClass::TM1630BaseClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin[], const uint8_t modules) {
  this->dioPin = dioPin;
  this->clkPin = clkPin;
  this->stbPin = new uint8_t[modules];
  for (int i = 0; i < modules; i++) {
    this->stbPin[i] = stbPin[i];
  }
  this->modules = modules;
}

TM1630BaseClass::~TM1630BaseClass() {
  delete [] stbPin;
}

void TM1630BaseClass::begin() {
  pinMode(dioPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  for (uint8_t i = 0; i < modules; i++) {
    pinMode(stbPin[i], OUTPUT);
  }

  digitalWrite(dioPin, LOW);
  digitalWrite(clkPin, LOW);
  for (uint8_t i = 0; i < modules; i++) {
    digitalWrite(stbPin[i], HIGH);
  }
}

void TM1630BaseClass::begin(uint8_t dispMode,
                            uint8_t rw, uint8_t addrMode, uint8_t opMode,
                            uint8_t brightness, uint8_t displaySwitch) {
  begin();
  for (uint8_t i = 0; i < modules; i++) {
    displayMode(dispMode, i);
    dataCommand(rw, addrMode, opMode, i);
    displayControl(brightness, displaySwitch, i);
  }
}

void TM1630BaseClass::displayMode(uint8_t dispMode, uint8_t module) {
  digitalWrite(stbPin[module], LOW);
  shiftOut(dioPin, clkPin, LSBFIRST, TM1630_DISPLAY_MODE | dispMode);
  digitalWrite(stbPin[module], HIGH);
}

void TM1630BaseClass::dataCommand(uint8_t rw, uint8_t addrMode, uint8_t opMode, uint8_t module) {
  digitalWrite(stbPin[module], LOW);
  shiftOut(dioPin, clkPin, LSBFIRST, TM1630_DATA_COMMAND | rw | addrMode | opMode);
  digitalWrite(stbPin[module], HIGH);
}

void TM1630BaseClass::displayControl(uint8_t brightness, uint8_t displaySwitch, uint8_t module) {
  digitalWrite(stbPin[module], LOW);
  shiftOut(dioPin, clkPin, LSBFIRST, TM1630_DISPLAY_CONTROL | brightness | displaySwitch);
  digitalWrite(stbPin[module], HIGH);
}

void TM1630BaseClass::sendData(uint8_t address, uint8_t data, uint8_t module) {
  digitalWrite(stbPin[module], LOW);
  shiftOut(dioPin, clkPin, LSBFIRST, TM1630_ADDRESS_COMMAND | address);
  delayMicroseconds(1);
  shiftOut(dioPin, clkPin, LSBFIRST, data);
  digitalWrite(stbPin[module], HIGH);
}

void TM1630BaseClass::clearDisplay(uint8_t module) {
  for (uint8_t i = 0; i < 10; i++) {
    sendData(i, 0, module);
  }
}
