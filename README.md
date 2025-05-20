# ssd
2025 Cal Poly EE/CPE senior project exploring nonvolatile flash storage. Includes a [prototype design](#nor) using an 8051 and small NOR flash IC and the [final design](#nand) with a modern Atmel microcontroller and multiple high-density NAND flash ICs on a custom PCB.

## nand
4Gb NAND flash memory board with native USB interface. Under development.

## nor
Prototype breadboard 512kB flash memory storage device. Interface over UART at 9600 baud. Compile with SDCC and program with avrdude. See hardware schematic for hardware details.

### Firmware Build and Flash Instructions (Linux)
```sh
# Install dependencies
sudo apt install sdcc

# Clone this repo
git clone https://github.com/IanFeldman/ssd.git
cd ssd

# Compile and flash firmware using ISP
make
./program.sh
```

### Usage:
Connect a serial cable to ```RXD``` and ```TXD``` on the microcontroller. Open a terminal with:\
```screen /dev/[path-to-serial-cable] -b 9600```

### Commands:
- Read an address ```r[address]```
- Erase an address ```e[address]```
- Program an address ```p[address][data]```

Where:
- ```[address]``` is 3 hex bytes
- ```[data]``` is one hex byte
