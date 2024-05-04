#include <avr/io.h>
#include <util/delay.h>

// Reg Sel  Pin 12
// Enable   Pin 11
// Data 4-7 Pin 5-2

#define lcdE        PORTB3
#define lcdRS       PORTB4
#define lcdD4       PORTD5
#define lcdD5       PORTD4
#define lcdD6       PORTD3
#define lcdD7       PORTD3

#define DIRlcdE     DDRB3
#define DIRlcdRS    DDRB4
#define DIRlcdD4    DDRD5
#define DIRlcdD5    DDRD4
#define DIRlcdD6    DDRD3
#define DIRlcdD7    DDRD3


int main(void) {



	while(1) {

	}
}
