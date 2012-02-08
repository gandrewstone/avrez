#
VERSION      := 0.1
PROGRAM_NAME := hello

# Chip and programmer 
DEVICE_PROGRAMMER := usbtiny

# define the CPU variable on the command line to the avr-g++ cpu name to get the default settings for that CPU
ifndef $(CPU)
# what gcc/g++ calls this chip. To list, try "avr-g++ -mlist-devices --target-help"
CPU_GCC           := attiny24a
# what avrdude calls this chip: To list, try "avrdude -c usbtiny"
CPU_AVRDUDE       := t24
# CPU frequency in hz
F_CPU             := 8000000ULL
endif

ifeq ($(CPU),attiny13a)
CPU_AVRDUDE := t13
CPU_GCC     := attiny13a
F_CPU       := 9600000ULL
endif

# FLAGS
CF      := -c -g -Os -mmcu=$(CPU_GCC) -DF_CPU=$(F_CPU) -I. 
LF      := -Os -mmcu=$(CPU_GCC) -Wl,--gc-sections -L -lm
# TOOLS
CC      := avr-g++

# Discover all the files
Hfiles  := $(wildcard *.h)
Cfiles  := $(wildcard *.cpp) $(wildcard *.c) $(wildcard *.pde)
Ofiles  := $(patsubst %.pde,%.o,$(patsubst %.c,%.o,$(patsubst %.cpp,%_$(CPU_GCC).o,$(Cfiles))))
PdeFile := $(wildcard *.pde)



default: programmedDevice_$(CPU_GCC).time

programmedDevice_$(CPU_GCC).time:  $(PROGRAM_NAME)_$(CPU_GCC).hex
	avrdude -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -v -U flash:w:$(PROGRAM_NAME)_$(CPU_GCC).hex
	touch programmedDevice_$(CPU_GCC).time

$(PROGRAM_NAME)_$(CPU_GCC).hex: $(Ofiles)
	$(CC) $(LF) -o $(PROGRAM_NAME)_$(CPU_GCC).elf $(Ofiles)
	avr-objcopy -j .text -j .data -O ihex  $(PROGRAM_NAME)_$(CPU_GCC).elf  $(PROGRAM_NAME)_$(CPU_GCC).hex

clean:
	-rm -f *.o *.hex *.elf programmedDevice_*.time

ifeq ($(CPU),attiny13a)

fuse_8mhz_internal:
	avrdude -c usbtiny -p t13 -U lfuse:w:0x3a:m

endif


%_$(CPU_GCC).o: %.cpp $(Hfiles)
	$(CC) $(CF) -o $@ $<

%_$(CPU_GCC).o: %.c $(Hfiles)
	$(CC) $(CF) -o $@ $<

%_$(CPU_GCC).o: %.pde $(Hfiles)
	$(CC) $(CF) -x c++ -o $@ $<

