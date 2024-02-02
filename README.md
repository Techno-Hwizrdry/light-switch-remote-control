# light-switch-remote-control
A remote control for a lamp via MQTT, using an ESP8266 board.

## Description
This arduino sketch will switch a Powerswitch Tail 2 either on or off, via MQTT publication, using a simple push button switch.

The code was created for the Wemos D1 Mini, but can be modified to run on other ESP8266 boards.
After uploading the code to the Wemos D1 Mini, wire the D3 pin to one pin of your push button switch.
Then wire GND on the Wemos D1 Mini to the other pin of your push button switch.

## Prerequistes
This code was written and tested with VScode and PlatformIO.  VScode was also used to upload the sketch to the board.
The steps to set up the tool chain is:

0. [Download](https://www.python.org/downloads/) and install Python 3.5 or higher.
1. [Download](https://code.visualstudio.com/download) and install VSCode.
2. In VScode, download and install the following VScode extensions:
    - Arduino
    - C/C++
    - C/C++ Extension Pack
    - PlatformIO IDE

## secrets.h
Before you compile and upload to your board, you will need to:

1. Copy `src/secrets.h_example` to `src/secrets.h`
2. Enter the details of your MQTT server in secrets.h.

In secrets.h, your `mqttCertFingerprint[]` should look something like this:

`const uint8_t mqttCertFingerprint[] = {0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x11,0x22,0x33,0x44,0x55,0x1A,0x69,0x42,0x00,0x80,0x08,0x55,0xB0,0x0B};`

If you do not want to use TLS encrpytion, simply comment out `"#define ENABLE_SSL"` in light-switch-remote-control.ino.

## case_stl
The `src/` directory contains STL files for a 3D printable enclosure, for the Wemos D1 mini and button shield.  Simply slice the models, print them out, place the circuit inside the case, and place the top cover on top of the case.  Both pieces easily snap together, so no glue is necessary.  The enclosure was designed in Fusion 360.

## Connecting to your WiFi network
This project uses the WiFiManager.h library.  Once your esp8266 board has been successfully flashed, and either hasn't been connected to wifi before or to a network it recognizes, it will act as a WiFi access point (AP).  The AP serves a web interface that will allow you to add your WiFi network's credentials.  Once added, the AP turns off and the esp8266 will join the WiFi network you specified.  To do this:

1. Connect to the `Light-switch-remote-AP` access point.
2. In a web browser, go to `192.168.4.1`
3. Tap the Configure WiFi button.
4. Add your WiFi network's credentials.