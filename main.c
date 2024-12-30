#include "func.h"
#include "pindefines.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

// Reg Sel  Pin 12
// RW				Pin 8
// Enable   Pin 11
// Data 4-7 Pin 5-2
// RW H Read L Write

#define FOSC 16000000UL
#define BAUD 115200
#define MYUBRR FOSC / (16 * BAUD) - 1

void usart_init(unsigned int ubrr) {
  UCSR0C = 0;
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  // Enable
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // 8 bit char; 2 bit stop
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

int main() {
  DDRB |= _BV(PORTB5); // Builtin LED Direction Register
  // Set all pins to outputs
  DIRlcdE |= _BV(PINlcdE);
  DIRlcdRW |= _BV(PINlcdRW);
  DIRlcdRS |= _BV(PINlcdRS);
  DIRlcdD4 |= _BV(PINlcdD4);
  DIRlcdD5 |= _BV(PINlcdD5);
  DIRlcdD6 |= _BV(PINlcdD6);
  DIRlcdD7 |= _BV(PINlcdD7);
  // Set RW to read
  PORTlcdRW |= _BV(PINlcdRW);

  // initLcd();
  lcdDataWrite(0b01000001, RAM);
  // busyWait();
  _delay_us(5);
  lcdDataWrite(55, RAM);
  // busyWait();
  _delay_us(5);
  lcdDataWrite(0b00111110, RAM);
  // busyWait();
  _delay_us(5);

  DDRB |= 0b100000; // PORTB5
  usart_init(MYUBRR);
  while (1) {
    // turn LED on
    PORTB |= 0b100000; // PORTB5
    _delay_ms(BLINK_DELAY_MS);

    // turn LED off
    PORTB &= ~0b100000; // PORTB5
    _delay_ms(BLINK_DELAY_MS);

    if ((UCSR0A & (1 << RXC0))) {
      unsigned char data = UDR0;
      while (!(UCSR0A & (1 << UDRE0))) {
        UDR0 = data;
      }
    }
  }
}
