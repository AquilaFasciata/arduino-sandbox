#include "func.h"
#include "pindefines.h"
#include "serial.h"
#include <stdlib.h>
#include <util/delay.h>

AVAILABLE isLcdBusy() {
  // Set RW pin to indicate READ
  SETREADlcdRW;
  PORTlcdRS &= ~(_BV(PINlcdRS));
  DIRlcdD7 &= ~(_BV(PINlcdD7)); // Set D7 direction to input

  // Enable pin must be pulsed to get busy flag info
  PORTlcdE |= _BV(PINlcdE); // Enable High
  _delay_us(1.5);

  uint8_t pinValue = (PIND & _BV(PINlcdD7));

  UNSETlcdE;
  _delay_us(1);
  SETlcdE;
  _delay_us(1);
  UNSETlcdE;

  if (!pinValue) {
    return BUSY;
  }
  return FREE;
}

void busyWait() {
  AVAILABLE processing = isLcdBusy();
  while (processing == BUSY) {
    _delay_ms(1);
    processing = isLcdBusy();
  }
}

void lcdDataWrite(uint8_t data, REGSEL selregister) {
  DIRlcdDATA |= 0b00111100;
  uint8_t mask1 = 0b00000000;
  uint8_t mask2 = 0b00000000;
  CLEARlcdD;
  SETWRITElcdRW;

  char numstr[8 * sizeof(int) + 1];
  numstr[8 * sizeof(int)] = '\0';
  itoa(data, numstr, 2);
  usart_print("Intending to write: ");
  usart_print(numstr);
  usart_print("\n\r");

  // Iterate through the each bit of data and add it to the mask if the bit is 1
  // First half will go to mask1 and second will go to mask2
  for (int i = 0; i < 8; i++) {
    if (data & (1 << i)) {
      if (i < 4) {
        mask2 |= (1 << i);
      } else {
        mask1 |= (1 << (i % 4));
      }
    }
  }

  // Shift masks to match physical bit positions
  mask1 <<= 2;
  mask2 <<= 2;

  numstr[8 * sizeof(int)] = '\0';
  itoa(mask1, numstr, 2);
  usart_print("Mask 1 is: ");
  usart_print(numstr);
  usart_print("\n\r");

  numstr[8 * sizeof(int)] = '\0';
  itoa(mask2, numstr, 2);
  usart_print("Mask 2 is: ");
  usart_print(numstr);
  usart_print("\n\r");

  if (selregister == CONTROLLER) {
    PORTlcdRS &= ~(_BV(PINlcdRS));
  } else {
    PORTlcdRS |= _BV(PINlcdRS);
  }

  SETlcdE;
  PORTlcdDATA |= mask1;
  _delay_us(1);
  UNSETlcdE;
  _delay_us(1);
  CLEARlcdD;
  _delay_us(1);

  SETlcdE;
  PORTlcdDATA |= mask2;
  _delay_us(1);
  UNSETlcdE;
  _delay_us(1);
  CLEARlcdD;
  _delay_us(1);
}

void initLcd() {
  PORTlcdE &= ~(_BV(PINlcdE));
  // Wait 10 ms for LCD power suppy + 15 ms according to DS +
  // 5 ms as margin for error
  _delay_ms(40);
  // Next three sections send 0b0011 three times as per the DS
  SETlcdE;
  PORTlcdDATA = 0b00110000;
  _delay_ms(4.5);
  UNSETlcdE;
  CLEARlcdD;
  _delay_us(1);
  // Section 2
  SETlcdE;
  PORTlcdDATA = 0b00110000;
  _delay_us(10);
  UNSETlcdE;
  CLEARlcdD;
  _delay_us(100);
  // Section 3
  SETlcdE;
  PORTlcdDATA = 0b00110000;
  _delay_us(1.5);
  UNSETlcdE;
  _delay_us(0.1);
  CLEARlcdD;
  // busyWait();
  _delay_ms(100);

  // Now we configure with 0b0011 first
  SETlcdE;
  PORTlcdDATA = 0b00110000;
  _delay_us(1.5);
  UNSETlcdE;
  _delay_us(0.1);
  CLEARlcdD;
  // busyWait();
  _delay_us(1);

  lcdDataWrite(0b00101000, CONTROLLER); // Set 4bit length, 2 lines, 5x7
                                        // busyWait();
  _delay_us(1);
  lcdDataWrite(0b00001000, CONTROLLER); // Display off
                                        // busyWait();
  _delay_us(1);
  lcdDataWrite(0b00000001, CONTROLLER); // Clear display
                                        // busyWait();
  _delay_us(1);
  lcdDataWrite(0b00000110, CONTROLLER); // Set entry mode
                                        // busyWait();
  _delay_us(1);
  lcdDataWrite(0b00001111, CONTROLLER); // Display on, Cursor on, Cursor blink
                                        // busyWait();
  _delay_us(1);
  PORTlcdDATA = 0b00000000;
}

void ledBlink() {
  ledOn;
  _delay_ms(500);
  ledOff;
}
