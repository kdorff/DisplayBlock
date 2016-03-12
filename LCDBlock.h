#include <Adafruit_LiquidCrystal.h>
#include <PString.h>
#include <Print.h>

#ifndef LCDBlock_h
#define LCDBlock_h

#define LCDBLOCK_ALIGN_LEFT   0
#define LCDBLOCK_ALIGN_RIGHT  1
#define LCDBLOCK_ALIGN_CENTER 2

class LCDBlock : public Print {
	public:
		// Support for "print*" methods for this class.
#if defined(ARDUINO) && ARDUINO >= 100
		virtual size_t write(uint8_t);
#else
		virtual void write(uint8_t);
#endif

	public:
		// Constructor
		LCDBlock(Adafruit_LiquidCrystal *_lcd, int _rows, int _cols, int _width);
		~LCDBlock();
		// Clear what has already been written to the block
		// (interally, does not update screen)
		void clear();
		// Update the screen to display has has be sent via this 
		//class's print* calls
		void display();
		// Set left or right justified text
		void setAlignment(int _alignment);

		// Alternative to .clear(), .print(), .display() if you just
		// need to write a single piece of information
		size_t display(int val, int base = DEC);
		size_t display(long val, int base = DEC);
		size_t display(double val, int digits = 2);
		size_t display(unsigned char val, int base = DEC);
		size_t display(unsigned int val, int base = DEC);
		size_t display(unsigned long val, int base = DEC);
		size_t display(char val);
		// TODO: This wouldn't compile. Why? It came directly from Print.h
		//size_t display(const char[] val);
		size_t display(const Printable &p);
		size_t display(const String &s);
		size_t displayf(char *fmt, ... );

	protected:
		void lcdSetCursor(int col, int row);
		void lcdWritePadding(int _size);
		void lcdWriteValue();

		// Support variables.
		Adafruit_LiquidCrystal *lcd;
		String value = "";
		char *displayfBuffer;
		int row;
		int col;
		int width;
		int alignment;
		//char *name;
};

#endif /*LCDBlock_h*/
