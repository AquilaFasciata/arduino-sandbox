#include <avr/io.h>

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