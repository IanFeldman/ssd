                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _uart_print_esc
                                     13 	.globl _uart_init
                                     14 	.globl _flash_delay
                                     15 	.globl _flash_init
                                     16 ;--------------------------------------------------------
                                     17 ; special function registers
                                     18 ;--------------------------------------------------------
                                     19 	.area RSEG    (ABS,DATA)
      000000                         20 	.org 0x0000
                                     21 ;--------------------------------------------------------
                                     22 ; special function bits
                                     23 ;--------------------------------------------------------
                                     24 	.area RSEG    (ABS,DATA)
      000000                         25 	.org 0x0000
                                     26 ;--------------------------------------------------------
                                     27 ; overlayable register banks
                                     28 ;--------------------------------------------------------
                                     29 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                         30 	.ds 8
                                     31 ;--------------------------------------------------------
                                     32 ; internal ram data
                                     33 ;--------------------------------------------------------
                                     34 	.area DSEG    (DATA)
                                     35 ;--------------------------------------------------------
                                     36 ; overlayable items in internal ram 
                                     37 ;--------------------------------------------------------
                                     38 ;--------------------------------------------------------
                                     39 ; Stack segment in internal ram 
                                     40 ;--------------------------------------------------------
                                     41 	.area	SSEG
      00002D                         42 __start__stack:
      00002D                         43 	.ds	1
                                     44 
                                     45 ;--------------------------------------------------------
                                     46 ; indirectly addressable internal ram data
                                     47 ;--------------------------------------------------------
                                     48 	.area ISEG    (DATA)
                                     49 ;--------------------------------------------------------
                                     50 ; absolute internal ram data
                                     51 ;--------------------------------------------------------
                                     52 	.area IABS    (ABS,DATA)
                                     53 	.area IABS    (ABS,DATA)
                                     54 ;--------------------------------------------------------
                                     55 ; bit data
                                     56 ;--------------------------------------------------------
                                     57 	.area BSEG    (BIT)
                                     58 ;--------------------------------------------------------
                                     59 ; paged external ram data
                                     60 ;--------------------------------------------------------
                                     61 	.area PSEG    (PAG,XDATA)
                                     62 ;--------------------------------------------------------
                                     63 ; external ram data
                                     64 ;--------------------------------------------------------
                                     65 	.area XSEG    (XDATA)
                                     66 ;--------------------------------------------------------
                                     67 ; absolute external ram data
                                     68 ;--------------------------------------------------------
                                     69 	.area XABS    (ABS,XDATA)
                                     70 ;--------------------------------------------------------
                                     71 ; external initialized ram data
                                     72 ;--------------------------------------------------------
                                     73 	.area XISEG   (XDATA)
                                     74 	.area HOME    (CODE)
                                     75 	.area GSINIT0 (CODE)
                                     76 	.area GSINIT1 (CODE)
                                     77 	.area GSINIT2 (CODE)
                                     78 	.area GSINIT3 (CODE)
                                     79 	.area GSINIT4 (CODE)
                                     80 	.area GSINIT5 (CODE)
                                     81 	.area GSINIT  (CODE)
                                     82 	.area GSFINAL (CODE)
                                     83 	.area CSEG    (CODE)
                                     84 ;--------------------------------------------------------
                                     85 ; interrupt vector 
                                     86 ;--------------------------------------------------------
                                     87 	.area HOME    (CODE)
      000000                         88 __interrupt_vect:
      000000 02 00 29         [24]   89 	ljmp	__sdcc_gsinit_startup
      000003 32               [24]   90 	reti
      000004                         91 	.ds	7
      00000B 32               [24]   92 	reti
      00000C                         93 	.ds	7
      000013 32               [24]   94 	reti
      000014                         95 	.ds	7
      00001B 32               [24]   96 	reti
      00001C                         97 	.ds	7
      000023 02 01 C4         [24]   98 	ljmp	_uart_isr
                                     99 ;--------------------------------------------------------
                                    100 ; global & static initialisations
                                    101 ;--------------------------------------------------------
                                    102 	.area HOME    (CODE)
                                    103 	.area GSINIT  (CODE)
                                    104 	.area GSFINAL (CODE)
                                    105 	.area GSINIT  (CODE)
                                    106 	.globl __sdcc_gsinit_startup
                                    107 	.globl __sdcc_program_startup
                                    108 	.globl __start__stack
                                    109 	.globl __mcs51_genXINIT
                                    110 	.globl __mcs51_genXRAMCLEAR
                                    111 	.globl __mcs51_genRAMCLEAR
                                    112 	.area GSFINAL (CODE)
      0000D0 02 00 26         [24]  113 	ljmp	__sdcc_program_startup
                                    114 ;--------------------------------------------------------
                                    115 ; Home
                                    116 ;--------------------------------------------------------
                                    117 	.area HOME    (CODE)
                                    118 	.area HOME    (CODE)
      000026                        119 __sdcc_program_startup:
      000026 02 00 D3         [24]  120 	ljmp	_main
                                    121 ;	return from main will return to caller
                                    122 ;--------------------------------------------------------
                                    123 ; code
                                    124 ;--------------------------------------------------------
                                    125 	.area CSEG    (CODE)
                                    126 ;------------------------------------------------------------
                                    127 ;Allocation info for local variables in function 'main'
                                    128 ;------------------------------------------------------------
                                    129 ;	main.c:4: void main()
                                    130 ;	-----------------------------------------
                                    131 ;	 function main
                                    132 ;	-----------------------------------------
      0000D3                        133 _main:
                           000007   134 	ar7 = 0x07
                           000006   135 	ar6 = 0x06
                           000005   136 	ar5 = 0x05
                           000004   137 	ar4 = 0x04
                           000003   138 	ar3 = 0x03
                           000002   139 	ar2 = 0x02
                           000001   140 	ar1 = 0x01
                           000000   141 	ar0 = 0x00
                                    142 ;	main.c:7: uart_init();
      0000D3 12 00 F3         [24]  143 	lcall	_uart_init
                                    144 ;	main.c:8: flash_init();
      0000D6 12 02 0B         [24]  145 	lcall	_flash_init
                                    146 ;	main.c:11: uart_print_esc(CLEAR_SCREEN);
      0000D9 90 03 30         [24]  147 	mov	dptr,#___str_0
      0000DC 75 F0 80         [24]  148 	mov	b,#0x80
      0000DF 12 01 6F         [24]  149 	lcall	_uart_print_esc
                                    150 ;	main.c:12: uart_print_esc(HOME_CURSOR);
      0000E2 90 03 34         [24]  151 	mov	dptr,#___str_1
      0000E5 75 F0 80         [24]  152 	mov	b,#0x80
      0000E8 12 01 6F         [24]  153 	lcall	_uart_print_esc
                                    154 ;	main.c:13: flash_delay(0xFF);
      0000EB 75 82 FF         [24]  155 	mov	dpl,#0xff
      0000EE 12 02 E1         [24]  156 	lcall	_flash_delay
                                    157 ;	main.c:29: while (1)
      0000F1                        158 00102$:
                                    159 ;	main.c:32: }
      0000F1 80 FE            [24]  160 	sjmp	00102$
                                    161 	.area CSEG    (CODE)
                                    162 	.area CONST   (CODE)
                                    163 	.area CONST   (CODE)
      000330                        164 ___str_0:
      000330 5B 32 4A               165 	.ascii "[2J"
      000333 00                     166 	.db 0x00
                                    167 	.area CSEG    (CODE)
                                    168 	.area CONST   (CODE)
      000334                        169 ___str_1:
      000334 5B 48                  170 	.ascii "[H"
      000336 00                     171 	.db 0x00
                                    172 	.area CSEG    (CODE)
                                    173 	.area XINIT   (CODE)
                                    174 	.area CABS    (ABS,CODE)
