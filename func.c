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
  PORTlcdE  &= ~(_BV(PINlcdE));
  // Wait 10 ms for LCD power suppy + 15 ms according to DS +
  // 5 ms as margin for error
  _delay_ms(10);
  // Next three sections send 0b0011 three times as per the DS
  SETlcdE;
  PORTlcdDATA = 0b00001100;
  _delay_us(1.5);
  UNSETlcdE;
  _delay_us(0.1);
  CLEARlcdD;
  _delay_ms(4.5);
  // Section 2
  SETlcdE;
  PORTlcdDATA = 0b00001100;
  _delay_us(1.5);
  UNSETlcdE;
  _delay_us(0.1);
  CLEARlcdD;
  _delay_us(100);
  //Section 3
  SETlcdE;
  PORTlcdDATA = 0b00001100;
  _delay_us(1.5);
  UNSETlcdE;
  _delay_us(0.1);
  CLEARlcdD;
  busyWait();
  // Now we configure with 0b0011 first
  SETlcdE;
  PORTlcdDATA = 0b00001100;
  _delay_us(1.5);
  UNSETlcdE;
  _delay_us(0.1);
  CLEARlcdD;
  busyWait();

}

void ledBlink() {
    ledOn;
    _delay_ms(500);
    ledOff;
}