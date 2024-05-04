# Arduino Playground

### This repo is a playground and a "throw it in that one" repo for my Arduino projects written entirely in C. I will archive whatever I end up writing in this repo both in its own repo (if I deem it worthy) and compressed in this repo.

## Current Project: LCD Ultrasonic Distance Display

Currently, I am working on writing a project to display the distance of a *thing* from the sensor (have yet to decide between Metric units and Moon units).

### Build Instructions

1. Ensure that you have the build depends installed (avr-gcc, avr-lib, and avr-dude).
2. Double check the last line of `Makefile` is set to your Arduino port (`/dev/ttyACM0` is the default for me and many others. If you aren't sure, just try giving it a run)
3. This should build the program and flash it to your Arduino