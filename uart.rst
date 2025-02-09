                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module uart
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _strlen
                                     12 	.globl _CY
                                     13 	.globl _AC
                                     14 	.globl _F0
                                     15 	.globl _RS1
                                     16 	.globl _RS0
                                     17 	.globl _OV
                                     18 	.globl _F1
                                     19 	.globl _P
                                     20 	.globl _PS
                                     21 	.globl _PT1
                                     22 	.globl _PX1
                                     23 	.globl _PT0
                                     24 	.globl _PX0
                                     25 	.globl _RD
                                     26 	.globl _WR
                                     27 	.globl _T1
                                     28 	.globl _T0
                                     29 	.globl _INT1
                                     30 	.globl _INT0
                                     31 	.globl _TXD
                                     32 	.globl _RXD
                                     33 	.globl _P3_7
                                     34 	.globl _P3_6
                                     35 	.globl _P3_5
                                     36 	.globl _P3_4
                                     37 	.globl _P3_3
                                     38 	.globl _P3_2
                                     39 	.globl _P3_1
                                     40 	.globl _P3_0
                                     41 	.globl _EA
                                     42 	.globl _ES
                                     43 	.globl _ET1
                                     44 	.globl _EX1
                                     45 	.globl _ET0
                                     46 	.globl _EX0
                                     47 	.globl _P2_7
                                     48 	.globl _P2_6
                                     49 	.globl _P2_5
                                     50 	.globl _P2_4
                                     51 	.globl _P2_3
                                     52 	.globl _P2_2
                                     53 	.globl _P2_1
                                     54 	.globl _P2_0
                                     55 	.globl _SM0
                                     56 	.globl _SM1
                                     57 	.globl _SM2
                                     58 	.globl _REN
                                     59 	.globl _TB8
                                     60 	.globl _RB8
                                     61 	.globl _TI
                                     62 	.globl _RI
                                     63 	.globl _P1_7
                                     64 	.globl _P1_6
                                     65 	.globl _P1_5
                                     66 	.globl _P1_4
                                     67 	.globl _P1_3
                                     68 	.globl _P1_2
                                     69 	.globl _P1_1
                                     70 	.globl _P1_0
                                     71 	.globl _TF1
                                     72 	.globl _TR1
                                     73 	.globl _TF0
                                     74 	.globl _TR0
                                     75 	.globl _IE1
                                     76 	.globl _IT1
                                     77 	.globl _IE0
                                     78 	.globl _IT0
                                     79 	.globl _P0_7
                                     80 	.globl _P0_6
                                     81 	.globl _P0_5
                                     82 	.globl _P0_4
                                     83 	.globl _P0_3
                                     84 	.globl _P0_2
                                     85 	.globl _P0_1
                                     86 	.globl _P0_0
                                     87 	.globl _B
                                     88 	.globl _ACC
                                     89 	.globl _PSW
                                     90 	.globl _IP
                                     91 	.globl _P3
                                     92 	.globl _IE
                                     93 	.globl _P2
                                     94 	.globl _SBUF
                                     95 	.globl _SCON
                                     96 	.globl _P1
                                     97 	.globl _TH1
                                     98 	.globl _TH0
                                     99 	.globl _TL1
                                    100 	.globl _TL0
                                    101 	.globl _TMOD
                                    102 	.globl _TCON
                                    103 	.globl _PCON
                                    104 	.globl _DPH
                                    105 	.globl _DPL
                                    106 	.globl _SP
                                    107 	.globl _P0
                                    108 	.globl _uart_init
                                    109 	.globl _uart_print
                                    110 	.globl _uart_print_esc
                                    111 	.globl _uart_print_char
                                    112 	.globl _uart_print_hex
                                    113 	.globl _uart_isr
                                    114 ;--------------------------------------------------------
                                    115 ; special function registers
                                    116 ;--------------------------------------------------------
                                    117 	.area RSEG    (ABS,DATA)
      000000                        118 	.org 0x0000
                           000080   119 _P0	=	0x0080
                           000081   120 _SP	=	0x0081
                           000082   121 _DPL	=	0x0082
                           000083   122 _DPH	=	0x0083
                           000087   123 _PCON	=	0x0087
                           000088   124 _TCON	=	0x0088
                           000089   125 _TMOD	=	0x0089
                           00008A   126 _TL0	=	0x008a
                           00008B   127 _TL1	=	0x008b
                           00008C   128 _TH0	=	0x008c
                           00008D   129 _TH1	=	0x008d
                           000090   130 _P1	=	0x0090
                           000098   131 _SCON	=	0x0098
                           000099   132 _SBUF	=	0x0099
                           0000A0   133 _P2	=	0x00a0
                           0000A8   134 _IE	=	0x00a8
                           0000B0   135 _P3	=	0x00b0
                           0000B8   136 _IP	=	0x00b8
                           0000D0   137 _PSW	=	0x00d0
                           0000E0   138 _ACC	=	0x00e0
                           0000F0   139 _B	=	0x00f0
                                    140 ;--------------------------------------------------------
                                    141 ; special function bits
                                    142 ;--------------------------------------------------------
                                    143 	.area RSEG    (ABS,DATA)
      000000                        144 	.org 0x0000
                           000080   145 _P0_0	=	0x0080
                           000081   146 _P0_1	=	0x0081
                           000082   147 _P0_2	=	0x0082
                           000083   148 _P0_3	=	0x0083
                           000084   149 _P0_4	=	0x0084
                           000085   150 _P0_5	=	0x0085
                           000086   151 _P0_6	=	0x0086
                           000087   152 _P0_7	=	0x0087
                           000088   153 _IT0	=	0x0088
                           000089   154 _IE0	=	0x0089
                           00008A   155 _IT1	=	0x008a
                           00008B   156 _IE1	=	0x008b
                           00008C   157 _TR0	=	0x008c
                           00008D   158 _TF0	=	0x008d
                           00008E   159 _TR1	=	0x008e
                           00008F   160 _TF1	=	0x008f
                           000090   161 _P1_0	=	0x0090
                           000091   162 _P1_1	=	0x0091
                           000092   163 _P1_2	=	0x0092
                           000093   164 _P1_3	=	0x0093
                           000094   165 _P1_4	=	0x0094
                           000095   166 _P1_5	=	0x0095
                           000096   167 _P1_6	=	0x0096
                           000097   168 _P1_7	=	0x0097
                           000098   169 _RI	=	0x0098
                           000099   170 _TI	=	0x0099
                           00009A   171 _RB8	=	0x009a
                           00009B   172 _TB8	=	0x009b
                           00009C   173 _REN	=	0x009c
                           00009D   174 _SM2	=	0x009d
                           00009E   175 _SM1	=	0x009e
                           00009F   176 _SM0	=	0x009f
                           0000A0   177 _P2_0	=	0x00a0
                           0000A1   178 _P2_1	=	0x00a1
                           0000A2   179 _P2_2	=	0x00a2
                           0000A3   180 _P2_3	=	0x00a3
                           0000A4   181 _P2_4	=	0x00a4
                           0000A5   182 _P2_5	=	0x00a5
                           0000A6   183 _P2_6	=	0x00a6
                           0000A7   184 _P2_7	=	0x00a7
                           0000A8   185 _EX0	=	0x00a8
                           0000A9   186 _ET0	=	0x00a9
                           0000AA   187 _EX1	=	0x00aa
                           0000AB   188 _ET1	=	0x00ab
                           0000AC   189 _ES	=	0x00ac
                           0000AF   190 _EA	=	0x00af
                           0000B0   191 _P3_0	=	0x00b0
                           0000B1   192 _P3_1	=	0x00b1
                           0000B2   193 _P3_2	=	0x00b2
                           0000B3   194 _P3_3	=	0x00b3
                           0000B4   195 _P3_4	=	0x00b4
                           0000B5   196 _P3_5	=	0x00b5
                           0000B6   197 _P3_6	=	0x00b6
                           0000B7   198 _P3_7	=	0x00b7
                           0000B0   199 _RXD	=	0x00b0
                           0000B1   200 _TXD	=	0x00b1
                           0000B2   201 _INT0	=	0x00b2
                           0000B3   202 _INT1	=	0x00b3
                           0000B4   203 _T0	=	0x00b4
                           0000B5   204 _T1	=	0x00b5
                           0000B6   205 _WR	=	0x00b6
                           0000B7   206 _RD	=	0x00b7
                           0000B8   207 _PX0	=	0x00b8
                           0000B9   208 _PT0	=	0x00b9
                           0000BA   209 _PX1	=	0x00ba
                           0000BB   210 _PT1	=	0x00bb
                           0000BC   211 _PS	=	0x00bc
                           0000D0   212 _P	=	0x00d0
                           0000D1   213 _F1	=	0x00d1
                           0000D2   214 _OV	=	0x00d2
                           0000D3   215 _RS0	=	0x00d3
                           0000D4   216 _RS1	=	0x00d4
                           0000D5   217 _F0	=	0x00d5
                           0000D6   218 _AC	=	0x00d6
                           0000D7   219 _CY	=	0x00d7
                                    220 ;--------------------------------------------------------
                                    221 ; overlayable register banks
                                    222 ;--------------------------------------------------------
                                    223 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        224 	.ds 8
                                    225 ;--------------------------------------------------------
                                    226 ; overlayable bit register bank
                                    227 ;--------------------------------------------------------
                                    228 	.area BIT_BANK	(REL,OVR,DATA)
      000020                        229 bits:
      000020                        230 	.ds 1
                           008000   231 	b0 = bits[0]
                           008100   232 	b1 = bits[1]
                           008200   233 	b2 = bits[2]
                           008300   234 	b3 = bits[3]
                           008400   235 	b4 = bits[4]
                           008500   236 	b5 = bits[5]
                           008600   237 	b6 = bits[6]
                           008700   238 	b7 = bits[7]
                                    239 ;--------------------------------------------------------
                                    240 ; internal ram data
                                    241 ;--------------------------------------------------------
                                    242 	.area DSEG    (DATA)
      000008                        243 _uart_print_str_65536_31:
      000008                        244 	.ds 3
      00000B                        245 _uart_print_hex_hex_chars_65536_41:
      00000B                        246 	.ds 17
                                    247 ;--------------------------------------------------------
                                    248 ; overlayable items in internal ram 
                                    249 ;--------------------------------------------------------
                                    250 	.area	OSEG    (OVR,DATA)
                                    251 ;--------------------------------------------------------
                                    252 ; indirectly addressable internal ram data
                                    253 ;--------------------------------------------------------
                                    254 	.area ISEG    (DATA)
                                    255 ;--------------------------------------------------------
                                    256 ; absolute internal ram data
                                    257 ;--------------------------------------------------------
                                    258 	.area IABS    (ABS,DATA)
                                    259 	.area IABS    (ABS,DATA)
                                    260 ;--------------------------------------------------------
                                    261 ; bit data
                                    262 ;--------------------------------------------------------
                                    263 	.area BSEG    (BIT)
                                    264 ;--------------------------------------------------------
                                    265 ; paged external ram data
                                    266 ;--------------------------------------------------------
                                    267 	.area PSEG    (PAG,XDATA)
                                    268 ;--------------------------------------------------------
                                    269 ; external ram data
                                    270 ;--------------------------------------------------------
                                    271 	.area XSEG    (XDATA)
                                    272 ;--------------------------------------------------------
                                    273 ; absolute external ram data
                                    274 ;--------------------------------------------------------
                                    275 	.area XABS    (ABS,XDATA)
                                    276 ;--------------------------------------------------------
                                    277 ; external initialized ram data
                                    278 ;--------------------------------------------------------
                                    279 	.area XISEG   (XDATA)
                                    280 	.area HOME    (CODE)
                                    281 	.area GSINIT0 (CODE)
                                    282 	.area GSINIT1 (CODE)
                                    283 	.area GSINIT2 (CODE)
                                    284 	.area GSINIT3 (CODE)
                                    285 	.area GSINIT4 (CODE)
                                    286 	.area GSINIT5 (CODE)
                                    287 	.area GSINIT  (CODE)
                                    288 	.area GSFINAL (CODE)
                                    289 	.area CSEG    (CODE)
                                    290 ;--------------------------------------------------------
                                    291 ; global & static initialisations
                                    292 ;--------------------------------------------------------
                                    293 	.area HOME    (CODE)
                                    294 	.area GSINIT  (CODE)
                                    295 	.area GSFINAL (CODE)
                                    296 	.area GSINIT  (CODE)
                                    297 ;------------------------------------------------------------
                                    298 ;Allocation info for local variables in function 'uart_print_hex'
                                    299 ;------------------------------------------------------------
                                    300 ;hex_chars                 Allocated with name '_uart_print_hex_hex_chars_65536_41'
                                    301 ;val                       Allocated to registers r7 
                                    302 ;------------------------------------------------------------
                                    303 ;	uart.c:65: static char hex_chars[] = "0123456789ABCDEF";
      000082 75 0B 30         [24]  304 	mov	_uart_print_hex_hex_chars_65536_41,#0x30
      000085 75 0C 31         [24]  305 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0001),#0x31
      000088 75 0D 32         [24]  306 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0002),#0x32
      00008B 75 0E 33         [24]  307 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0003),#0x33
      00008E 75 0F 34         [24]  308 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0004),#0x34
      000091 75 10 35         [24]  309 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0005),#0x35
      000094 75 11 36         [24]  310 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0006),#0x36
      000097 75 12 37         [24]  311 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0007),#0x37
      00009A 75 13 38         [24]  312 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0008),#0x38
      00009D 75 14 39         [24]  313 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0009),#0x39
      0000A0 75 15 41         [24]  314 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000a),#0x41
      0000A3 75 16 42         [24]  315 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000b),#0x42
      0000A6 75 17 43         [24]  316 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000c),#0x43
      0000A9 75 18 44         [24]  317 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000d),#0x44
      0000AC 75 19 45         [24]  318 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000e),#0x45
      0000AF 75 1A 46         [24]  319 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000f),#0x46
      0000B2 75 1B 00         [24]  320 	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0010),#0x00
                                    321 ;--------------------------------------------------------
                                    322 ; Home
                                    323 ;--------------------------------------------------------
                                    324 	.area HOME    (CODE)
                                    325 	.area HOME    (CODE)
                                    326 ;--------------------------------------------------------
                                    327 ; code
                                    328 ;--------------------------------------------------------
                                    329 	.area CSEG    (CODE)
                                    330 ;------------------------------------------------------------
                                    331 ;Allocation info for local variables in function 'uart_init'
                                    332 ;------------------------------------------------------------
                                    333 ;	uart.c:6: void uart_init()
                                    334 ;	-----------------------------------------
                                    335 ;	 function uart_init
                                    336 ;	-----------------------------------------
      0000F3                        337 _uart_init:
                           000007   338 	ar7 = 0x07
                           000006   339 	ar6 = 0x06
                           000005   340 	ar5 = 0x05
                           000004   341 	ar4 = 0x04
                           000003   342 	ar3 = 0x03
                           000002   343 	ar2 = 0x02
                           000001   344 	ar1 = 0x01
                           000000   345 	ar0 = 0x00
                                    346 ;	uart.c:9: TMOD |= 0x20;   /* timer 1 in mode 2 (8-bit overflow) */
      0000F3 43 89 20         [24]  347 	orl	_TMOD,#0x20
                                    348 ;	uart.c:10: TH1   = 0xF5;   /* timer reload value for baud = 9600 */
      0000F6 75 8D F5         [24]  349 	mov	_TH1,#0xf5
                                    350 ;	uart.c:11: PCON |= 0x80;   /* set SMOD1 */
      0000F9 43 87 80         [24]  351 	orl	_PCON,#0x80
                                    352 ;	uart.c:12: TCON |= 0x40;   /* enable timer */
      0000FC 43 88 40         [24]  353 	orl	_TCON,#0x40
                                    354 ;	uart.c:15: SCON  = 0x50;   /* mode 1 (8 bit tx/rx) + enable receive */
      0000FF 75 98 50         [24]  355 	mov	_SCON,#0x50
                                    356 ;	uart.c:18: EA = 1;
                                    357 ;	assignBit
      000102 D2 AF            [12]  358 	setb	_EA
                                    359 ;	uart.c:19: ES = 1;
                                    360 ;	assignBit
      000104 D2 AC            [12]  361 	setb	_ES
                                    362 ;	uart.c:20: }
      000106 22               [24]  363 	ret
                                    364 ;------------------------------------------------------------
                                    365 ;Allocation info for local variables in function 'uart_print'
                                    366 ;------------------------------------------------------------
                                    367 ;string                    Allocated to registers r5 r6 r7 
                                    368 ;str                       Allocated with name '_uart_print_str_65536_31'
                                    369 ;i                         Allocated to registers r6 r7 
                                    370 ;------------------------------------------------------------
                                    371 ;	uart.c:24: void uart_print(char *string)
                                    372 ;	-----------------------------------------
                                    373 ;	 function uart_print
                                    374 ;	-----------------------------------------
      000107                        375 _uart_print:
      000107 AD 82            [24]  376 	mov	r5,dpl
      000109 AE 83            [24]  377 	mov	r6,dph
      00010B AF F0            [24]  378 	mov	r7,b
                                    379 ;	uart.c:27: const char *str = string;
      00010D 8D 08            [24]  380 	mov	_uart_print_str_65536_31,r5
      00010F 8E 09            [24]  381 	mov	(_uart_print_str_65536_31 + 1),r6
      000111 8F 0A            [24]  382 	mov	(_uart_print_str_65536_31 + 2),r7
                                    383 ;	uart.c:28: if (string == NULL)
      000113 ED               [12]  384 	mov	a,r5
      000114 4E               [12]  385 	orl	a,r6
      000115 70 09            [24]  386 	jnz	00111$
                                    387 ;	uart.c:30: str = "Error print string is null";
      000117 75 08 37         [24]  388 	mov	_uart_print_str_65536_31,#___str_0
      00011A 75 09 03         [24]  389 	mov	(_uart_print_str_65536_31 + 1),#(___str_0 >> 8)
      00011D 75 0A 80         [24]  390 	mov	(_uart_print_str_65536_31 + 2),#0x80
                                    391 ;	uart.c:33: for (int i = 0; i < strlen(str); i++)
      000120                        392 00111$:
      000120 7E 00            [12]  393 	mov	r6,#0x00
      000122 7F 00            [12]  394 	mov	r7,#0x00
      000124                        395 00105$:
      000124 85 08 82         [24]  396 	mov	dpl,_uart_print_str_65536_31
      000127 85 09 83         [24]  397 	mov	dph,(_uart_print_str_65536_31 + 1)
      00012A 85 0A F0         [24]  398 	mov	b,(_uart_print_str_65536_31 + 2)
      00012D C0 07            [24]  399 	push	ar7
      00012F C0 06            [24]  400 	push	ar6
      000131 12 02 F8         [24]  401 	lcall	_strlen
      000134 A9 82            [24]  402 	mov	r1,dpl
      000136 AD 83            [24]  403 	mov	r5,dph
      000138 D0 06            [24]  404 	pop	ar6
      00013A D0 07            [24]  405 	pop	ar7
      00013C 8E 00            [24]  406 	mov	ar0,r6
      00013E 8F 04            [24]  407 	mov	ar4,r7
      000140 C3               [12]  408 	clr	c
      000141 E8               [12]  409 	mov	a,r0
      000142 99               [12]  410 	subb	a,r1
      000143 EC               [12]  411 	mov	a,r4
      000144 9D               [12]  412 	subb	a,r5
      000145 50 27            [24]  413 	jnc	00107$
                                    414 ;	uart.c:35: uart_print_char(str[i]);
      000147 EE               [12]  415 	mov	a,r6
      000148 25 08            [12]  416 	add	a,_uart_print_str_65536_31
      00014A FB               [12]  417 	mov	r3,a
      00014B EF               [12]  418 	mov	a,r7
      00014C 35 09            [12]  419 	addc	a,(_uart_print_str_65536_31 + 1)
      00014E FC               [12]  420 	mov	r4,a
      00014F AD 0A            [24]  421 	mov	r5,(_uart_print_str_65536_31 + 2)
      000151 8B 82            [24]  422 	mov	dpl,r3
      000153 8C 83            [24]  423 	mov	dph,r4
      000155 8D F0            [24]  424 	mov	b,r5
      000157 12 03 10         [24]  425 	lcall	__gptrget
      00015A F5 82            [12]  426 	mov	dpl,a
      00015C C0 07            [24]  427 	push	ar7
      00015E C0 06            [24]  428 	push	ar6
      000160 12 01 9D         [24]  429 	lcall	_uart_print_char
      000163 D0 06            [24]  430 	pop	ar6
      000165 D0 07            [24]  431 	pop	ar7
                                    432 ;	uart.c:33: for (int i = 0; i < strlen(str); i++)
      000167 0E               [12]  433 	inc	r6
      000168 BE 00 B9         [24]  434 	cjne	r6,#0x00,00105$
      00016B 0F               [12]  435 	inc	r7
      00016C 80 B6            [24]  436 	sjmp	00105$
      00016E                        437 00107$:
                                    438 ;	uart.c:37: }
      00016E 22               [24]  439 	ret
                                    440 ;------------------------------------------------------------
                                    441 ;Allocation info for local variables in function 'uart_print_esc'
                                    442 ;------------------------------------------------------------
                                    443 ;code                      Allocated to registers r5 r6 r7 
                                    444 ;------------------------------------------------------------
                                    445 ;	uart.c:41: void uart_print_esc(char *code)
                                    446 ;	-----------------------------------------
                                    447 ;	 function uart_print_esc
                                    448 ;	-----------------------------------------
      00016F                        449 _uart_print_esc:
      00016F AD 82            [24]  450 	mov	r5,dpl
      000171 AE 83            [24]  451 	mov	r6,dph
      000173 AF F0            [24]  452 	mov	r7,b
                                    453 ;	uart.c:43: if (code == NULL)
      000175 ED               [12]  454 	mov	a,r5
      000176 4E               [12]  455 	orl	a,r6
      000177 70 09            [24]  456 	jnz	00102$
                                    457 ;	uart.c:45: uart_print("Error escape code is null");
      000179 90 03 52         [24]  458 	mov	dptr,#___str_1
      00017C 75 F0 80         [24]  459 	mov	b,#0x80
                                    460 ;	uart.c:46: return;
      00017F 02 01 07         [24]  461 	ljmp	_uart_print
      000182                        462 00102$:
                                    463 ;	uart.c:48: uart_print_char(ESC_CHAR);
      000182 75 82 1B         [24]  464 	mov	dpl,#0x1b
      000185 C0 07            [24]  465 	push	ar7
      000187 C0 06            [24]  466 	push	ar6
      000189 C0 05            [24]  467 	push	ar5
      00018B 12 01 9D         [24]  468 	lcall	_uart_print_char
      00018E D0 05            [24]  469 	pop	ar5
      000190 D0 06            [24]  470 	pop	ar6
      000192 D0 07            [24]  471 	pop	ar7
                                    472 ;	uart.c:49: uart_print(code);
      000194 8D 82            [24]  473 	mov	dpl,r5
      000196 8E 83            [24]  474 	mov	dph,r6
      000198 8F F0            [24]  475 	mov	b,r7
                                    476 ;	uart.c:50: }
      00019A 02 01 07         [24]  477 	ljmp	_uart_print
                                    478 ;------------------------------------------------------------
                                    479 ;Allocation info for local variables in function 'uart_print_char'
                                    480 ;------------------------------------------------------------
                                    481 ;ch                        Allocated to registers 
                                    482 ;------------------------------------------------------------
                                    483 ;	uart.c:54: void uart_print_char(char ch)
                                    484 ;	-----------------------------------------
                                    485 ;	 function uart_print_char
                                    486 ;	-----------------------------------------
      00019D                        487 _uart_print_char:
      00019D 85 82 99         [24]  488 	mov	_SBUF,dpl
                                    489 ;	uart.c:57: while (TI == 0);
      0001A0                        490 00101$:
                                    491 ;	uart.c:58: TI = 0;
                                    492 ;	assignBit
      0001A0 10 99 02         [24]  493 	jbc	_TI,00114$
      0001A3 80 FB            [24]  494 	sjmp	00101$
      0001A5                        495 00114$:
                                    496 ;	uart.c:59: }
      0001A5 22               [24]  497 	ret
                                    498 ;------------------------------------------------------------
                                    499 ;Allocation info for local variables in function 'uart_print_hex'
                                    500 ;------------------------------------------------------------
                                    501 ;hex_chars                 Allocated with name '_uart_print_hex_hex_chars_65536_41'
                                    502 ;val                       Allocated to registers r7 
                                    503 ;------------------------------------------------------------
                                    504 ;	uart.c:63: void uart_print_hex(char val)
                                    505 ;	-----------------------------------------
                                    506 ;	 function uart_print_hex
                                    507 ;	-----------------------------------------
      0001A6                        508 _uart_print_hex:
                                    509 ;	uart.c:66: uart_print_char(hex_chars[val >> 4]);
      0001A6 E5 82            [12]  510 	mov	a,dpl
      0001A8 FF               [12]  511 	mov	r7,a
      0001A9 C4               [12]  512 	swap	a
      0001AA 54 0F            [12]  513 	anl	a,#0x0f
      0001AC 24 0B            [12]  514 	add	a,#_uart_print_hex_hex_chars_65536_41
      0001AE F9               [12]  515 	mov	r1,a
      0001AF 87 82            [24]  516 	mov	dpl,@r1
      0001B1 C0 07            [24]  517 	push	ar7
      0001B3 12 01 9D         [24]  518 	lcall	_uart_print_char
      0001B6 D0 07            [24]  519 	pop	ar7
                                    520 ;	uart.c:67: uart_print_char(hex_chars[val & 0x0F]);
      0001B8 53 07 0F         [24]  521 	anl	ar7,#0x0f
      0001BB EF               [12]  522 	mov	a,r7
      0001BC 24 0B            [12]  523 	add	a,#_uart_print_hex_hex_chars_65536_41
      0001BE F9               [12]  524 	mov	r1,a
      0001BF 87 82            [24]  525 	mov	dpl,@r1
                                    526 ;	uart.c:68: }
      0001C1 02 01 9D         [24]  527 	ljmp	_uart_print_char
                                    528 ;------------------------------------------------------------
                                    529 ;Allocation info for local variables in function 'uart_isr'
                                    530 ;------------------------------------------------------------
                                    531 ;	uart.c:72: void uart_isr() __interrupt (4)
                                    532 ;	-----------------------------------------
                                    533 ;	 function uart_isr
                                    534 ;	-----------------------------------------
      0001C4                        535 _uart_isr:
      0001C4 C0 20            [24]  536 	push	bits
      0001C6 C0 E0            [24]  537 	push	acc
      0001C8 C0 F0            [24]  538 	push	b
      0001CA C0 82            [24]  539 	push	dpl
      0001CC C0 83            [24]  540 	push	dph
      0001CE C0 07            [24]  541 	push	(0+7)
      0001D0 C0 06            [24]  542 	push	(0+6)
      0001D2 C0 05            [24]  543 	push	(0+5)
      0001D4 C0 04            [24]  544 	push	(0+4)
      0001D6 C0 03            [24]  545 	push	(0+3)
      0001D8 C0 02            [24]  546 	push	(0+2)
      0001DA C0 01            [24]  547 	push	(0+1)
      0001DC C0 00            [24]  548 	push	(0+0)
      0001DE C0 D0            [24]  549 	push	psw
      0001E0 75 D0 00         [24]  550 	mov	psw,#0x00
                                    551 ;	uart.c:74: if (RI)
                                    552 ;	uart.c:76: RI = 0;
                                    553 ;	assignBit
      0001E3 10 98 02         [24]  554 	jbc	_RI,00109$
      0001E6 80 06            [24]  555 	sjmp	00103$
      0001E8                        556 00109$:
                                    557 ;	uart.c:77: uart_print_char(SBUF);
      0001E8 85 99 82         [24]  558 	mov	dpl,_SBUF
      0001EB 12 01 9D         [24]  559 	lcall	_uart_print_char
      0001EE                        560 00103$:
                                    561 ;	uart.c:79: }
      0001EE D0 D0            [24]  562 	pop	psw
      0001F0 D0 00            [24]  563 	pop	(0+0)
      0001F2 D0 01            [24]  564 	pop	(0+1)
      0001F4 D0 02            [24]  565 	pop	(0+2)
      0001F6 D0 03            [24]  566 	pop	(0+3)
      0001F8 D0 04            [24]  567 	pop	(0+4)
      0001FA D0 05            [24]  568 	pop	(0+5)
      0001FC D0 06            [24]  569 	pop	(0+6)
      0001FE D0 07            [24]  570 	pop	(0+7)
      000200 D0 83            [24]  571 	pop	dph
      000202 D0 82            [24]  572 	pop	dpl
      000204 D0 F0            [24]  573 	pop	b
      000206 D0 E0            [24]  574 	pop	acc
      000208 D0 20            [24]  575 	pop	bits
      00020A 32               [24]  576 	reti
                                    577 	.area CSEG    (CODE)
                                    578 	.area CONST   (CODE)
                                    579 	.area CONST   (CODE)
      000337                        580 ___str_0:
      000337 45 72 72 6F 72 20 70   581 	.ascii "Error print string is null"
             72 69 6E 74 20 73 74
             72 69 6E 67 20 69 73
             20 6E 75 6C 6C
      000351 00                     582 	.db 0x00
                                    583 	.area CSEG    (CODE)
                                    584 	.area CONST   (CODE)
      000352                        585 ___str_1:
      000352 45 72 72 6F 72 20 65   586 	.ascii "Error escape code is null"
             73 63 61 70 65 20 63
             6F 64 65 20 69 73 20
             6E 75 6C 6C
      00036B 00                     587 	.db 0x00
                                    588 	.area CSEG    (CODE)
                                    589 	.area XINIT   (CODE)
                                    590 	.area CABS    (ABS,CODE)
