#include "pindefines.h"
#include <avr/sfr_defs.h>
#include <util/delay.h>

#define DISTANCE_CALC(usecs) (secs / 58)

static void sensorTrigger() {
  TRIGPORT |= _BV(TRIG);
  _delay_us(10);
  TRIGPORT &= ~(_BV(TRIG));
}

// Must wait 10mS between distance checks
long int sensorGetDistance() { sensorTrigger(); }
