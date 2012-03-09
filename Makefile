#
CPU     ?= attiny13a
COMPORT ?= COM11

VERSION      := 0.1
PROGRAM_NAME := hello

#MSWINDOWS    := 1
ARDUINO_DIR  := c:\arduino-1.0

# Chip and programmer 
#DEVICE_PROGRAMMER := usbtiny
ifdef MSWINDOWS
DEVICE_PROGRAMMER := stk500v1 -P $(COMPORT)
else
DEVICE_PROGRAMMER := stk500v1 -P /dev/ttyACM0
endif

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
ifeq ($(CPU),atmega48a)
CPU_AVRDUDE := m48
CPU_GCC     := atmega48a
F_CPU       := 8000000ULL
endif

# FLAGS
CF      := -c -g -Os -mmcu=$(CPU_GCC) -DF_CPU=$(F_CPU) -I. 
LF      := -Os -mmcu=$(CPU_GCC) -Wl,--gc-sections -L -lm
# TOOLS
ifdef MSWINDOWS
CC          := $(ARDUINO_DIR)\hardware\tools\avr\bin\avr-g++
CF          += -I$(ARDUINO_DIR)\hardware\tools\avr\avr\include -I$(ARDUINO_DIR)\hardware\tools\avr\avr\include\avr
avr_objcopy ?= $(ARDUINO_DIR)\hardware\tools\avr\bin\avr-objcopy
avrdude     ?= mode $(COMPORT):dtr=on && $(ARDUINO_DIR)\hardware\tools\avr\bin\avrdude -C $(ARDUINO_DIR)\hardware\tools\avr\etc\avrdude.conf
else
CC          := avr-g++
avr_objcopy ?= avr-objcopy
avrdude     ?= avrdude
endif

# Discover all the files
Hfiles  := $(wildcard *.h)
Cfiles  := $(wildcard *.cpp) $(wildcard *.c) $(wildcard *.pde)
Ofiles  := $(patsubst %.pde,%.o,$(patsubst %.c,%.o,$(patsubst %.cpp,%_$(CPU_GCC).o,$(Cfiles))))
PdeFile := $(wildcard *.pde)



default: programmedDevice_$(CPU_GCC).time

programmedDevice_$(CPU_GCC).time:  $(PROGRAM_NAME)_$(CPU_GCC).hex
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -v -U flash:w:$(PROGRAM_NAME)_$(CPU_GCC).hex
	touch programmedDevice_$(CPU_GCC).time

$(PROGRAM_NAME)_$(CPU_GCC).hex: $(Ofiles)
	$(CC) $(LF) -o $(PROGRAM_NAME)_$(CPU_GCC).elf $(Ofiles)
	$(avr_objcopy) -j .text -j .data -O ihex  $(PROGRAM_NAME)_$(CPU_GCC).elf  $(PROGRAM_NAME)_$(CPU_GCC).hex

clean:
	-rm -f *.o *.hex *.elf programmedDevice_*.time

dumpchip_srec: 
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -U lfuse:r:lfuse_$(CPU_GCC).hex:i -U hfuse:r:hfuse_$(CPU_GCC).hex:i -U efuse:r:efuse_$(CPU_GCC).hex:i -U eeprom:r:eeprom_$(CPU_GCC).hex:i -U flash:r:flash_$(CPU_GCC).hex:i -U lock:r:lock_$(CPU_GCC).hex:i -U signature:r:sig_$(CPU_GCC).hex:i 

dumpchip: 
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -U lfuse:r:lfuse_$(CPU_GCC).bin:r -U hfuse:r:hfuse_$(CPU_GCC).bin:r -U eeprom:r:eeprom_$(CPU_GCC).bin:r -U flash:r:flash_$(CPU_GCC).bin:r -U lock:r:lock_$(CPU_GCC).bin:r -U signature:r:sig_$(CPU_GCC).bin:r -U efuse:r:efuse_$(CPU_GCC).bin:r 

check:
	$(avrdude) -v -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE)

ifeq ($(CPU),attiny13a)

fuse_8mhz_internal:
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -U lfuse:w:0x3a:m

fuse_1mhz_internal:
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -U lfuse:w:0x2a:m

fuse_slow_clock:
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p $(CPU_AVRDUDE) -U lfuse:w:0x29:m

endif
ifeq ($(CPU),atmega48a)

fuse_8mhz_internal:
	$(avrdude) -c $(DEVICE_PROGRAMMER) -p m48 -U lfuse:w:0xe2:m
endif


%_$(CPU_GCC).o: %.cpp $(Hfiles)
	$(CC) $(CF) -o $@ $<

%_$(CPU_GCC).o: %.c $(Hfiles)
	$(CC) $(CF) -o $@ $<

%_$(CPU_GCC).o: %.pde $(Hfiles)
	$(CC) $(CF) -x c++ -o $@ $<

