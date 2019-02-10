#pragma once

#include <arduino.h>

#define TM1630_DISPLAY_MODE 0x00
#define TM1630_MODE_8X4 0x0
#define TM1630_MODE_7X5 0x1

#define TM1630_DATA_COMMAND 0x40
#define TM1630_WRITE_DATA 0x00
#define TM1630_READ_DATA 0x02
#define TM1630_AUTOMATIC_ADDRESS 0x00
#define TM1630_FIXED_ADDRESS 0x04
#define TM1630_NORMAL_MODE 0x00
#define TM1630_TEST_MODE 0x08

#define TM1630_DISPLAY_CONTROL 0x80
#define TM1630_PULSE_WIDTH01 0x00
#define TM1630_PULSE_WIDTH02 0x01
#define TM1630_PULSE_WIDTH04 0x02
#define TM1630_PULSE_WIDTH10 0x03
#define TM1630_PULSE_WIDTH11 0x04
#define TM1630_PULSE_WIDTH12 0x05
#define TM1630_PULSE_WIDTH13 0x06
#define TM1630_PULSE_WIDTH14 0x07
#define TM1630_DISPLAY_OFF 0x00
#define TM1630_DISPLAY_ON 0x08

#define TM1630_ADDRESS_COMMAND 0xc0

class TM1630BaseClass {
  public:
    TM1630BaseClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin);
    TM1630BaseClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin[], const uint8_t modules);
    void begin();
    void begin(uint8_t dispMode,
               uint8_t rw, uint8_t addrMode, uint8_t opMode,
               uint8_t brightness, uint8_t displaySwitch);
    void displayMode(uint8_t dispMode, uint8_t module = 0);
    void dataCommand(uint8_t rw, uint8_t addrMode, uint8_t opMode, uint8_t module = 0);
    void displayControl(uint8_t brightness, uint8_t displaySwitch, uint8_t module = 0);
    void sendData(uint8_t address, uint8_t data, uint8_t module = 0);
    void clearDisplay(uint8_t module = 0);
    
  private:
    uint8_t dioPin;
    uint8_t clkPin;
    uint8_t *stbPin;
    uint8_t modules;
};
