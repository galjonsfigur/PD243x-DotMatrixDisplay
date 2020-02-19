# Arudino Dot-matrix Display Adapter Library

![PlatformIO CI](https://github.com/galjonsfigur/Arduino-DotMatrixLibrary/workflows/PlatformIO%20CI/badge.svg)  [![Documentation Status](https://readthedocs.org/projects/arduino-dotmatrixlibrary/badge/?version=latest)](https://arduino-dotmatrixlibrary.readthedocs.io/en/latest/?badge=latest)   [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) 

This project is an Arduino-compatible library for an [PD243x I²C Display Adapter Board](https://github.com/galjonsfigur/PD243X-I2C-Adapter).
It can be used on any Arduino-compatible environment that supports `Wire`
library. Tested on Arduino Uno and STM32 "Blue Pill" boards, but should work fine
regardless of the board as long as there is Arduino platform for it. It can be
used both with Arduino IDE and PlatformIO environments.
![Example setup](docs/img/uno.jpg)


### Documentation
All API documentation can be found [here](https://arduino-dotmatrixlibrary.readthedocs.io/en/latest/). It contains description of every
method and functionalities of this library. There is also folder with examples,
which can be found [here](examples/).

### Demo

![Demo](docs/img/demo.gif)

### License
[MIT](LICENSE.md)