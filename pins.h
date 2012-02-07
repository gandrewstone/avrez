#ifndef PINS_H
#define PINS_H

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

// See /usr/lib/avr/include/avr/io.h for the symbol defined for your chip
// Or, avr-g++ -mlist-devices --target-help
#if defined (__AVR_ATtiny24__) || defined (__AVR_ATtiny24A__)  

#define pinA0 PA0,DDRA,PORTA,PINA
#define pinA1 PA1,DDRA,PORTA,PINA
#define pinA2 PA2,DDRA,PORTA,PINA
#define pinA3 PA3,DDRA,PORTA,PINA
#define pinA4 PA4,DDRA,PORTA,PINA
#define pinA5 PA5,DDRA,PORTA,PINA
#define pinA6 PA6,DDRA,PORTA,PINA
#define pinA7 PA7,DDRA,PORTA,PINA

#define pinB0 PB0,DDRB,PORTB,PINB
#define pinB1 PB1,DDRB,PORTB,PINB
#define pinB2 PB2,DDRB,PORTB,PINB
#define pinB3 PB3,DDRB,PORTB,PINB

#elif defined (__AVR_ATtiny13A__)

#define pinB0 PB0,DDRB,PORTB,PINB
#define pinB1 PB1,DDRB,PORTB,PINB
#define pinB2 PB2,DDRB,PORTB,PINB
#define pinB3 PB3,DDRB,PORTB,PINB
#define pinB4 PB4,DDRB,PORTB,PINB
#define pinB5 PB5,DDRB,PORTB,PINB

#elif defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega168__) || defined (__AVR_ATmega168A__) || defined (__AVR_ATmega88__) || defined (__AVR_ATmega88A__) || defined (__AVR_ATmega48__) || defined (__AVR_ATmega48A__) || defined (__AVR_ATmega48P__)
#define pinB0 PB0,DDRB,PORTB,PINB
#define pinB1 PB1,DDRB,PORTB,PINB
#define pinB2 PB2,DDRB,PORTB,PINB
#define pinB3 PB3,DDRB,PORTB,PINB
#define pinB4 PB4,DDRB,PORTB,PINB
#define pinB5 PB5,DDRB,PORTB,PINB
#define pinB6 PB6,DDRB,PORTB,PINB
#define pinB7 PB7,DDRB,PORTB,PINB

#define pinC0 PC0,DDRC,PORTC,PINC
#define pinC1 PC1,DDRC,PORTC,PINC
#define pinC2 PC2,DDRC,PORTC,PINC
#define pinC3 PC3,DDRC,PORTC,PINC
#define pinC4 PC4,DDRC,PORTC,PINC
#define pinC5 PC5,DDRC,PORTC,PINC
//#define pinC6 PC6,DDRC,PORTC,PINC
//#define pinC7 PC7,DDRC,PORTC,PINC

#define pinD0 PD0,DDRD,PORTD,PIND
#define pinD1 PD1,DDRD,PORTD,PIND
#define pinD2 PD2,DDRD,PORTD,PIND
#define pinD3 PD3,DDRD,PORTD,PIND
#define pinD4 PD4,DDRD,PORTD,PIND
#define pinD5 PD5,DDRD,PORTD,PIND
#define pinD6 PD6,DDRD,PORTD,PIND
#define pinD7 PD7,DDRD,PORTD,PIND

#else
#error
#error -------------------------------------------------------------
#error Sorry I have not defined pins for your chip!  Please take a
#error look at your chip datasheet and add a section to pins.h.
#error
#error Ignore all subsequent errors
#error -------------------------------------------------------------
#endif

enum
{
    INPUT = 0,
    OUTPUT=1,

    UP=1,
    FLOAT=0,

    HIGH=1,
    LOW=0
};

    


//#define assignReg(reg,bits,value) do { if (value) asm("sbr %0,%1":"=r" reg:"I" bits:); else asm("cbr %0,%1":"=r" reg:"I" bits:); } while(0)
#define assignReg(_reg,_bits,_value) do { if (_value) _reg |=_bits; else _reg &=~(_bits); } while(0)

#define getReg(_reg,_bits) (_reg &_bits)


#define pinMode(pin,direction) _pinMode(pin,direction)
              //#define _pinMode(num,dir,port,pin,direction) do { if (direction) dir |=( 1<<num); else dir &= ~(1<<num); } while(0)
#define _pinMode(num,dir,port,pin,direction) assignReg(dir,(1<<num),direction)
                                             
#define pinPull(pin,pullMode) _pinPull(pin,pullMode)
//#define _pinPull(num,dir,port,pin,pullMode) do { if (pullMode) port |= (1<<num); else port &= ~(1<<num); } while(0)
#define _pinPull(num,dir,port,pin,pullMode) assignReg(port,(1<<num),pullMode)

//#define _pinToggle(num,dir,port,pinr) asm("sbr %0,%1":"=r" pinr:"I" (1<<num):)   // pinr |= (1<<num)
#define _pinToggle(num,dir,port,pinr) pinr |= (1<<num)
#define pinToggle(pin) _pinToggle(pin)

#define digitalWrite(pin,value) _digitalWrite(pin,value)
#define _digitalWrite(num,dir,port,pinr,value) assignReg(port,(1<<num),value)

#define digitalState(pin) _digitalState(pin)
#define _digitalState(num,dir,port,pinr) (getReg(port,(1<<num))>0)


#define digitalRead(drpin) _digitalRead(drpin)
#define _digitalRead(drnum,drdir,drport,drpinr) ((drpinr&(1<<drnum))>0)


#endif
