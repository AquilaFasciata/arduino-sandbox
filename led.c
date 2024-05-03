#include <avr/io.h>
#include <util/delay.h>

// Reg Sel  Pin 12
// Enable   Pin 11
// Data 4-7 Pin 5-2
int main(void) {
  // Enable pins to output mode
  DDRB |= (1 << DDB4);
  DDRB |= (1 << DDB3);
  
  DDRD |= (1 << DDD5);
  DDRD |= (1 << DDD4);
  DDRD |= (1 << DDD3);
  DDRD |= (1 << DDD2);



	while(1) {

	}
}
