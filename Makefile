# Makefile for SDCC with AT89S51 (outputting only .hex file)

# Compiler and flags
CC = sdcc
CFLAGS = -mmcs51

# Source and output files
SRC = main.c
OUT = nand

# Default target
all: $(OUT)

# Rule to build the .hex file
$(OUT): $(SRC)
	$(CC) -o $(OUT).hex $(CFLAGS) $(SRC)

# Clean up generated files (e.g., .asm, .cdb, .ihx, etc.)
clean:
	rm -f $(OUT).hex $(OUT).asm $(OUT).cdb $(OUT).ihx $(OUT).lst $(OUT).lk  $(OUT).map  $(OUT).mem  $(OUT).rel  $(OUT).rst  $(OUT).sym

