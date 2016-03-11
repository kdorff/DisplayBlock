#include "LCDBlock.h"

#define LCD_ROWS 4
#define LCD_COLS 20


LCDBlock oneBlock = LCDBlock(NULL, 0, 0, 20);
LCDBlock twoBlock = LCDBlock(NULL, 1, 0, 10);
LCDBlock treBlock = LCDBlock(NULL, 1, 10, 10);

void setup() {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);
  Serial.println("Beginning tests");
  
  // TODO: Write some tests
}

void loop() {
}