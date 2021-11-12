# Controller-on-NodeMcu-v3

Created this program to control DMX-512 via WiFi with NodeMcu v3
I will add functions and create schematics for the wiring.
A Rs485 module will be used in this project with a XLR plug to connect with the decoders.

![Main](https://github.com/AGNworks/Controller-on-NodeMcu-v3/blob/main/pics/IMG_20211110_182049.jpg)

## About

This controller is based on NodeMCU microcontroller and uses an RS485 module to create DMX-512 signal for testing decoders. I tried to make it as compact as it's possible. Made a case in Fusion 360. It has a turn on/off switch, a XLR plug, a LED to indicate if it's turned on and a plug for charging the batteries (3 pcs of 18650 with BMS 3S).

The following picture shows the schemantics without the power part.

![Scheme](https://github.com/AGNworks/Controller-on-NodeMcu-v3/blob/main/schematics/nodemcu_rs485.JPG)

## What you need
If uou want to use this program you will need two files, the [index_en.html](https://github.com/AGNworks/Controller-on-NodeMcu-v3/blob/main/src/index_en.h) (or [index_ru.html](https://github.com/AGNworks/Controller-on-NodeMcu-v3/blob/main/src/index_ru.h)) and the arduino file ([DMX_controller.ino](https://github.com/AGNworks/Controller-on-NodeMcu-v3/blob/main/src/DMX_controller.ino)) . Put these files to one folder and you should be able to compile it, if you installed the inculeded libraries. 
