#include <Arduino.h>
#include <DotMatrixDisplay.h>

DotMatrixDisplay disp(&Wire);

void setup() {
	Wire.begin();
	disp.begin();
}

void loop() {
	// Write scrolling text
	disp.print("Hello World!");
	delay(4000);
	disp.clear();
	delay(4000);
}
