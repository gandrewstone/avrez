/* Basic embedded hello world -- blink a LED
   
   Compilation and device programming notes:
   http://coderlut.blogspot.com/2012/02/avr-compilation-and-device-programming.html

   sudo apt-get install avrdude gcc-avr avr-libc binutils-avr
   
   // Find out what your CPU is named both in code and on the command line
   avr-g++ -mlist-devices --target-help
   // Compile this
   avr-g++ -mmcu=attiny24a -Os hello.cpp -o hello.o
   // Convert it into a format avrdude can understand 
   avr-objcopy -j .text -j .data -O ihex  hello.o  hello.hex
   // program the chip:
   sudo avrdude -c usbtiny -p t24 -v -U flash:w:hello.hex
   
 */

#include "pins.h"

// Hook a LED up to this pin: 5v->1k resistor->LED->pin
#define LED_PIN pinB0  // B0 is on most chips but you can change this to any pin your chip has

/* If a LED is connected to the pin (with resistor), it should show bright,off,bright,off,dim,off. */
int main(void)
{
  while(1)
  {
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,1);
  _delay_ms(1000);
  digitalWrite(LED_PIN,0);
  _delay_ms(1000);
  pinToggle(LED_PIN);
  _delay_ms(1000);
  pinToggle(LED_PIN);
  _delay_ms(1000);  
  pinMode(LED_PIN,INPUT);
  pinPull(LED_PIN,UP);
  _delay_ms(1000);
  pinPull(LED_PIN,FLOAT);
  _delay_ms(1000);
  }
  return 0;
}
