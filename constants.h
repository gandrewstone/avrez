
// With constants, this should be completely optimized away
#define biggestBit(x) ((x>=128) ? 7: (x>=64) ? 6 : (x>=32) ? 5 : (x>=16) ? 4 : (x>=8) ? 3 : (x>=2) ? 2 : (x>=1) ? 1 : 0)

enum
{
    
#if defined(__AVR_ATtiny13A__)
    MAX_ADC_CLOCK = 200000ULL,
#elif defined(__AVR_ATmega48A__) | defined(__AVR_ATmega48__) | defined(__AVR_ATmega48P__) | defined(__AVR_ATmega48PA__)
    MAX_ADC_CLOCK = 200000ULL,
#else
#warning Maximum analog to digital clock is not explicitly set for your CPU, using 200000hz    
    MAX_ADC_CLOCK = 200000ULL,
#endif    
};
