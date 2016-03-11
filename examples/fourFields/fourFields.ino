#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_LiquidCrystal.h"
#include "LCDBlock.h"

#define LCD_ROWS 4
#define LCD_COLS 20

Adafruit_LiquidCrystal lcd(0);
LCDBlock tempBlock =    LCDBlock(&lcd, 0 /* row# */, 12 /* col# */, 6 /* width */);
LCDBlock humidBlock =   LCDBlock(&lcd, 1, 12, 6);
LCDBlock voltBlock =    LCDBlock(&lcd, 2, 12, 6);
LCDBlock currentBlock = LCDBlock(&lcd, 3, 12, 6);

void setup() {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(LCD_COLS, LCD_ROWS);

  // Additional configuration of the blocks
  tempBlock.setAlignment(LCDBLOCK_ALIGN_RIGHT);
  humidBlock.setAlignment(LCDBLOCK_ALIGN_CENTER);
  voltBlock.setAlignment(LCDBLOCK_ALIGN_CENTER);
  currentBlock.setAlignment(LCDBLOCK_ALIGN_RIGHT);

  // Print the screen with blank spaces for the blocks
  lcd.setCursor(0, 0); lcd.print("Temperature:       C");
  lcd.setCursor(0, 1); lcd.print("Humidity:          %");
  lcd.setCursor(0, 2); lcd.print("Current:           V");
  lcd.setCursor(0, 3); lcd.print("Voltage:           A");
}

void loop() {
    // Update variables for output to use
    double temp    =  25 + random(9) + ((double) 1 / (random(10) + 1));
    int humudity   =  80 + random(9);
    int voltage    = 220 + random(9);
    float current =   12 + random(3) + ((double) 1 / (random(10) + 1));

    // Update temperature (with one digit after decimal)
    tempBlock.display(temp, 1);

    // Update humidity using a printf-compatible call
    // Note that Arduino doesn't support %f (floating point) formats
    // with printf-like functions. print(...) and display(...) handle
    // double and float just fine. 
    // NOTE: displayf(...) may be slightly slower than using multiple calls
    // NOTE: to print(...) but it can improve readability, so use it where it
    // NOTE: makes sense. In the case below I only use it for demonstration
    // NOTE: purposes. If your format is as simple as "%d" (only outputting 
    // NOTE: a single, otherwise unformatted, value) you should use 
    // NOTE: display(value).
    humidBlock.displayf("%d", humudity);

    // Update voltage
    voltBlock.display(voltage);

    // The long way. Using display(...) handles doing the
    // clear and display() for you, but if you want to have full control
    // to synchronize calling display() or some such, do it this way.
    // ALSO you want to do it this way if you have need multiple print() to
    // construct a single block.
    currentBlock.clear(); currentBlock.print(current, 1); currentBlock.display();
    delay(1000);
}