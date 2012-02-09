#ifndef AVREZ_H
#define AVREZ_H

#include "pins.h"
#include "constants.h"

typedef uint8_t byte;

//?? Delay for this many milliseconds
void delay(unsigned long int amt);

typedef enum
{
    RISING = 3,
    FALLING = 2,
    TOGGLE  = 0,
} AnalogComparatorMode;

    

class AnalogComparator
{
public:
    void begin(AnalogComparatorMode mode, byte pinP=0xff,byte pinN=0xff);
    void pause();
    void resume();
    void enableInterrupt();  //
    void disableInterrupt();  //      
};

extern AnalogComparator Comparator;


class AnalogToDigitalConverter
{
public:
    void begin(byte analogReference=AnalogReferenceVin);  // values: AnalogReferenceVin, AnalogReference1_1volt, AnalogReferencePin may not all exist for your part
    void pause();
    void resume();
    void enableInterrupt() { assignReg(ADCSRA,(1<<ADIE),1); }        
    void disableInterrupt() { assignReg(ADCSRA,(1<<ADIE),0); }  
    uint16_t sample(byte channel);
};

extern AnalogToDigitalConverter AnalogInput;




#endif
