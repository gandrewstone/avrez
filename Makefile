#
VERSION      := 0.1
PROGRAM_NAME := hello

# Chip and programmer 
DEVICE_PROGRAMMER := usbtiny
# what gcc/g++ calls this chip. To list, try "avr-g++ -mlist-devices --target-help"
CPU_GCC           := attiny24a 
# what avrdude calls this chip: To list, try "avrdude -c usbtiny"
CPU_AVRDUDE       := t24
# CPU frequency in hz
F_CPU             := 8000000ULL

# FLAGS
CF      := -c -g -Os -mmcu=$(CPU_GCC) -DF_CPU=$(F_CPU) -I. 
LF      := -Os -mmcu=$(CPU_GCC) -Wl,--gc-sections -L -lm
# TOOLS
CC      := avr-g++

# Discover all the files
Hfiles  := $(wildcard *.h)
Cfiles  := $(wildcard *.cpp) $(wildcard *.c) $(wildcard *.pde)
Ofiles  := $(patsubst %.pde,%.o,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(Cfiles))))
PdeFile := $(wildcard *.pde)



default: programmedDevice.time

programmedDevice.time:  $(PROGRAM_NAME).hex
	avrdude -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -v -U flash:w:$(PROGRAM_NAME)
	touch writeDevice.time

$(PROGRAM_NAME).hex: $(Ofiles)
	$(CC) $(LF) -o $(PROGRAM_NAME).elf $(Ofiles)
	avr-objcopy -j .text -j .data -O ihex  $(PROGRAM_NAME).elf  $(PROGRAM_NAME).hex

%.o: %.cpp $(Hfiles)
	$(CC) $(CF) -o $@ $<

%.o: %.c $(Hfiles)
	$(CC) $(CF) -o $@ $<

%.o: %.pde $(Hfiles)
	$(CC) $(CF) -x c++ -o $@ $<

clean:
	-rm -f *.o *.hex *.elf programmedDevice.time

