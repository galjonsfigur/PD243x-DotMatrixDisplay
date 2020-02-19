#include <Arduino.h>
#include <DotMatrixDisplay.h>

DotMatrixDisplay disp(&Wire);

void setup() {
	Wire.begin();
	disp.begin();
	disp.print("LED test");
	// Enable lamp test for 1 second
	delay(1000);
	disp.setLampTest(true);
	delay(1000);
	disp.setLampTest(false);
	// Set brightness to 100%
	disp.setBrightness(DotMatrixDisplay::BRIGHTNESS_100);
}

void loop() {
	// Blink red and green LED's on display board
	disp.setGreenLED(true);
	disp.setRedLED(false);
	delay(1000);
	disp.setGreenLED(false);
	disp.setRedLED(true);
	delay(1000);
}

