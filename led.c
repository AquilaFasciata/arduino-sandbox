#include <avr/io.h>
#include <util/delay.h>
#include "pindefines.h"
#include "func.h"

// Reg Sel  Pin 12
// RW				Pin 8
// Enable   Pin 11
// Data 4-7 Pin 5-2
// RW H Read L Write


int main(void) {
	// Set all pins to outputs
	DIRlcdE		|= _BV(PINlcdE);
	DIRlcdRW	|= _BV(PINlcdRW);
	DIRlcdRS	|= _BV(PINlcdRS);
	DIRlcdD4	|= _BV(PINlcdD4);
	DIRlcdD5	|= _BV(PINlcdD5);
	DIRlcdD6	|= _BV(PINlcdD6);
	DIRlcdD7	|= _BV(PINlcdD7);
	// Set RW to read
	PORTlcdRW	|= _BV(PINlcdRW);

	while(1) {

	}
}
