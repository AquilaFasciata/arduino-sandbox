# Arduino Playground

#### This repo is a playground and a "throw it in that one" repo for my Arduino projects written entirely in C. I will archive whatever I end up writing in this repo both in its own repo (if I deem it worthy) and compressed in this repo.

## Current Project: LCD Ultrasonic Distance Display

Currently, I am working on writing a project to display the distance of a *thing* from the sensor (have yet to decide between Metric units and Moon units).

### Build Instructions

1. Ensure that you have the build depends installed (avr-gcc, avr-lib, and avr-dude).
2. Double check the last line of `Makefile` is set to your Arduino port (`/dev/ttyACM0` is the default for me and many others. If you aren't sure, just try giving it a run)
3. This should build the program and flash it to your Arduino


### Pinout Diagram
Below is an ASCII pinout of what pin on the Arduino Uno goes to what pin on the LCD screen. NOTE: The pinout doesn't line up well with "tutorial" setups. I did this explicitly to 
make is harder on myself in order to learn properly. This pinoutt may change in the future (though, it likely won't).

                                                                  +-----+                                                                                                                               
                                     +----[PWR]-------------------| USB |--+                         .-------------.                                                                                    
                                     |                            +-----+  |                         |  1602a LCD  |                                                                                    
                                     |         GND/RST2  [ ][ ]            |                         |             |                                                                                    
                                     |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |                         |             |                                                                                    
                                     |          5V/MISO2 [ ][ ]  A4/SDA[ ] |                         |             |                                                                                    
                                     |                             AREF[ ] |                         |             |                                                                                    
                                     |                              GND[ ] |                         |             |                                                                                    
                                     | [ ]N/C                    SCK/13[ ] |                         |             |                                                                                    
                                     | [ ]IOREF                 MISO/12[X]---------------------------| RS          |                                                                                    
                                     | [ ]RST                   MOSI/11[X]+--------------------------+ E           |                                                                                    
                                     | [ ]3V3    +---+               10[ ]~|                         |             |                                                                                    
                                     | [ ]5v    -| A |-               9[ ]~|                         |             |                                                                                    
                                     | [ ]GND   -| R |-               8[ ] |                         |             |                                                                                    
                                     | [ ]GND   -| D |-                    |                         |             |                                                                                    
                                     | [ ]Vin   -| U |-               7[ ] |                         |             |                                                                                    
                                     |          -| I |-               6[ ]~|                         |             |                                                                                    
                                     | [ ]A0    -| N |-               5[X]---------------------------- D4          |                                                                                    
                                     | [ ]A1    -| O |-               4[X]+--------------------------+ D5          |                                                                                    
                                     | [ ]A2     +---+           INT1/3[X]---------------------------- D6          |                                                                                    
                                     | [ ]A3                     INT0/2[X]+--------------------------+ D7          |                                                                                    
                                     | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |                         |             |                                                                                    
                                     | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |                         |             |                                                                                    
                                     |            [ ] [ ] [ ]              |                         |             |                                                                                    
                                     |  UNO_R3    GND MOSI 5V  ____________/                         |             |                                                                                    
                                      \_______________________/                                      |             |                                                                                    
                                                                                                     '-------------'
                            		  http://busyducks.com/ascii-art-arduinos                                                                                                                                 
