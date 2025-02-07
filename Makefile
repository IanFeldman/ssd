# Makefile for SDCC with AT89S51 (outputting only .hex file)

CC = sdcc
CFLAGS = -mmcs51

all: nand.hex

nand.hex: main.c uart.rel flash.rel
	$(CC) -o nand.hex main.c uart.rel flash.rel

uart.rel: uart.c uart.h
	$(CC) $(CFLAGS) -c -o uart.rel uart.c

flash.rel: flash.c flash.h
	$(CC) $(CFLAGS) -c -o flash.rel flash.c

clean:
	rm -f *.hex *.o *.asm *.cdb *.ihx *.lst *.lk  *.map  *.mem  *.rel  *.rst  *.sym

