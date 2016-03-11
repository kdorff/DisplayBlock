#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_LiquidCrystal.h"
#include "LCDBlock.h"

#define LCD_ROWS 4
#define LCD_COLS 20

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
LCDBlock dayDateBlock = LCDBlock(&lcd, 0, 0, 20);
LCDBlock timeBlock =    LCDBlock(&lcd, 1, 0, 10);
LCDBlock flipBlock =    LCDBlock(&lcd, 1, 10, 10);

void setup() {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);

  // Configure the LCD
  lcd.begin(LCD_COLS, LCD_ROWS);
}
  
int int1 = 1;
int int2 = 1;
bool bool3 = false;

void loop() {

  // Clear the block, do some prints to it, update the LCD
  // TODO: This may not work on Arduino but it works on ESP8266. Hmm.
  dayDateBlock.displayf("%d:%d", int1, int2);

  // The update functions clear, print, and display all in one go
  timeBlock.clear();
  timeBlock.print("Pi:");
  double pi = 3.1415926536;
  // We don't have 15 but the field is only 10. So we should
  // end up with Pi:3.14159
  timeBlock.print(pi, 15);
  timeBlock.display();

  // We can chose left or right justified test.
  // You might want right justified test if you have an output that is
  // on the right side of the screen
  if (bool3) {
      flipBlock.setAlignment(LCDBLOCK_ALIGN_LEFT);
      flipBlock.display("left");
  }
  else {
      flipBlock.setAlignment(LCDBLOCK_ALIGN_RIGHT);
      flipBlock.display("right");
  }

  // Prepare for the next iteration and wait a moment
  int1 += 1;
  int2 += 2;
  bool3 = !bool3;
  delay(500);
}