# ==== Microcontroller settings ====
MCU        = atmega328p
F_CPU      = 16000000UL
BAUD       = 9600                # UART baud for your code

# ==== Toolchain ====
CXX        = avr-g++             # use C++ compiler
OBJCOPY    = avr-objcopy
OBJDUMP    = avr-objdump
SIZE       = avr-size

# ==== Programmer (Arduino bootloader) ====
PROGRAMMER   = arduino
PORT         = COM7
SERIAL_BAUD  = 115200            
AVRDUDE      = avrdude

# ==== Project ====
TARGET    = main
SRCDIR    = src
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS   = $(SOURCES:.cpp=.o)
DEPS      = $(OBJECTS:.o=.d)

# ==== Flags ====
COMMON_DEFS  = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD)
COMMON_MCU   = -mmcu=$(MCU)

CXXFLAGS  = $(COMMON_MCU) $(COMMON_DEFS) -Os -Wall -Wextra -std=c++20 \
            -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
            -ffunction-sections -fdata-sections -MMD -MP
# Uncomment to enable LTO (make sure to use the same at link time)
# CXXFLAGS += -flto

LDFLAGS   = $(COMMON_MCU) -Wl,--gc-sections
# LDFLAGS  += -flto

# ==== Targets ====
.PHONY: all clean upload flash size disasm

all: $(TARGET).hex size

# Compile C++ sources
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link
$(TARGET).elf: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

# Hex
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Size
size: $(TARGET).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

# Upload via Arduino bootloader
upload flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(SERIAL_BAUD) -D -U flash:w:$<:i

# Disassembly + source interleave to .lst
disasm: $(TARGET).elf
	$(OBJDUMP) -S -d $< > $(TARGET).lst
	@echo "Wrote $(TARGET).lst"

# Clean
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET).elf $(TARGET).hex $(TARGET).lst

# Include auto-generated dependency files
-include $(DEPS)
