#ifndef AVREZ_PINS_H
#define AVREZ_PINS_H

#ifndef F_CPU
#warning F_CPU (cpu frequency) is not defined.  Using the chips factory default of 1mhz
#warning You can fix this by either doing "#define F_CPU 1000000ULL" in your code or adding "-DF_CPU=1000000ULL" to the compilation line.
#warning Of course the number should be your actual chip clock speed or timing, (delay, sleep functions) and serial ports will not work.
#define F_CPU 1000000ULL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

/* To define a new chip:
Discover what the compiler calls your chip.  You need 2 names:
1. The name specified when running avr-g++, for example avr-g++ -mmcu=attiny24
   run: avr-g++ -mlist-devices --target-help
2. The name of the chip within C code, for example "__AVR_ATtiny24__"
   look at: <prefix dir>/avr/include/avr/io.h  On Linux: /usr/lib/avr/include/avr/io.h

Next, check the datasheet to determine whether your chip is exactly the same (programmatically) as a chip that's already been defined.  If that is the case you can easily add your chip name to one of the existing definitions below.

But if your chip is different, in this file you need to create a section for your chip near the bottom of the file.  Just before the  "#else #error" sections.  Do it like this:

[In this description, Things you need to change are bracketed in * since normal parens is valid c]

#elif defined (*C CODE NAME*) || defined (*ANOTHER C CODE NAME*) 
#else

Inside you need to define the chip as follows.  

#elif defined (*C CODE NAME*) || defined (*ANOTHER C CODE NAME*)

// First pick a name for the chip "family".  This will be the name for ALL chips that are programatically the same as yours.  If nothing is obvious, use the name of the smallest, cheapest variant.
#define PINOUT_*your canonical name*

// Next define the pins.  Use the following format:
#define pin*Name from datasheet* *bit index*,*direction register*,*port register*,*pin register*,*analog bit index*

// Normally the "io.h" file (or files it includes) should have defined constants for the values you need.  So it can be as easy as:
#define pinA0 PA0,DDRA,PORTA,PINA,0
// And note if your pin does NOT support an analog function, use "invalidPinFunction" as the last item, like this:
#define pinB0 PB0,DDRB,PORTB,PINB,invalidPinFunction

// Analog Section:  Note if you are not using analogRead() you *could* cheat and just define this to all zeros...
// Next, look up "analog reference" in the datasheet and make constants for the various references.  These constants allow you to choose the reference voltage for the analogRead function.  Here are all possible values:

enum
{
    AnalogReferenceVin = *a number here*,
    AnalogReference1_1volt = *a number here*,
    AnalogReferencePin = *a number here*
};

// Finally, you have to tell the system how many bits are used to select the analog reference voltage as follows.
#define AnalogMuxMask (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)

// Next, head over to the "Makefile" and add some logic to handle the different CPU= parameters...  you should be able to look at the existing examples to figure that out.
#else // done!

*/

// See /usr/lib/avr/include/avr/io.h for the symbol defined for your chip
// Or, avr-g++ -mlist-devices --target-help
#if defined (__AVR_ATtiny24__) || defined (__AVR_ATtiny24A__)  

// Family name
#define PINOUT_ATtiny24

//      name  bit dir  port  pin  analog bit
#define pinA0 PA0,DDRA,PORTA,PINA,0
#define pinA1 PA1,DDRA,PORTA,PINA,1
#define pinA2 PA2,DDRA,PORTA,PINA,2
#define pinA3 PA3,DDRA,PORTA,PINA,3
#define pinA4 PA4,DDRA,PORTA,PINA,4
#define pinA5 PA5,DDRA,PORTA,PINA,5
#define pinA6 PA6,DDRA,PORTA,PINA,6
#define pinA7 PA7,DDRA,PORTA,PINA,7

//      name  bit dir  port  pin  analog bit
#define pinB0 PB0,DDRB,PORTB,PINB,invalidPinFunction
#define pinB1 PB1,DDRB,PORTB,PINB,invalidPinFunction
#define pinB2 PB2,DDRB,PORTB,PINB,invalidPinFunction
#define pinB3 PB3,DDRB,PORTB,PINB,invalidPinFunction

enum
{
    AnalogReferenceVin = 0,
    AnalogReference1_1volt = 2,
    AnalogReferencePin = 1
};

#define AnalogMuxMask (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)

#elif defined (__AVR_ATtiny13A__)

// Family name
#define PINOUT_ATtiny13

//      name  bit dir  port  pin  analog bit
#define pinB0 0,DDRB,PORTB,PINB,invalidPinFunction
#define pinB1 1,DDRB,PORTB,PINB,invalidPinFunction
#define pinB2 2,DDRB,PORTB,PINB,1
#define pinB3 3,DDRB,PORTB,PINB,3
#define pinB4 4,DDRB,PORTB,PINB,2
#define pinB5 5,DDRB,PORTB,PINB,0

enum
{
    AnalogReferenceVin = 0,
    AnalogReference1_1volt = 1,
};

#define AnalogMuxMask (1<<MUX0)|(1<<MUX1)

#elif defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega168__) || defined (__AVR_ATmega168A__) || defined (__AVR_ATmega88__) || defined (__AVR_ATmega88A__) || defined (__AVR_ATmega48__) || defined (__AVR_ATmega48A__) || defined (__AVR_ATmega48P__)

// Family name
#define PINOUT_ATmega48

//      name  bit dir  port  pin  analog bit
#define pinB0 PB0,DDRB,PORTB,PINB,invalidPinFunction
#define pinB1 PB1,DDRB,PORTB,PINB,invalidPinFunction
#define pinB2 PB2,DDRB,PORTB,PINB,invalidPinFunction
#define pinB3 PB3,DDRB,PORTB,PINB,invalidPinFunction
#define pinB4 PB4,DDRB,PORTB,PINB,invalidPinFunction
#define pinB5 PB5,DDRB,PORTB,PINB,invalidPinFunction
#define pinB6 PB6,DDRB,PORTB,PINB,invalidPinFunction
#define pinB7 PB7,DDRB,PORTB,PINB,invalidPinFunction

#define pinC0 PC0,DDRC,PORTC,PINC,0
#define pinC1 PC1,DDRC,PORTC,PINC,1
#define pinC2 PC2,DDRC,PORTC,PINC,2
#define pinC3 PC3,DDRC,PORTC,PINC,3
#define pinC4 PC4,DDRC,PORTC,PINC,4
#define pinC5 PC5,DDRC,PORTC,PINC,5
#define pinADC6 invalidPinFunction,invalidPinFunction,invalidPinFunction,invalidPinFunction,6
#define pinADC7 invalidPinFunction,invalidPinFunction,invalidPinFunction,invalidPinFunction,7
#define chipTemp invalidPinFunction,invalidPinFunction,invalidPinFunction,invalidPinFunction,8

#define AnalogMuxMask (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)

#define pinD0 PD0,DDRD,PORTD,PIND,invalidPinFunction
#define pinD1 PD1,DDRD,PORTD,PIND,invalidPinFunction
#define pinD2 PD2,DDRD,PORTD,PIND,invalidPinFunction
#define pinD3 PD3,DDRD,PORTD,PIND,invalidPinFunction
#define pinD4 PD4,DDRD,PORTD,PIND,invalidPinFunction
#define pinD5 PD5,DDRD,PORTD,PIND,invalidPinFunction
#define pinD6 PD6,DDRD,PORTD,PIND,invalidPinFunction
#define pinD7 PD7,DDRD,PORTD,PIND,invalidPinFunction

enum
{
    AnalogReferenceVin = 1,
    AnalogReference1_1volt = 3,
    AnalogReferencePin = 0
};

// Add a new section here:
//#elif defined (*NEW CHIP*)

#else
#error
#error -------------------------------------------------------------
#error Sorry I have not defined pins for your chip!  Please take a
#error look at your chip datasheet and add a section to pins.h.
#error
#error Ignore all subsequent errors
#error -------------------------------------------------------------
#endif


// Defines that are the same for all chips.

enum
{
    INPUT = 0,
    OUTPUT= 1,
    ANALOG_INPUT=0,

    UP=1,
    FLOAT=0,

    HIGH=1,
    LOW=0
};

    
// Functions that are similar to the Arduino's Wired library:

//#define assignReg(reg,bits,value) do { if (value) asm("sbr %0,%1":"=r" reg:"I" bits:); else asm("cbr %0,%1":"=r" reg:"I" bits:); } while(0)
#define assignReg(_reg,_bits,_value) do { if (_value) _reg |=_bits; else _reg &=~(_bits); } while(0)

#define clearAndSetReg(_reg,_bits,_value) do { _reg &=~(_bits); _reg|=_value; } while(0)

#define getReg(_reg,_bits) (_reg &_bits)


#define pinMode(pin,direction) _pinMode(pin,direction)
              //#define _pinMode(num,dir,port,pin,direction) do { if (direction) dir |=( 1<<num); else dir &= ~(1<<num); } while(0)
#define _pinMode(num,dir,port,pin,ana,direction) do { if (direction != ANALOG_INPUT) assignReg(dir,(1<<num),direction); else assignReg(dir,(1<<num),INPUT); } while(0)

#define pinPull(pin,pullMode) _pinPull(pin,pullMode)
//#define _pinPull(num,dir,port,pin,pullMode) do { if (pullMode) port |= (1<<num); else port &= ~(1<<num); } while(0)
#define _pinPull(num,dir,port,pin,ana,pullMode) assignReg(port,(1<<num),pullMode)

//#define _pinToggle(num,dir,port,pinr) asm("sbr %0,%1":"=r" pinr:"I" (1<<num):)   // pinr |= (1<<num)
#define _pinToggle(num,dir,port,pinr,ana) pinr |= (1<<num)
#define pinToggle(pin) _pinToggle(pin)

#define digitalWrite(pin,value) _digitalWrite(pin,value)
#define _digitalWrite(num,dir,port,pinr,ana,value) assignReg(port,(1<<num),value)

#define digitalState(pin) _digitalState(pin)
#define _digitalState(num,dir,port,pinr,ana) (getReg(port,(1<<num))>0)

#define digitalRead(drpin) _digitalRead(drpin)
#define _digitalRead(drnum,drdir,drport,drpinr,ana) ((drpinr&(1<<drnum))>0)

#define analogInput(pin) _analogInput(pin)
#define _analogInput(drnum,drdir,drport,drpinr,analogChannel) AnalogInput.sample(analogChannel)

#endif
