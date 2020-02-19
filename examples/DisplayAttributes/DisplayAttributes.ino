#include <Arduino.h>
#include <DotMatrixDisplay.h>

DotMatrixDisplay disp(&Wire);

// To enable attributes on given
// char an attribute bit must be added to the char itself
static const char message[4] = {(char) 'H' + DotMatrixDisplay::ATTRIBUTE_BIT, 'e', 'y', '!'};

void setup() {
	Wire.begin();
	disp.begin();
	// Set scrolling speed to 150 milliseconds
	disp.setScrollSpeed(150);
}

void loop() {
	// Turn off any attributes
	disp.setAttributes(DotMatrixDisplay::NO_ATTRIBUTE);
	disp.print(message);
	delay(1000);
	// Blink entire screen
	disp.setAttributes(DotMatrixDisplay::BLINK_SCREEN);
	delay(1000);
	// Blink 'H' character
	disp.setAttributes(DotMatrixDisplay::BLINK);
	delay(1000);
	// Display cursor instead of 'H' character
	disp.setAttributes(DotMatrixDisplay::CURSOR);
	delay(1000);
	// Display blinking cursor instead of 'H' character
	disp.setAttributes(DotMatrixDisplay::BLINKING_CURSOR);
	delay(1000);
	// Alternate 'H' character witch cursor
	disp.setAttributes(DotMatrixDisplay::ALTERNATING_CURSOR);
	delay(1000);
	disp.clear();
}

