#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_LiquidCrystal.h"
//#include "LCDBlock.h"

#define LCD_ROWS 4
#define LCD_COLS 20

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
// LCDBlock dayDateBlock = LCDBlock(&lcd, 0, 0, 20);
// LCDBlock timeBlock =    LCDBlock(&lcd, 1, 0, 10);
// LCDBlock flipBlock =    LCDBlock(&lcd, 1, 10, 10);

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
  lcd.setCursor(0, 0);
  lcd.print(int1);
  lcd.print(':');
  lcd.print(int2);

  // The update functions clear, print, and display all in one go
  lcd.setCursor(0, 1);
  double pi = 3.1415926536;
  lcd.print("Pi:");
  lcd.println(pi, 5);

  // We can chose left or right justified test.
  // You might want right justified test if you have an output that is
  // on the right side of the screen
  lcd.setCursor(10, 1);
  if (bool3) {
      lcd.println("left      ");
  }
  else {
      lcd.println("     right");
  }

  // Prepare for the next iteration and wait a moment
  int1 += 1;
  int2 += 2;
  bool3 = !bool3;
  delay(500);
}