#include <avr/io.h>
#include <string.h>

void usart_transmit(unsigned char data) {
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void usart_init(unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  // Enable
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // 8 bit char; 2 bit stop
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void usart_print(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (!(i > 600)) {
      usart_transmit(str[i]);
    } else {
      return;
    }
  }
}
