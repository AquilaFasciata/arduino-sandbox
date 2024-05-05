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
	volatile uint8_t pinValue = READlcdD7	& _BV(PINlcdD7);
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

void lcd_data_write(uint8_t data) {
  uint8_t  
  DIRlcdDATA = 0b00111100;


}

void initLcd() {
  _delay_ms(30);
  DIRlcdE   |= _BV(PINlcdE);
// Init round 1
  PORTlcdE  |= _BV(PINlcdE);
  _delay_us(1);
  PORTlcdD5 |= _BV(PINlcdD5);
  PORTlcdD4 |= _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE  &= ~(_BV(PINlcdE));
  PORTlcdD5 &= ~(_BV(PINlcdD5));
  PORTlcdD4 &= ~(_BV(PINlcdD4));
  _delay_ms(4.2);
// Init round 2
  PORTlcdE  |= _BV(PINlcdE);
  _delay_us(1);
  PORTlcdD5 |= _BV(PINlcdD5);
  PORTlcdD4 |= _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE  &= ~(_BV(PINlcdE));
  PORTlcdD5 &= ~(_BV(PINlcdD5));
  PORTlcdD4 &= ~(_BV(PINlcdD4));
// Configure
  busyWait();
  
  PORTlcdE  |= _BV(PINlcdE);
  _delay_us(1);
  PORTlcdD5 |= _BV(PINlcdD5);
  PORTlcdD4 |= _BV(PINlcdD4);
  _delay_us(1);
  PORTlcdE  &= ~(_BV(PINlcdE));
  PORTlcdD5 &= ~(_BV(PINlcdD5));
  PORTlcdD4 &= ~(_BV(PINlcdD4));
  busyWait();

}
