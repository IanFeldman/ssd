# ssd
2025 CPE senior project exploring nonvolatile storage.

## nor
512kb flash memory storage device. Interface over UART 9600 baud. Program with avrdude + ISP. See hardware schematic for details.

### Usage:
Read an address: ```r[address]```\
Erase an address: ```e[address]```\
Program an address: ```p[address][data]```

```[address]``` is 3 hex bytes\
```[data]``` is one hex byte

## nand
In development...

