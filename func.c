#include <util/delay.h>
#include "pindefines.h"
#include "func.h"

AVAILABLE isLcdBusy() {
	// Set RW pin to indicate READ
	DIRlcdRW 	|= _BV(PINlcdRW);
	PORTlcdRW |= _BV(PINlcdRS);

	DIRlcdD7	&= ~(_BV(PINlcdD7));// Set D7 direction to input

	// Enable pin must be pulsed to get busy flag info
	DIRlcdE		|= _BV(PINlcdE);
	PORTlcdE	|= _BV(PINlcdE); 		// Enable High

	_delay_us(1);
	volatile uint8_t pinValue = (READlcdD7	& _BV(PINlcdD7));
	PORTlcdE &= ~(_BV(PINlcdE)); 	// Enable low
	_delay_us(1);
		
	PORTlcdE |= _BV(PINlcdE); 		// Enable High
	_delay_us(1);
	PORTlcdE &= ~(_BV(PINlcdE)); 	// Enable Low
	_delay_us(1);

	if (pinValue != 0) {
		return BUSY;
	}
	return FREE;
}

void busyWait()
{
  AVAILABLE processing = isLcdBusy();
  while (processing == BUSY)
  {
    _delay_us(1);
    processing = isLcdBusy();
  }
}

void lcdDataWrite(uint8_t data, REGSEL selregister) {
//                     D7 D6 D5 D4
  uint8_t nibble[4] = { 0, 0, 0, 0};
  int     pin[]   = {PINlcdD7, PINlcdD6, PINlcdD5, PINlcdD4};
  uint8_t mask = 0b00000000;
  PORTlcdDATA = 0b00000000;
  ledOn;
  
  int i = 0;
  for ( /* i declared */ ; i < sizeof(data) / 2; i++) {
    uint8_t compare = (1 << i);
    if (compare & data) {
      nibble[i] = 1;
    }
  }

  for (int j = 0; j < sizeof(nibble) / sizeof(sizeof(nibble[0])); j++) {
    if (nibble[j] == 1) {
      mask |= _BV(pin[j]);
    }
  }
  
  PORTlcdRW &= ~(_BV(PINlcdRW));
  if (selregister == CONTROLLER) {
    PORTlcdRS &= ~(_BV(PINlcdRS));
  }
  else {
    PORTlcdRS |= _BV(PINlcdRS);
  }
  _delay_us(1);
  SETlcdE;
  PORTlcdDATA = mask;
  _delay_us(1);
  
  UNSETlcdE;
  PORTlcdRW |= _BV(PINlcdRW);

  for ( /* i declared */ ; i < sizeof(data); i++) {
    uint8_t compare = (1 << i);
    if (compare & data) {
      nibble[i] = 1;
    }
  }

  for (int j = 0; j < sizeof(nibble) / sizeof(sizeof(nibble[0])); j++) {
    if (nibble[j] == 1) {
      mask |= _BV(pin[j]);
    }
  }
  
  PORTlcdRW &= ~(_BV(PINlcdRW));
  _delay_us(1);
  SETlcdE;
  PORTlcdDATA = mask;
  _delay_ms(1000);
  
  UNSETlcdE;
  PORTlcdRW |= _BV(PINlcdRW);
  ledOff;
}

void initLcd() {
  _delay_ms(30);
  DIRlcdE   |= _BV(PINlcdE);
// Init round 1
  PORTlcdE  |= _BV(PINlcdE);
  PORTlcdD5 |= _BV(PINlcdD5);
  PORTlcdD4 |= _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE  &= ~(_BV(PINlcdE));
  PORTlcdD5 &= ~(_BV(PINlcdD5));
  PORTlcdD4 &= ~(_BV(PINlcdD4));
  _delay_ms(4.2);
// Init round 2
  PORTlcdE  |= _BV(PINlcdE);
  PORTlcdD5 |= _BV(PINlcdD5);
  PORTlcdD4 |= _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE  &= ~(_BV(PINlcdE));
  PORTlcdD5 &= ~(_BV(PINlcdD5));
  PORTlcdD4 &= ~(_BV(PINlcdD4));
  _delay_us(100);
// Init round 3
  PORTlcdE  |= _BV(PINlcdE);
  PORTlcdD5 |= _BV(PINlcdD5);
  PORTlcdD4 |= _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE  &= ~(_BV(PINlcdE));
  PORTlcdD5 &= ~(_BV(PINlcdD5));
  PORTlcdD4 &= ~(_BV(PINlcdD4));
// Configure
  _delay_us(100);
  
  PORTlcdE    |= _BV(PINlcdE);
  PORTlcdDATA |= _BV(PINlcdD5) | _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE    &= ~(_BV(PINlcdE));
  PORTlcdDATA &= ~(_BV(PINlcdD5) | _BV(PINlcdD4));
// From here on, each instruction needs 2 write cycles to get 1 byte from 4 wires
// Configuration information for these values can be found on the instruction set section
// of the LCD 1602a datasheet. Datasheet I used: https://t.ly/wD0rJ
  _delay_ms(10000);
  lcdDataWrite(0b00101100, CONTROLLER); // Set controller to 4 bit mode, with 2 lines and 5x10 font
  _delay_ms(10000);
  lcdDataWrite(0b00001000, CONTROLLER); // Set display to off
  _delay_ms(10000);
  lcdDataWrite(0b00000001, CONTROLLER); // Clear display
  _delay_ms(10000);
  lcdDataWrite(0b00000110, CONTROLLER); // Set entry mode
  _delay_ms(10000);
  lcdDataWrite(0b00001110, CONTROLLER); // Set display on, cursor on, cursor blinking
  _delay_ms(10000);
}

void ledBlink() {
    ledOn;
    _delay_ms(500);
    ledOff;
}