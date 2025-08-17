# Simple Arduino Makefile for C/C++
# Usage: make upload (or just 'make' to build)

# ==== Hardware Settings ====
MCU = atmega328p
F_CPU = 16000000UL
PORT = COM7

# ==== Project ====
TARGET = main
SRCDIR = src

# Find all C and C++ source files
C_SOURCES = $(wildcard $(SRCDIR)/*.c)
CPP_SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(C_SOURCES:.c=.o) $(CPP_SOURCES:.cpp=.o)

# ==== Toolchain ====
CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

# ==== Compiler Flags ====
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=c99
CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -std=c++11
LDFLAGS = -mmcu=$(MCU)

# ==== Default Target ====
all: $(TARGET).hex size

# ==== Build Rules ====
# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files  
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link
$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Create hex file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Show size
size: $(TARGET).elf
	@echo "Program size:"
	$(SIZE) --format=avr --mcu=$(MCU) $<

# Upload to Arduino
upload: $(TARGET).hex
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b 115200 -D -U flash:w:$<:i

# Clean up
clean:
	rm -f $(SRCDIR)/*.o $(TARGET).elf $(TARGET).hex

.PHONY: all size upload clean