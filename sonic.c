#include "pindefines.h"
#include "serial.h"
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

static void sensorTrigger() {
  usart_print("Triggering!");
  TRIGPORT |= _BV(TRIG);
  _delay_us(11);
  TRIGPORT &= ~(_BV(TRIG));
  usart_print("Untriggered!");
}

// Must wait 10mS between distance checks
int sensorGetDistance() {
  TCNT1 = 0;
  sensorTrigger();
  while (!(ECHOPORT & (1 << ECHO)))
    ;
  TCNT1 = 0;
  while (ECHOPORT & (1 << ECHO)) { // Wait for the echo pin to go low
    usart_print("Waiting\n\r");
    // if (TCNT1 > 30000) {
    //   break; // Escape loop if it takes longer than 30ms
    // }
  }
  uint16_t time_elapsed = TCNT1;
  time_elapsed /= USECCYCLES; // Convert time to usecs
  return time_elapsed / 58;
}
