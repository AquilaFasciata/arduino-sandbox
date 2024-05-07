default:
		avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
		avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o func.o func.c
		avr-gcc -o main.bin main.o func.o
		avr-objcopy -O ihex -R .eeprom main.bin main.hex
		avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex
clean:
	rm func.o main.hex main.o 
