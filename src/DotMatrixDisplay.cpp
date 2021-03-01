#include <stdint.h>
#include <Wire.h>
#include "DotMatrixDisplay.h"

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"
void DotMatrixDisplay::write(uint8_t value, uint8_t busAddress) {
	Wire.beginTransmission(busAddress);
	Wire.write(value);
	Wire.endTransmission();
}

#else

#include "WProgram.h"
void DotMatrixDisplay::write(uint8_t value, uint8_t busAddress) {
	Wire.beginTransmission(busAddress);
	Wire.send(value);
	Wire.endTransmission();
}

#endif

void DotMatrixDisplay::sendChar(uint8_t position, char data) {
	dataBus = (uint8_t) data;
	DotMatrixDisplay::write(dataBus, DATA_LANE_ADDR);
	 // Set A0 and A1 address lanes
	controlBus = (controlBus & ~PD2435_A0) | (position & PD2435_A0);
	controlBus = (controlBus & ~PD2435_A1) | (position & PD2435_A1);
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);

	controlBus &= ~PD2435_CE0; // Disable display for a moment
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	controlBus ^= PD2435_WR; // Toggle write
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	delay(1);
	controlBus ^= PD2435_WR;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	controlBus |= PD2435_CE0; // Enable display
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
}


DotMatrixDisplay::DotMatrixDisplay(TwoWire *I2CInterface) {
	I2C = I2CInterface;
	controlBus = 0;
	dataBus = 0;
	pos = 0;
	// Full brightness and attributes enabled by default
	controlWord = DotMatrixDisplay::BRIGHTNESS_100 && PD2435_ATTR_ENABLE;
	scrollSpeed = 250;
}

void DotMatrixDisplay::begin() {
	controlBus |= PD2435_CE0 & PD2435_WR; // CE, WR high
	controlBus &= ~PD2435_RST; // RST low (to toggle)
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	delay(25); // Wait for reset
	controlBus |= PD2435_RST; // RST high (to toggle)
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	DotMatrixDisplay::clear();
}

void DotMatrixDisplay::clear() {
	// Set command mode
	controlBus &= ~PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	// Toggle Clear bit to clear display
	controlWord |= PD2435_CLEAR;
	DotMatrixDisplay::sendChar(0, controlWord);
	controlWord &= ~PD2435_CLEAR;
	DotMatrixDisplay::sendChar(0, controlWord);
	// Set ASCII mode
	controlBus |= PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	pos = 0;
}

void DotMatrixDisplay::setAttributes(uint8_t attribute) {
	 // Set command mode
	controlBus &= ~PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	// check if attributes need to be enabled
	if (attribute & ATTRIBUTE_BIT) controlWord |= PD2435_ATTR_ENABLE;
	else controlWord &= ~PD2435_ATTR_ENABLE;
	// Set attribute bits
	controlWord = (controlWord & ~PD2435_ATTR_BLINK) | (attribute & PD2435_ATTR_BLINK);
	controlWord = (controlWord & ~PD2435_ATTR_CURSOR) | (attribute & PD2435_ATTR_CURSOR);
	controlWord = (controlWord & ~PD2435_BLINK) | (attribute & PD2435_BLINK);
	DotMatrixDisplay::sendChar(0, controlWord);
	// Set ASCII mode
	controlBus |= PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
}

void DotMatrixDisplay::setLampTest(bool lampTest) {
	 // Set command mode
	controlBus &= ~PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	// Set attribute enable bit
	if (lampTest) controlWord |= PD2435_LAMP_TEST;
	else controlWord &= ~PD2435_LAMP_TEST;
	DotMatrixDisplay::sendChar(0, controlWord);
	// Set ASCII mode
	controlBus |= PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
}

void DotMatrixDisplay::setBrightness(uint8_t brightnessLevel) {
	 // Set command mode
	controlBus &= ~PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
	// Set brightness bits
	controlWord = (controlWord & ~PD2435_BRIGHTNESS_A) | (brightnessLevel & PD2435_BRIGHTNESS_A);
	controlWord = (controlWord & ~PD2435_BRIGHTNESS_B) | (brightnessLevel & PD2435_BRIGHTNESS_B);
	DotMatrixDisplay::sendChar(0, controlWord);
	// Set ASCII mode
	controlBus |= PD2435_A2;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
}

void DotMatrixDisplay::setScrollSpeed(int speed) {
	scrollSpeed = speed;
}

void DotMatrixDisplay::setRedLED(bool enableLED) {
	if (enableLED) controlBus |= PD2435_RED_LED;
	else controlBus &= ~PD2435_RED_LED;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
}

void DotMatrixDisplay::setGreenLED(bool enableLED) {
	if (enableLED) controlBus |= PD2435_GREEN_LED;
	else controlBus &= ~PD2435_GREEN_LED;
	DotMatrixDisplay::write(controlBus, CONTROL_LANE_ADDR);
}

size_t DotMatrixDisplay::write(uint8_t c) {
	if (c == 13) c = ' '; // Newline character treated as space
	if (c >= 32) {
		if (pos == PD2435_SIZE) { // Scroll left
			for (int i = 0; i < PD2435_SIZE - 1; i++) {
				uint8_t ch = buffer[i+1];
				DotMatrixDisplay::sendChar(PD2435_SIZE - i - 1, ch);
				buffer[i] = ch;
			}
			pos = pos - 1;
		}
		DotMatrixDisplay::sendChar(PD2435_SIZE - pos - 1, c);
		buffer[pos] = c;
		pos = pos + 1;
		if (pos == PD2435_SIZE) delay(scrollSpeed);
	} else if (c == 12) { // Clear display
		DotMatrixDisplay::clear();
	}
	return 1;
}



