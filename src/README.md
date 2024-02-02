# light-switch-remote-control
A remote control for a lamp via MQTT, using an ESP8266 board.

## Description
This arduino sketch switch a Powerswitch Tail 2 either on or off, via MQTT publication, using a simple push button switch.

The code was created for the Wemos D1 Mini, but can be modified to run on other ESP8266 boards.
After uploading the code to the Wemos D1 Mini, wire the D3 pin to one pin of your push button switch.
Then wire GND on the Wemos D1 Mini to the other pin of your push button switch.

## secrets.h
Before you compile and upload to your board, you will need to enter the details of your wifi network and MQTT server in secrets.h.

If you do not want to use TLS encrpytion, simply comment out `"#define ENABLE_SSL"` in mqtt_powerswitchtail_pub.ino.

## case_stl
This directory contains STL files for a 3D printable enclosure, for the Wemos D1 mini and button shield.  Simply slice the models, print them out, place the circuit inside the case, and place the top cover on top of the case.  Both pieces easily snap together, so no glue is necessary.  The enclosure was designed in Fusion 360.
