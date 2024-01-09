# NeoPixel Arduino Project

This Arduino project controls NeoPixel LED strips using an ESP8266 microcontroller. It includes a web server for remote control and customization of LED colors.

## Table of Contents

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Setup](#setup)
- [Usage](#usage)
- [Web Interface](#web-interface)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project utilizes the Adafruit NeoPixel library and ESP8266WiFi library to control NeoPixel LED strips. The main features include:

- Three color modes with customizable color combinations.
- Web server for remote control and configuration.

## Dependencies

- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
- [ESP8266WiFi Library](https://github.com/esp8266/Arduino)

## Setup

1. Connect your NeoPixel LED strip to the ESP8266 microcontroller.
2. Install the required libraries using the Arduino IDE Library Manager.
3. Open the Arduino IDE, load the sketch, and upload it to your ESP8266.

## Usage

1. Power on the ESP8266 with the NeoPixel LED strip connected.
2. Connect to the ESP8266's WiFi network (SSID: PrincessLuna, Password: Purpl3R@inbow0192).
3. Open a web browser and navigate to the IP address shown in the Serial Monitor.
4. Use the web interface to choose color modes, toggle colors, and customize color combinations.

## Web Interface

The web interface provides the following functionalities:

- Select color modes: First, Second, Third.
- Toggle colors on/off.
- Customize main color and additional colors using color pickers.
- Update colors with the "Zaktualizuj Kolory" button.

## Contributing

Feel free to contribute to this project by submitting issues or pull requests. Your feedback and improvements are welcome!

## License

This project is licensed under the [MIT License](LICENSE).
