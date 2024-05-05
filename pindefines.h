#include <avr/io.h>

#define PINlcdE       PORTB3
#define PINlcdRW			PORTB0
#define PINlcdRS      PORTB4
#define PINlcdD4      PORTD5
#define PINlcdD5      PORTD4
#define PINlcdD6      PORTD3
#define PINlcdD7      PORTD3

#define DIRlcdE 			DDRB
#define DIRlcdRW			DDRB
#define DIRlcdRS    	DDRB
#define DIRlcdD4    	DDRD
#define DIRlcdD5    	DDRD
#define DIRlcdD6    	DDRD
#define DIRlcdD7    	DDRD
#define DIRlcdDATA    DDRD

#define PORTlcdE    	PORTB
#define PORTlcdRW			PORTB
#define PORTlcdRS   	PORTB
#define PORTlcdD4   	PORTD
#define PORTlcdD5   	PORTD
#define PORTlcdD6   	PORTD
#define PORTlcdD7   	PORTD
#define PORTlcdDATA   PORTD

#define READlcdE      PINB
#define READlcdRW			PINB
#define READlcdRS     PINB
#define READlcdD4     PIND
#define READlcdD5     PIND
#define READlcdD6     PIND
#define READlcdD7     PIND

#define CLEARlcdD     PORTD = 0b00000000
#define SETlcdE       PORTlcdE |= _BV(PINlcdE)
#define CLEARlcdE     PORTlcdE &= ~(_BV(PINlcdE))