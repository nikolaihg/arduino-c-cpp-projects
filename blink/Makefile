# Microcontroller settings
MCU = atmega328p
F_CPU = 16000000UL
BAUD = 9600

# Compiler settings
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size

# Programmer settings
PROGRAMMER = arduino
PORT = COM7
AVRDUDE = avrdude

# Project settings
TARGET = main
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DBAUD=$(BAUD)
CFLAGS += -Os -Wall -Wextra -std=c++20
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -ffunction-sections -fdata-sections

# Linker flags
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections

# Default target
all: $(TARGET).hex size

# Compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Create hex file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Show size information
size: $(TARGET).elf
	$(SIZE) --format=avr --mcu=$(MCU) $(TARGET).elf

# Upload to Arduino
upload: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:w:$(TARGET).hex

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).hex

# Show disassembly
disasm: $(TARGET).elf
	$(OBJDUMP) -d $

.PHONY: all clean upload size disasm