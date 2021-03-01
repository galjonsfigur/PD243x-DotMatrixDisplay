# Arduino Dot-Matrix Library

This library allows to use any Arduino-compatible board with an PD243x I²C Display Adapter Board. It should work as long as `Wire` library and C++ compiler is available for a particular Arduino platform.

## DotMatrixDisplay::DotMatrixDisplay

The constructor initializes `DotMatrixDisplay` object and allocates required memory. Multiple objects can be created and assigned to different I²C interfaces. The class itself derives from `Print` class and thus can utilize `print`, `println` and other functions from that class.

#### Syntax

```c++
DotMatrixDisplay(TwoWire *I2CInterface)
```

#### Parameters

- `TwoWire *I2CInterface`: Address of `Wire` object. With most of Arduino boards only `Wire` will be available, but with more capable controllers like STM32 other I²C buses like `Wire1`, `Wire2` can be used.

#### Returns

`DotMatrixDisplay` object.

#### Example

`DotMatrixDisplay disp(&Wire);`

## DotMatrixDisplay::begin

Method used to init and reset PD245X display. Should be called only once in the code.

!!! attention
    This method can only be called after I²C interface is initialized (e.g. `Wire.init()` is called).


#### Syntax

`disp.begin();`

#### Parameters

None

#### Returns

Nothing

#### Example

```c++
Wire.begin();
disp.begin();
```

## DotMatrixDisplay::clear

Sends clear command to the display and thus clears display content.

#### Syntax

`void clear()`

#### Parameters

None

#### Returns

Nothing

#### Example

```c++
disp.clear();
```

## DotMatrixDisplay::setAttributes

Sets display attributes. PD243X displays have an option to set various visual attributes on some characters or entire display. All attributes supported by PD243X displays:

- `NO_ATTRIBUTE`: Turns off any enabled attributes.
- `CURSOR`: Displays cursor instead of character.
- `BLINK`: Blinks character.
- `BLINKING_CURSOR`: Displays blinking cursor instead of character.
- `ALTERNATING_CURSOR`: Alternates character with cursor.
- `BLINK_SCREEN`: Blinks entire screen.
All blinking attributes have constant frequency of about 0.5 Hz.

!!! attention
    All above attributes except `BLINK_SCREEN` require an `ATTRIBUTE_BIT` added to the character before writing it to the display. An example of this operation can be found in [Display attributes example](examples/display_attributes.md).

#### Syntax

`void setAttributes(uint8_t attribute)`

#### Parameters

- `uint8_t attribute`: Attribute to set. Possible options:
    - `DotMatrixDisplay::NO_ATTRIBUTE`
    - `DotMatrixDisplay::CURSOR`
    - `DotMatrixDisplay::BLINK`
    - `DotMatrixDisplay::BLINKING_CURSOR`
    - `DotMatrixDisplay::ALTERNATING_CURSOR`
    - `DotMatrixDisplay::BLINK_SCREEN`

#### Returns

Nothing

#### Example

```c++
// Turns of all attributes
disp.setAttributes(DotMatrixDisplay::NO_ATTRIBUTE);
```

## DotMatrixDisplay::setLampTest

Enables or disables PD243X lamp test routine. Test routine displays all dots at 50% brightness and can be helpful when looking for damaged LEDs in the display.

#### Syntax

`void setLampTest(bool lampTest)`

#### Parameters

- `bool lampTest`: set `true` to enable lamp test or `false` to disable it.

#### Returns

Nothing

#### Example

```c++
// Enables lamp test routine
disp.setLampTest(true);
```

## DotMatrixDisplay::setBrightness

Allows to set brightness of PD243X display. Display itself supports only 0% (blank display), 25%, 50% and 100%.

#### Syntax

`void setBrightness(uint8_t brightnessLevel)`

#### Parameters

- `uint8_t brightnessLevel`: Brightness level. Supported options:
    - `BRIGHTNESS_100`: 100% brightness.
    - `BRIGHTNESS_50`: 50% brightness (set by default).
    - `BRIGHTNESS_25`: 25% brightness.
    - `BRIGHTNESS_0`: 0% brightness (blank screen).

#### Returns

Nothing

#### Example

```c++
// Set brightness to 100%
disp.setBrightness(DotMatrixDisplay::BRIGHTNESS_100);
```

## DotMatrixDisplay::setScrollSpeed

Allows to change default scroll speed (250ms) of text on the display.

#### Syntax

`void setScrollSpeed(int scrollSpeed)`

#### Parameters

- `int scrollSpeed`: Scrolling speed in milliseconds.

#### Returns

Nothing

#### Example

```c++
// Set scrolling speed to 150 milliseconds 
disp.setScrollSpeed(150);
```

## DotMatrixDisplay::setRedLED

Enables or disables red LED on PD243X adapter board.

#### Syntax

`void setRedLED(bool redLed)`

#### Parameters

- `bool redLed`:  set `true` to enable red LED or `false` to disable it.

#### Returns

Nothing

#### Example

```c++
// Enable red LED on display board
disp.setRedLED(true);
```

## DotMatrixDisplay::setGreenLED

Enables or disables green LED on PD243X adapter board.

#### Syntax

`void setGreenLED(bool greenLed)`

#### Parameters

- `bool greenLed`:  set `true` to enable green LED or `false` to disable it.

#### Returns

Nothing

#### Example

```c++
// Enable green LED on display board
disp.setGreenLED(true);
```

## DotMatrixDisplay::sendChar

Writes one character to desired place on screen.

!!! note
    This method is very useful when use of `delay` is not desired in code. Otherwise use of functions derived form `Print` class (`print`) is recommended. More information about using `print` functions can be found in examples code and in [Arduino `Serial.print` documentation](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/) which is also derived from `Print` class. 

#### Syntax

`void sendChar(uint8_t position, char data)`

#### Parameters

- `uint8_t position`: Position on screen from 0 to 3. PD254X displays have inverted positions, so the first character on screen is on 3rd position.
- `char data`: Character to write on screen.

#### Returns

Nothing

#### Example

```c++
// Display single characters on screen
// Position on screen is inverted
disp.sendChar(3, 'H');
disp.sendChar(2, 'e');
disp.sendChar(1, 'y');
disp.sendChar(0, '!');
```
