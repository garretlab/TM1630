#pragma once

#include "TM1630BaseClass.h"

#define TM1630DM_HORIZONTAL 0x00
#define TM1630DM_VERTICAL 0x01

class TM1630DMClass : public TM1630BaseClass {
  public:
    TM1630DMClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin[],
                  uint8_t mode, uint8_t direction, uint8_t numHorizontal, uint8_t numVertical);
    TM1630DMClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin, uint8_t mode, uint8_t direction);
    ~TM1630DMClass();
    void clearBuffer(uint8_t doFlush = 0);
    void writeDot(int x, int y, uint8_t value, uint8_t doFlush = 0);
    void writeRegion(int x, int y, int width, int height, uint8_t data[], uint8_t doFlush = 0);
    void flush();
    
  private:
    uint8_t mode;
    uint8_t direction;
    uint8_t numVertical;
    uint8_t numHorizontal;
    uint8_t modules;
    uint8_t *buffer;
    uint8_t bufferSize;

    void autoFlush(uint8_t doFlush);
};
