#include "func.h"
#include "pindefines.h"
#include "serial.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

// Reg Sel  Pin 12
// RW				Pin 8
// Enable   Pin 11
// Data 4-7 Pin 5-2
// RW H Read L Write

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

int main() {
  usart_init(MYUBRR);
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

  initLcd();
  // lcdDataWrite('H', RAM);
  // busyWait();
  // lcdDataWrite(134, RAM);
  // busyWait();
  // lcdDataWrite(0b00111110, RAM);
  // busyWait();

  DDRB |= 0b100000; // PORTB5
  while (1) {
    unsigned char serial_input;
    while ((UCSR0A & (1 << RXC0))) {
      lcdDataWrite(UDR0, RAM);
      busyWait();
    }
  }
}
