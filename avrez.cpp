#include "pins.h"
#include "avrez.h"

AnalogComparator Comparator;
AnalogToDigitalConverter AnalogInput;

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

void AnalogComparator::begin(AnalogComparatorMode mode,byte pinP,byte pinN)
{
  ADCSRB |= (1<<ACME);
  clearAndSetReg(ACSR,(1<<ACIS0)|(1<<ACIS1),((byte)mode)<<ACIS0);
  resume();
}

void AnalogComparator::pause()
{
  assignReg(ACSR,(1<<ACIE) | (1<<ACD),0);  // Turn off the interrupt and power
}
void AnalogComparator::resume()
{
  assignReg(ACSR,(1<<ACIE) | (1<<ACD),1);  // Turn on the interrupt and power
}


void AnalogToDigitalConverter::begin(byte analogReference)
{
  assignReg(ADMUX,(1<<REFS0),analogReference);

  clearAndSetReg(ADCSRA,(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0),biggestBit(F_CPU/MAX_ADC_CLOCK)<<ADPS0);  // Set the fastest clock possible

  resume();
  sample(0);  // Throw away the first sample because its bad.
}

void AnalogToDigitalConverter::pause()
{
  assignReg(ADCSRA,(1<<ADEN),0);  // turn on power
}

void AnalogToDigitalConverter::resume()
{
  assignReg(ADCSRA,(1<<ADEN),1);  // turn on power
}

uint16_t AnalogToDigitalConverter::sample(byte channel)
{
  //while(getReg(ADCSRA,(1<<ADSC)));  // Wait for prior sample 
  clearAndSetReg(ADMUX,AnalogMuxMask,channel);
  assignReg(ADCSRA,(1<<ADSC),1);
  while(getReg(ADCSRA,(1<<ADSC)));  // Wait for prior sample
  uint16_t result = ADCL;
  result = result | (((uint16_t)(ADCH))<<8);
  return result;
}
