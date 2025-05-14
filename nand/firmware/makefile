# Makefile for AVR-GCC with atmega32u2 (outputting only .hex file)

CC = avr-gcc
CCPY = avr-objcopy
CFLAGS = -mmcu=atmega32u2 -Wall -Os

all: nand.hex

nand.hex: nand.elf
	$(CCPY) -j .text -j .data -O ihex nand.elf nand.hex

nand.elf: main.c uart.c flash.c
	$(CC) $(CFLAGS) -o nand.elf main.c uart.c flash.c

clean:
	rm -f nand.elf nand.hex

flash: nand.hex
	avrdude -c avrisp -P /dev/ttyACM0 -p m32u2 -b 19200 -U flash:w:nand.hex -F

fuses:
	avrdude -c avrisp -p m32u2 -P /dev/ttyACM0 -b 19200 -U lfuse:w:0xDE:m -U hfuse:w:0xD9:m -F

