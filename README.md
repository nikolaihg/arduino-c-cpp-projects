# arduino-cpp-projects
A collection of Arduino Uno projects written in C and C++ for learning embedded systems development.

## Overview
This repository contains various Arduino projects implemented in C and C++ to explore embedded programming concepts. The goal is to understand low-level hardware interaction, memory management, and efficient code practices for embedded development.

Since the goal is to learn C & C++ for embedded systems, some of the projects also contain a version of the code written in the Arduino language (.ino) as aprototype for ease of rewrites. 

## Compiling and uploading
Each of the c/c++ projects contains a makefile that can be used to compile, upload and clean the projects.
```bash
make
make upload
make clean
```

But you can also upload the arduino sketches located in the projects with the `arduino-cli`:
```bash
# 1. Install the core for your board (example for Arduino Uno)
arduino-cli core install arduino:avr
# 2. Create a new sketch (optional)
arduino-cli sketch new MySketch
# 3. Compile the sketch
arduino-cli compile --fqbn arduino:avr:uno /path/to/your/sketch
# 4. Upload to board (Linux / Unix)
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno /path/to/your/sketch
# Windows
arduino-cli upload -p COM7 --fqbn arduino:avr:uno /path/to/your/sketch
```

## Projects
- blink - Classic LED blink, exploring GPIO control and timing
    - .ino version: 
        - 340 bytes (1%) of program storage space
        - 9 bytes (0%) of dynamic memory
    - .c version: 
        - Program:  176 bytes (0.5% Full)
        - Data:       0 bytes (0.0% Full)
- tmp36 - Temperature sensor reading with ADC operations
    - .ino version:
        - 5108 bytes (15%) of program storage space
        - 232 bytes (11%) of dynamic memory
    - .c version:
        - Program:    4256 bytes (13.0% Full)
        - Data:         48 bytes (2.3% Full)
- ssd1306_tmp36 - Temperature sensor reading and displaying result on ssd1306 
    - .ino version:
        - 20026 bytes (62%) of program storage space
        - 631 bytes (30%) of dynamic memory, leaving 1417 bytes for local variables

Next up:
i2c
ssd1306+tmp36
More projects coming...

## Resources
### Datasheets
- **ATmega328P Datasheet** - [Microchip ATmega328P](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
- **TMP36 Datasheet** - [Analog Devices TMP36](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)
### Docs
- **AVR Libc Documentation** - [nongnu.org/avr-libc](https://www.nongnu.org/avr-libc/)
- **Arduino to AVR Guide** - [Arduino to bare AVR transition guide](https://www.arduino.cc/en/Hacking/PinMapping168)
- **AVRDUDE Documentation** - [AVRDUDE manual](https://www.nongnu.org/avrdude/)
- **AVR Fuse Calculator** - [engbedded.com/fusecalc](http://www.engbedded.com/fusecalc/)
### Books
- **"Make: AVR Programming"** by Elliot Williams
- **"Programming Arduino"** by Simon Monk  
- **"AVR Microcontroller and Embedded Systems"** by Mazidi
### Vidoes
 - **[Fundamentals of Microcontrollers - Arduino bare-metal breakdown"](https://www.youtube.com/playlist?list=PLNyfXcjhOAwOF-7S-ZoW2wuQ6Y-4hfjMR) by Mitch Davis
