#pragma once

#include <stdint.h>
#include <Wire.h>

// I2C addresses of both PCF8574 controlling the board
static constexpr uint8_t CONTROL_LANE_ADDR      = 0x21;
static constexpr uint8_t DATA_LANE_ADDR         = 0x20;

static constexpr uint8_t PD2435_SIZE            = 4;

static constexpr uint8_t PD2435_CLEAR           = 0x80;
static constexpr uint8_t PD2435_LAMP_TEST       = 0x40;
static constexpr uint8_t PD2435_BLINK           = 0x20;
static constexpr uint8_t PD2435_ATTR_ENABLE     = 0x10;
static constexpr uint8_t PD2435_ATTR_CURSOR     = 0x08;
static constexpr uint8_t PD2435_ATTR_BLINK      = 0x04;
static constexpr uint8_t PD2435_BRIGHTNESS_A    = 0x02;
static constexpr uint8_t PD2435_BRIGHTNESS_B    = 0x01;

static constexpr uint8_t PD2435_RED_LED         = 0x80;
static constexpr uint8_t PD2435_GREEN_LED       = 0x40;
static constexpr uint8_t PD2435_CE0             = 0x20;
static constexpr uint8_t PD2435_RST             = 0x10;
static constexpr uint8_t PD2435_WR              = 0x08;
static constexpr uint8_t PD2435_A2              = 0x04;
static constexpr uint8_t PD2435_A1              = 0x02;
static constexpr uint8_t PD2435_A0              = 0x01;

class DotMatrixDisplay : public Print {
public:
	DotMatrixDisplay(TwoWire *I2CInterface);
	void begin();
	void clear();
	void setAttributes(uint8_t attribute);
	void setLampTest(bool lampTest);
	void setBrightness(uint8_t brightnessLevel);
	void setScrollSpeed(int scrollSpeed);
	void setRedLED(bool redLed);
	void setGreenLED(bool greenLed);

	#if defined(ARDUINO) && ARDUINO >= 100
		size_t write(uint8_t c);
	#else
		void write(uint8_t c);
	#endif
	void sendChar(uint8_t position, char data);

	// Possible brightness configurations
	static constexpr uint8_t BRIGHTNESS_100 = 0x03;
	static constexpr uint8_t BRIGHTNESS_50 = 0x02;
	static constexpr uint8_t BRIGHTNESS_25 = 0x01;
	static constexpr uint8_t BRIGHTNESS_0 = 0x00;

	// Possible attributes configurations
	static constexpr char ATTRIBUTE_BIT = 0x80;
	static constexpr uint8_t NO_ATTRIBUTE = 0x00;
	static constexpr uint8_t CURSOR = 0x00 + ATTRIBUTE_BIT;
	static constexpr uint8_t BLINK = 0x04 + ATTRIBUTE_BIT;
	static constexpr uint8_t BLINKING_CURSOR = 0x08 + ATTRIBUTE_BIT;
	static constexpr uint8_t ALTERNATING_CURSOR = 0x0C + ATTRIBUTE_BIT;
	static constexpr uint8_t BLINK_SCREEN = 0x20;
    virtual void flush() { /* Empty implementation for backward compatibility */ }

	virtual ~DotMatrixDisplay() {}

private:
	void write(uint8_t value, uint8_t busAddress);
	TwoWire *I2C;
	uint8_t controlBus;
	uint8_t dataBus;
	uint8_t controlWord;
	uint8_t pos;
	int scrollSpeed;
	char buffer[4] = {' ', ' ', ' ', ' '};
};
