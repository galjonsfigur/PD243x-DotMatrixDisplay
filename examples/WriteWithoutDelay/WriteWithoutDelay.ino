#include <Arduino.h>
#include <DotMatrixDisplay.h>

DotMatrixDisplay disp(&Wire);

void setup() {
	Wire.begin();
	disp.begin();
}

void loop() {
	// Display single characters on screen
	// Position on screen is inverted
	disp.sendChar(3, 'H');
	disp.sendChar(2, 'e');
	disp.sendChar(1, 'y');
	disp.sendChar(0, '!');
	delay(4000);
	disp.clear();
	delay(1000);
}

