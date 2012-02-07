#include "pins.h"

void delay(unsigned long int amt)
{
  // _delay_ms needs a constant
  // I do these while loops so the CPU isn't thrashing (at least in my code)
  // and that should make the time more accurate.
  while (amt>10000) { amt-=10000; _delay_ms(10000);}
  while (amt>1000) { amt-=1000; _delay_ms(1000);}
  while (amt>100) { amt-=100; _delay_ms(100);}
  while (amt>10) { amt-=10; _delay_ms(10);}
  while(amt) { amt--; _delay_ms(1);}
}

