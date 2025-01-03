#include "pindefines.h"
#include "serial.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

#define DISTANCE_CALC(usecs) (usecs / 58)
#define FOSC 16000000
#define USECCYCLES FOSC / 1000000

void sensorInit() {
  // Set the Counter control
  // Source = Clock with no prescaling
  TCCR1B |= (1 << CS10);
  DDRB |= (1 << TRIG);
  DDRB &= ~(1 << ECHO);
}

// Must wait 10mS between distance checks
int sensorGetDistance() {
  TRIGPORT |= _BV(TRIG);

  _delay_us(10);
  int num_loops = 0;

  TRIGPORT &= ~(_BV(TRIG));
  usart_print("Letting previous finish before measuring");
  while ((ECHOPORT & (1 << ECHO)))
    ;
  while (!(ECHOPORT & (1 << ECHO)))
    ;
  TCNT1 = 0;
  while ((ECHOPORT & (1 << ECHO))) { // Wait for the echo pin to go low
    usart_print("Waiting\n\r");
    num_loops++;
  }
  return num_loops / 58;
}
