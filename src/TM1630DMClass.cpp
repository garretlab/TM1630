#include "TM1630DMClass.h"

TM1630DMClass::TM1630DMClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin[],
                             uint8_t mode, uint8_t direction, uint8_t numHorizontal, uint8_t numVertical)
  : TM1630BaseClass(dioPin, clkPin, stbPin, numHorizontal * numVertical) {
  this->mode = mode;
  this->direction = direction;
  this->numHorizontal = numHorizontal;
  this->numVertical = numVertical;
  this->modules = numHorizontal * numVertical;

  switch (mode) {
    case TM1630_MODE_8X4: /* not implemented */
      break;
    case TM1630_MODE_7X5:
      bufferSize = numHorizontal * numVertical * 5;
      buffer = new uint8_t[bufferSize]();
      break;
  }
}

TM1630DMClass::TM1630DMClass(const uint8_t dioPin, const uint8_t clkPin, const uint8_t stbPin, uint8_t mode, uint8_t direction) :
  TM1630DMClass(dioPin, clkPin, &stbPin, mode, direction, 1, 1) {
}

TM1630DMClass::~TM1630DMClass() {
  delete [] buffer;
}

void TM1630DMClass::clearBuffer(uint8_t doFlush) {
  for (int i = 0; i < bufferSize; i++) {
    buffer[i] = 0;
  }

  autoFlush(doFlush);
}

void TM1630DMClass::writeDot(int x, int y, uint8_t value, uint8_t doFlush) {
  switch (mode) {
    case TM1630_MODE_8X4: /* not implemented */
      break;
    case TM1630_MODE_7X5:
      if (direction == TM1630DM_HORIZONTAL) {
        if (value) { /* set */
          buffer[y % (5 * numVertical) + (x / 7) * 5 * numVertical] |= 1 << (8 - (x % 7 + 1));
        } else { /* unset */
          buffer[y % (5 * numVertical) + (x / 7) * 5 * numVertical] &= ~(1 << (8 - (x % 7 + 1)));
        }
      } else {
        if (value) { /* set */
          buffer[x % (5 * numHorizontal) + (y / 7) * 5 * numHorizontal] |= 1 << (y % 7 + 1);
        } else { /* unset */
          buffer[x % (5 * numHorizontal) + (y / 7) * 5 * numHorizontal] &= ~(1 << (y % 7 + 1));
        }
      }
      break;
    default:
      break;
  }

  autoFlush(doFlush);
}

void TM1630DMClass::writeRegion(int x, int y, int width, int height, uint8_t data[], uint8_t doFlush) {
  uint8_t n = 0;
  uint8_t b = 7;

  for (int yy = 0; yy < height; yy++) {
    for (int xx = 0; xx < width; xx++) {
      if (data) {
        writeDot(x + xx, y + yy, data[n] & (1 << b));
      } else {
        writeDot(x + xx, y + yy, 0);
      }

      if (b) {
        b--;
      } else {
        b = 7, n++;
      }
    }
  }

  autoFlush(doFlush);
}

void TM1630DMClass::flush() {
  switch (mode) {
    case TM1630_MODE_8X4: /* not implemented */
      break;
    case TM1630_MODE_7X5:
      for (int i = 0; i < modules; i++) {
        for (int j = 0; j < 5; j++) {
          sendData(j * 2, buffer[5 * i + j], i);
        }
      }
    default:
      break;
  }
}

void TM1630DMClass::autoFlush(uint8_t doFlush) {
  if (doFlush) {
    flush();
  }
}
