#include "func.h"
#include "pindefines.h"
#include "serial.h"
#include "sonic.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <string.h>
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
  sensorInit();
  DDRB |= _BV(PORTB5); // Builtin LED & Trigger DIR
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
  lcdPrint("Distance: ");
  int distArr[2] = {0};
  int arrAccess = 0;
  static const int distArrLen = sizeof(distArr) / sizeof(distArr[0]);
  while (1) {
    unsigned char serial_input;
    while ((UCSR0A & (1 << RXC0))) {
      serial_input = UDR0;

      switch (serial_input) {
      case ':':
        lcdDataWrite(1, CONTROLLER);
        busyWait();
        break;
      case 'h':
        lcdShiftCursor(1, LEFT);
        busyWait();
        break;
      case 'l':
        lcdShiftCursor(2, RIGHT);
        busyWait();
        break;
      default:
        lcdDataWrite(serial_input, RAM);
        busyWait();
        break;
      }
    }

    int distance = sensorGetDistance();

    if (arrAccess++ == distArrLen - 1) {
      arrAccess = 0;
    }

    distArr[arrAccess] = distance;

    int distAvg = 0;
    for (int i = 0; i < distArrLen; i++) {
      distAvg += distArr[i];
    }
    distAvg /= distArrLen;

    usart_print("avg: ");
    usart_num_print(distAvg);
    usart_print("\n\r");

    char number[10] = {'\0'};
    itoa(distAvg, number, 10);
    lcdPrint(number);
    lcdPrint("cm");
    lcdShiftCursor(strlen(number) + 2, LEFT);
    _delay_ms(100);
  }
}
