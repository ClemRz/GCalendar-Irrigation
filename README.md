# Google Calendar Irrigation system

**How to use it?** Add a task to your Google Calendar and the irrigation of your garden/lawn will start when the event begins and stop when it ends!

**Why I invented that?** I don't like the interface of cheap irrigation programmers, the irrigation parameters are not flexible enough and it can't be controlled remotely. I wanted a cheap wifi irrigation programmer but I didn't want to build the entire UI for the ESP8266, I preferred to be able to change the irrigation planning from anywhere with simple means. I decided to have the ESP polling one of my Google Calendars, with events to turn on and off the valve at the correct timing.

**How is this made possible?** A ESP8266 connects to your Google Calendar via your home Wifi (using a Google Script) and commands a solenoid valve.

## TOC

  - [Hardware design](#hardware-design)
  - [Software design](#software-design)

## Hardware design

Parts list:

  - 1 x Resistor (10KΩ)
  - 3 x Capacitors (22µF, 0.1µF, 4700µF)
  - 1 x DC motor driver (DRV8872 in this case)
  - 1 x ESP8266 (version ESP07)
  - 1 x Voltage regulator (LT1521CST-3.3 for instance)
  - 1 x 12V 1.5A charger
  - 1 x Female plug (same size as the charger's plug)
  - 1 x Prototyping board
  - 1 x Latching solenoid valve (scavenged from an Orbit 58874N)
  - 3 x Momentary push buttons
  - 1 x Rocker switch

![Sketch](res/sketch.png)

## Software design

### Dependencies

  - [ArduinoJson library](https://github.com/bblanchon/ArduinoJson)

### Parameters

Change the constants according to your needs:

  - WAKEUP_RATE: How long should the device be sleeping between each polling.
