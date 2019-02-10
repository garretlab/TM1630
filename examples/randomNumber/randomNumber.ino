#include "TM1630DMClass.h"

TM1630DMClass tm1630(25, 26, 27, TM1630_MODE_7X5, TM1630DM_HORIZONTAL);

uint8_t digits[][2] = {
  {0xf6, 0xde}, {0xc9, 0x2e}, {0xe7, 0xce}, {0xe7, 0x9e}, {0xb7, 0x92},
  {0xf3, 0x9e}, {0xf3, 0xde}, {0xe4, 0x92}, {0xf7, 0xde}, {0xf7, 0x9e},
};

void setup() {
  Serial.begin(115200);

  tm1630.begin(TM1630_MODE_7X5,
               TM1630_WRITE_DATA, TM1630_FIXED_ADDRESS, TM1630_NORMAL_MODE,
               TM1630_PULSE_WIDTH02, TM1630_DISPLAY_ON);
  tm1630.clearDisplay();
}

void loop() {
  int n = random(0, 100);

  tm1630.writeRegion(0, 0, 3, 5, digits[n / 10]);
  tm1630.writeRegion(4, 0, 3, 5, digits[n % 10]);
  tm1630.flush();

  delay(200);
}
