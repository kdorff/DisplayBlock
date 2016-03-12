#include "Print.h"
#include "Print.h"
#include "LCDBlock.h"
#include <stdarg.h>

LCDBlock::LCDBlock(
			Adafruit_LiquidCrystal *_lcd, 
			int _row, int _col, int _width) {
	lcd = _lcd;
	row = _row;
	col = _col;
	alignment = LCDBLOCK_ALIGN_LEFT;
	width = _width;
	displayfBuffer = (char *) malloc(width + 1);
}
LCDBlock::~LCDBlock() {
	free(displayfBuffer);
}

void LCDBlock::setAlignment(int _alignment) {
	if (_alignment == LCDBLOCK_ALIGN_LEFT || 
		_alignment == LCDBLOCK_ALIGN_RIGHT ||
		_alignment == LCDBLOCK_ALIGN_CENTER) {
		alignment = _alignment;
	}
}

void LCDBlock::clear() {
	// Serial.printf("[%s] Clearing string\n", name);
	value = "";
}

/**
 * Implemented for Print.h print() methods.
 */
#if defined(ARDUINO) && ARDUINO >= 100
size_t LCDBlock::write(uint8_t b)
#else
void LCDBlock::write(uint8_t b)
#endif
{
	// Serial.printf("[%s] Writing char %d '%c'\n", name, b, b);
	if (value.length() < width) {
		value += (char) b;
	}
	#if defined(ARDUINO) && ARDUINO >= 100
		return 1;
	#endif
}

void LCDBlock::lcdSetCursor(int col, int row) {
	// Serial.printf("[%s] Setting cursor to col=%d, row=%d\n", name, col, row);
	if (lcd) {
		lcd->setCursor(col, row);
	}
}

void LCDBlock::lcdWritePadding(int _size) {
	int size = _size <= 0 ? 0 : _size;
	// Serial.printf("[%s] Writing padding size=%d\n", name, size);
	if (lcd && size > 0) {
		for (int i = 0; i < size; i++) {
				lcd->print(' ');
		}
	}
}

void LCDBlock::lcdWriteValue() {
	// Serial.printf("[%s] Writing value='%s'\n", name, value.c_str());
	if (lcd) {
		lcd->print(value);
	}
}

void LCDBlock::display() {
	// Serial.printf("[%s] Updating field on LCD\n", name);
	lcdSetCursor(col, row);
	if (alignment == LCDBLOCK_ALIGN_LEFT) {
		lcdWriteValue();
		lcdWritePadding(width - value.length());
	}
	else if (alignment == LCDBLOCK_ALIGN_RIGHT) {
		lcdWritePadding(width - value.length());
		lcdWriteValue();
	}
	else if (alignment == LCDBLOCK_ALIGN_CENTER) {
		int totalPad = width - value.length();
		int rightPad = totalPad / 2;
		int leftPad  = totalPad - rightPad;
		lcdWritePadding(leftPad);
		lcdWriteValue();
		lcdWritePadding(rightPad);
	}
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(char val) {
	clear();
	size_t size = print((char) val); 
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(unsigned long val, int base) {
	clear();
	size_t size = print((unsigned long) val, (int) base);
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(long val, int base) {
	clear();
	size_t size = print((long) val, (int) base); 
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(unsigned int val, int base) {
	clear();
	size_t size = print((unsigned int) val, (int) base);
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(unsigned char val, int base) {
	clear();
	size_t size = print((unsigned char) val, (int) base);
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(int val, int base) {
	clear();
	size_t size = print((int) val, (int) base);
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(double val, int digits) {
	clear();
	size_t size = print((double) val, (int) digits);
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(const Printable &p) {
	clear();
	size_t size = print(p);
	display();
	return size;
}

/**
 * Convenience write and update method.
 */
size_t LCDBlock::display(const String &s) {
	clear();
	size_t size = print(s);
	display();
	return size;
}

size_t LCDBlock::displayf(char *fmt, ... ) {
    va_list args;
    va_start (args, fmt);
#ifdef __AVR__
    vsnprintf_P(displayfBuffer, sizeof(displayfBuffer), (const char *)fmt, args); // progmem for AVR
#else
    vsnprintf(displayfBuffer, sizeof(displayfBuffer), (const char *)fmt, args); // for the rest of the world
#endif
    va_end(args);
    clear();
    size_t size = print(displayfBuffer);
    display();
    return size;
}
