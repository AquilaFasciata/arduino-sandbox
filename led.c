#include <avr/io.h>
#include <util/delay.h>

// Reg Sel  Pin 12
// RW				Pin 0
// Enable   Pin 11
// Data 4-7 Pin 5-2

#define PINlcdE       PORTB3
#define PINlcdRW			PORTD0
#define PINlcdRS      PORTB4
#define PINlcdD4      PORTD5
#define PINlcdD5      PORTD4
#define PINlcdD6      PORTD3
#define PINlcdD7      PORTD3

#define DIRlcdE 			DDRB
#define DIRlcdRW			DDRD
#define DIRlcdRS    	DDRB
#define DIRlcdD4    	DDRD
#define DIRlcdD5    	DDRD
#define DIRlcdD6    	DDRD
#define DIRlcdD7    	DDRD

#define PORTlcdE    	PORTB
#define PORTlcdRW			PORTD
#define PORTlcdRS   	PORTB
#define PORTlcdD4   	PORTD
#define PORTlcdD5   	PORTD
#define PORTlcdD6   	PORTD
#define PORTlcdD7   	PORTD

#define READlcdE      PINB
#define READlcdRW			PIND
#define READlcdRS     PINB
#define READlcdD4     PIND
#define READlcdD5     PIND
#define READlcdD6     PIND
#define READlcdD7     PIND

typedef enum {
	BUSY,
	FREE
} AVAILABLE;

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

int main(void) {

	DIRlcdE		|= _BV(PINlcdE);
	DIRlcdRW	|= _BV(PINlcdRW);
	DIRlcdRS	|= _BV(PINlcdRS);
	DIRlcdD4	|= _BV(PINlcdD4);
	DIRlcdD5	|= _BV(PINlcdD5);
	DIRlcdD6	|= _BV(PINlcdD6);
	DIRlcdD7	|= _BV(PINlcdD7);

	PORTlcdRW	|= _BV(PINlcdRW);

	// Delay required to allow LCD controller to get to proper voltage/
	_delay_ms(500);



	while(1) {

	}
}
