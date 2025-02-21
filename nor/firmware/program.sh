#!/bin/bash

avrdude -C ../hardware/AT89S5x.conf -c stk500v1 -P /dev/ttyACM0 -p 89s51 -b 19200 -U flash:w:$1

