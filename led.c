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

int main(void) {

	DIRlcdE		|= _BV(PINlcdE);
	DIRlcdRW	|= _BV(PINlcdRW);
	DIRlcdRS	|= _BV(PINlcdRS);
	DIRlcdD4	|= _BV(PINlcdD4);
	DIRlcdD5	|= _BV(PINlcdD5);
	DIRlcdD6	|= _BV(PINlcdD6);
	DIRlcdD7	|= _BV(PINlcdD7);

	PORTlcdRW	|= _BV(PINlcdRW);

	while(1) {

	}
}
