                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module flash
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _CY
                                     12 	.globl _AC
                                     13 	.globl _F0
                                     14 	.globl _RS1
                                     15 	.globl _RS0
                                     16 	.globl _OV
                                     17 	.globl _F1
                                     18 	.globl _P
                                     19 	.globl _PS
                                     20 	.globl _PT1
                                     21 	.globl _PX1
                                     22 	.globl _PT0
                                     23 	.globl _PX0
                                     24 	.globl _RD
                                     25 	.globl _WR
                                     26 	.globl _T1
                                     27 	.globl _T0
                                     28 	.globl _INT1
                                     29 	.globl _INT0
                                     30 	.globl _TXD
                                     31 	.globl _RXD
                                     32 	.globl _P3_7
                                     33 	.globl _P3_6
                                     34 	.globl _P3_5
                                     35 	.globl _P3_4
                                     36 	.globl _P3_3
                                     37 	.globl _P3_2
                                     38 	.globl _P3_1
                                     39 	.globl _P3_0
                                     40 	.globl _EA
                                     41 	.globl _ES
                                     42 	.globl _ET1
                                     43 	.globl _EX1
                                     44 	.globl _ET0
                                     45 	.globl _EX0
                                     46 	.globl _P2_7
                                     47 	.globl _P2_6
                                     48 	.globl _P2_5
                                     49 	.globl _P2_4
                                     50 	.globl _P2_3
                                     51 	.globl _P2_2
                                     52 	.globl _P2_1
                                     53 	.globl _P2_0
                                     54 	.globl _SM0
                                     55 	.globl _SM1
                                     56 	.globl _SM2
                                     57 	.globl _REN
                                     58 	.globl _TB8
                                     59 	.globl _RB8
                                     60 	.globl _TI
                                     61 	.globl _RI
                                     62 	.globl _P1_7
                                     63 	.globl _P1_6
                                     64 	.globl _P1_5
                                     65 	.globl _P1_4
                                     66 	.globl _P1_3
                                     67 	.globl _P1_2
                                     68 	.globl _P1_1
                                     69 	.globl _P1_0
                                     70 	.globl _TF1
                                     71 	.globl _TR1
                                     72 	.globl _TF0
                                     73 	.globl _TR0
                                     74 	.globl _IE1
                                     75 	.globl _IT1
                                     76 	.globl _IE0
                                     77 	.globl _IT0
                                     78 	.globl _P0_7
                                     79 	.globl _P0_6
                                     80 	.globl _P0_5
                                     81 	.globl _P0_4
                                     82 	.globl _P0_3
                                     83 	.globl _P0_2
                                     84 	.globl _P0_1
                                     85 	.globl _P0_0
                                     86 	.globl _B
                                     87 	.globl _ACC
                                     88 	.globl _PSW
                                     89 	.globl _IP
                                     90 	.globl _P3
                                     91 	.globl _IE
                                     92 	.globl _P2
                                     93 	.globl _SBUF
                                     94 	.globl _SCON
                                     95 	.globl _P1
                                     96 	.globl _TH1
                                     97 	.globl _TH0
                                     98 	.globl _TL1
                                     99 	.globl _TL0
                                    100 	.globl _TMOD
                                    101 	.globl _TCON
                                    102 	.globl _PCON
                                    103 	.globl _DPH
                                    104 	.globl _DPL
                                    105 	.globl _SP
                                    106 	.globl _P0
                                    107 	.globl _flash_program_PARM_2
                                    108 	.globl _flash_init
                                    109 	.globl _flash_set_address
                                    110 	.globl _flash_program
                                    111 	.globl _flash_read
                                    112 	.globl _flash_erase
                                    113 	.globl _flash_delay
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
                                    226 ; internal ram data
                                    227 ;--------------------------------------------------------
                                    228 	.area DSEG    (DATA)
      000021                        229 _flash_program_sdp_addr1_65537_12:
      000021                        230 	.ds 3
      000024                        231 _flash_program_sdp_addr2_65537_12:
      000024                        232 	.ds 3
      000027                        233 _flash_program_sdp_addr3_65537_12:
      000027                        234 	.ds 3
      00002A                        235 _flash_program_PARM_2:
      00002A                        236 	.ds 3
                                    237 ;--------------------------------------------------------
                                    238 ; overlayable items in internal ram 
                                    239 ;--------------------------------------------------------
                                    240 	.area	OSEG    (OVR,DATA)
                                    241 	.area	OSEG    (OVR,DATA)
                                    242 ;--------------------------------------------------------
                                    243 ; indirectly addressable internal ram data
                                    244 ;--------------------------------------------------------
                                    245 	.area ISEG    (DATA)
                                    246 ;--------------------------------------------------------
                                    247 ; absolute internal ram data
                                    248 ;--------------------------------------------------------
                                    249 	.area IABS    (ABS,DATA)
                                    250 	.area IABS    (ABS,DATA)
                                    251 ;--------------------------------------------------------
                                    252 ; bit data
                                    253 ;--------------------------------------------------------
                                    254 	.area BSEG    (BIT)
                                    255 ;--------------------------------------------------------
                                    256 ; paged external ram data
                                    257 ;--------------------------------------------------------
                                    258 	.area PSEG    (PAG,XDATA)
                                    259 ;--------------------------------------------------------
                                    260 ; external ram data
                                    261 ;--------------------------------------------------------
                                    262 	.area XSEG    (XDATA)
                                    263 ;--------------------------------------------------------
                                    264 ; absolute external ram data
                                    265 ;--------------------------------------------------------
                                    266 	.area XABS    (ABS,XDATA)
                                    267 ;--------------------------------------------------------
                                    268 ; external initialized ram data
                                    269 ;--------------------------------------------------------
                                    270 	.area XISEG   (XDATA)
                                    271 	.area HOME    (CODE)
                                    272 	.area GSINIT0 (CODE)
                                    273 	.area GSINIT1 (CODE)
                                    274 	.area GSINIT2 (CODE)
                                    275 	.area GSINIT3 (CODE)
                                    276 	.area GSINIT4 (CODE)
                                    277 	.area GSINIT5 (CODE)
                                    278 	.area GSINIT  (CODE)
                                    279 	.area GSFINAL (CODE)
                                    280 	.area CSEG    (CODE)
                                    281 ;--------------------------------------------------------
                                    282 ; global & static initialisations
                                    283 ;--------------------------------------------------------
                                    284 	.area HOME    (CODE)
                                    285 	.area GSINIT  (CODE)
                                    286 	.area GSFINAL (CODE)
                                    287 	.area GSINIT  (CODE)
                                    288 ;------------------------------------------------------------
                                    289 ;Allocation info for local variables in function 'flash_program'
                                    290 ;------------------------------------------------------------
                                    291 ;sdp_addr1                 Allocated with name '_flash_program_sdp_addr1_65537_12'
                                    292 ;sdp_addr2                 Allocated with name '_flash_program_sdp_addr2_65537_12'
                                    293 ;sdp_addr3                 Allocated with name '_flash_program_sdp_addr3_65537_12'
                                    294 ;address                   Allocated with name '_flash_program_PARM_2'
                                    295 ;data                      Allocated to registers r7 
                                    296 ;------------------------------------------------------------
                                    297 ;	flash.c:35: static address_t sdp_addr1 = { 0x00, 0x55, 0x55 };
      0000B5 75 21 00         [24]  298 	mov	_flash_program_sdp_addr1_65537_12,#0x00
      0000B8 75 22 55         [24]  299 	mov	(_flash_program_sdp_addr1_65537_12 + 0x0001),#0x55
      0000BB 75 23 55         [24]  300 	mov	(_flash_program_sdp_addr1_65537_12 + 0x0002),#0x55
                                    301 ;	flash.c:36: static address_t sdp_addr2 = { 0x00, 0x2A, 0xAA };
      0000BE 75 24 00         [24]  302 	mov	_flash_program_sdp_addr2_65537_12,#0x00
      0000C1 75 25 2A         [24]  303 	mov	(_flash_program_sdp_addr2_65537_12 + 0x0001),#0x2a
      0000C4 75 26 AA         [24]  304 	mov	(_flash_program_sdp_addr2_65537_12 + 0x0002),#0xaa
                                    305 ;	flash.c:37: static address_t sdp_addr3 = { 0x00, 0x55, 0x55 };
      0000C7 75 27 00         [24]  306 	mov	_flash_program_sdp_addr3_65537_12,#0x00
      0000CA 75 28 55         [24]  307 	mov	(_flash_program_sdp_addr3_65537_12 + 0x0001),#0x55
      0000CD 75 29 55         [24]  308 	mov	(_flash_program_sdp_addr3_65537_12 + 0x0002),#0x55
                                    309 ;--------------------------------------------------------
                                    310 ; Home
                                    311 ;--------------------------------------------------------
                                    312 	.area HOME    (CODE)
                                    313 	.area HOME    (CODE)
                                    314 ;--------------------------------------------------------
                                    315 ; code
                                    316 ;--------------------------------------------------------
                                    317 	.area CSEG    (CODE)
                                    318 ;------------------------------------------------------------
                                    319 ;Allocation info for local variables in function 'flash_init'
                                    320 ;------------------------------------------------------------
                                    321 ;	flash.c:5: void flash_init()
                                    322 ;	-----------------------------------------
                                    323 ;	 function flash_init
                                    324 ;	-----------------------------------------
      00020B                        325 _flash_init:
                           000007   326 	ar7 = 0x07
                           000006   327 	ar6 = 0x06
                           000005   328 	ar5 = 0x05
                           000004   329 	ar4 = 0x04
                           000003   330 	ar3 = 0x03
                           000002   331 	ar2 = 0x02
                           000001   332 	ar1 = 0x01
                           000000   333 	ar0 = 0x00
                                    334 ;	flash.c:7: CTRL_PORT |= CHIP_ENABLE | OUTPUT_ENABLE | WRITE_ENABLE;
      00020B 43 B0 70         [24]  335 	orl	_P3,#0x70
                                    336 ;	flash.c:8: }
      00020E 22               [24]  337 	ret
                                    338 ;------------------------------------------------------------
                                    339 ;Allocation info for local variables in function 'flash_set_address'
                                    340 ;------------------------------------------------------------
                                    341 ;address                   Allocated to registers r5 r6 r7 
                                    342 ;high_bits                 Allocated to registers r5 
                                    343 ;------------------------------------------------------------
                                    344 ;	flash.c:12: void flash_set_address(address_t *address)
                                    345 ;	-----------------------------------------
                                    346 ;	 function flash_set_address
                                    347 ;	-----------------------------------------
      00020F                        348 _flash_set_address:
      00020F AD 82            [24]  349 	mov	r5,dpl
      000211 AE 83            [24]  350 	mov	r6,dph
      000213 AF F0            [24]  351 	mov	r7,b
                                    352 ;	flash.c:15: P1 = address->low;
      000215 74 02            [12]  353 	mov	a,#0x02
      000217 2D               [12]  354 	add	a,r5
      000218 FA               [12]  355 	mov	r2,a
      000219 E4               [12]  356 	clr	a
      00021A 3E               [12]  357 	addc	a,r6
      00021B FB               [12]  358 	mov	r3,a
      00021C 8F 04            [24]  359 	mov	ar4,r7
      00021E 8A 82            [24]  360 	mov	dpl,r2
      000220 8B 83            [24]  361 	mov	dph,r3
      000222 8C F0            [24]  362 	mov	b,r4
      000224 12 03 10         [24]  363 	lcall	__gptrget
      000227 F5 90            [12]  364 	mov	_P1,a
                                    365 ;	flash.c:16: P2 = address->middle;
      000229 74 01            [12]  366 	mov	a,#0x01
      00022B 2D               [12]  367 	add	a,r5
      00022C FA               [12]  368 	mov	r2,a
      00022D E4               [12]  369 	clr	a
      00022E 3E               [12]  370 	addc	a,r6
      00022F FB               [12]  371 	mov	r3,a
      000230 8F 04            [24]  372 	mov	ar4,r7
      000232 8A 82            [24]  373 	mov	dpl,r2
      000234 8B 83            [24]  374 	mov	dph,r3
      000236 8C F0            [24]  375 	mov	b,r4
      000238 12 03 10         [24]  376 	lcall	__gptrget
      00023B F5 A0            [12]  377 	mov	_P2,a
                                    378 ;	flash.c:19: char high_bits = address->high;
      00023D 8D 82            [24]  379 	mov	dpl,r5
      00023F 8E 83            [24]  380 	mov	dph,r6
      000241 8F F0            [24]  381 	mov	b,r7
      000243 12 03 10         [24]  382 	lcall	__gptrget
      000246 FD               [12]  383 	mov	r5,a
                                    384 ;	flash.c:20: P3 &= ~(7 << 2);
      000247 53 B0 E3         [24]  385 	anl	_P3,#0xe3
                                    386 ;	flash.c:21: high_bits &= 0x03; /* isolate first three bits */
      00024A 53 05 03         [24]  387 	anl	ar5,#0x03
                                    388 ;	flash.c:22: high_bits <<= 2;   /* shift bits over to match port */
      00024D ED               [12]  389 	mov	a,r5
      00024E 2D               [12]  390 	add	a,r5
                                    391 ;	flash.c:23: P3 |= high_bits;
      00024F 25 E0            [12]  392 	add	a,acc
      000251 42 B0            [12]  393 	orl	_P3,a
                                    394 ;	flash.c:24: }
      000253 22               [24]  395 	ret
                                    396 ;------------------------------------------------------------
                                    397 ;Allocation info for local variables in function 'flash_program'
                                    398 ;------------------------------------------------------------
                                    399 ;sdp_addr1                 Allocated with name '_flash_program_sdp_addr1_65537_12'
                                    400 ;sdp_addr2                 Allocated with name '_flash_program_sdp_addr2_65537_12'
                                    401 ;sdp_addr3                 Allocated with name '_flash_program_sdp_addr3_65537_12'
                                    402 ;address                   Allocated with name '_flash_program_PARM_2'
                                    403 ;data                      Allocated to registers r7 
                                    404 ;------------------------------------------------------------
                                    405 ;	flash.c:28: void flash_program(char data, address_t *address)
                                    406 ;	-----------------------------------------
                                    407 ;	 function flash_program
                                    408 ;	-----------------------------------------
      000254                        409 _flash_program:
      000254 AF 82            [24]  410 	mov	r7,dpl
                                    411 ;	flash.c:31: CTRL_PORT &= ~CHIP_ENABLE;
      000256 53 B0 DF         [24]  412 	anl	_P3,#0xdf
                                    413 ;	flash.c:32: flash_delay(TIME_QUICK);
      000259 75 82 FF         [24]  414 	mov	dpl,#0xff
      00025C C0 07            [24]  415 	push	ar7
      00025E 12 02 E1         [24]  416 	lcall	_flash_delay
                                    417 ;	flash.c:39: flash_set_address(&sdp_addr1);
      000261 90 00 21         [24]  418 	mov	dptr,#_flash_program_sdp_addr1_65537_12
      000264 75 F0 40         [24]  419 	mov	b,#0x40
      000267 12 02 0F         [24]  420 	lcall	_flash_set_address
                                    421 ;	flash.c:40: CTRL_PORT &= ~WRITE_ENABLE;    /* latch address */
      00026A 53 B0 EF         [24]  422 	anl	_P3,#0xef
                                    423 ;	flash.c:41: DATA_PORT = 0xAA;
      00026D 75 80 AA         [24]  424 	mov	_P0,#0xaa
                                    425 ;	flash.c:42: CTRL_PORT |= WRITE_ENABLE;    /* latch data */
      000270 43 B0 10         [24]  426 	orl	_P3,#0x10
                                    427 ;	flash.c:43: flash_delay(TIME_QUICK);
      000273 75 82 FF         [24]  428 	mov	dpl,#0xff
      000276 12 02 E1         [24]  429 	lcall	_flash_delay
                                    430 ;	flash.c:45: flash_set_address(&sdp_addr2);
      000279 90 00 24         [24]  431 	mov	dptr,#_flash_program_sdp_addr2_65537_12
      00027C 75 F0 40         [24]  432 	mov	b,#0x40
      00027F 12 02 0F         [24]  433 	lcall	_flash_set_address
                                    434 ;	flash.c:46: CTRL_PORT &= ~WRITE_ENABLE;
      000282 53 B0 EF         [24]  435 	anl	_P3,#0xef
                                    436 ;	flash.c:47: DATA_PORT = 0x55;
      000285 75 80 55         [24]  437 	mov	_P0,#0x55
                                    438 ;	flash.c:48: CTRL_PORT |= WRITE_ENABLE;
      000288 43 B0 10         [24]  439 	orl	_P3,#0x10
                                    440 ;	flash.c:49: flash_delay(TIME_QUICK);
      00028B 75 82 FF         [24]  441 	mov	dpl,#0xff
      00028E 12 02 E1         [24]  442 	lcall	_flash_delay
                                    443 ;	flash.c:51: flash_set_address(&sdp_addr3);
      000291 90 00 27         [24]  444 	mov	dptr,#_flash_program_sdp_addr3_65537_12
      000294 75 F0 40         [24]  445 	mov	b,#0x40
      000297 12 02 0F         [24]  446 	lcall	_flash_set_address
                                    447 ;	flash.c:52: CTRL_PORT &= ~WRITE_ENABLE;
      00029A 53 B0 EF         [24]  448 	anl	_P3,#0xef
                                    449 ;	flash.c:53: DATA_PORT = 0xA0;
      00029D 75 80 A0         [24]  450 	mov	_P0,#0xa0
                                    451 ;	flash.c:54: CTRL_PORT |= WRITE_ENABLE;
      0002A0 43 B0 10         [24]  452 	orl	_P3,#0x10
                                    453 ;	flash.c:55: flash_delay(TIME_QUICK);
      0002A3 75 82 FF         [24]  454 	mov	dpl,#0xff
      0002A6 12 02 E1         [24]  455 	lcall	_flash_delay
                                    456 ;	flash.c:58: flash_set_address(address);
      0002A9 85 2A 82         [24]  457 	mov	dpl,_flash_program_PARM_2
      0002AC 85 2B 83         [24]  458 	mov	dph,(_flash_program_PARM_2 + 1)
      0002AF 85 2C F0         [24]  459 	mov	b,(_flash_program_PARM_2 + 2)
      0002B2 12 02 0F         [24]  460 	lcall	_flash_set_address
      0002B5 D0 07            [24]  461 	pop	ar7
                                    462 ;	flash.c:59: CTRL_PORT &= ~WRITE_ENABLE;
      0002B7 53 B0 EF         [24]  463 	anl	_P3,#0xef
                                    464 ;	flash.c:60: DATA_PORT = data;
      0002BA 8F 80            [24]  465 	mov	_P0,r7
                                    466 ;	flash.c:61: CTRL_PORT |= WRITE_ENABLE;
      0002BC 43 B0 10         [24]  467 	orl	_P3,#0x10
                                    468 ;	flash.c:64: flash_delay(TIME_QUICK);
      0002BF 75 82 FF         [24]  469 	mov	dpl,#0xff
      0002C2 12 02 E1         [24]  470 	lcall	_flash_delay
                                    471 ;	flash.c:67: flash_init();
                                    472 ;	flash.c:68: }
      0002C5 02 02 0B         [24]  473 	ljmp	_flash_init
                                    474 ;------------------------------------------------------------
                                    475 ;Allocation info for local variables in function 'flash_read'
                                    476 ;------------------------------------------------------------
                                    477 ;address                   Allocated to registers r5 r6 r7 
                                    478 ;data                      Allocated to registers r7 
                                    479 ;------------------------------------------------------------
                                    480 ;	flash.c:72: char flash_read(address_t *address)
                                    481 ;	-----------------------------------------
                                    482 ;	 function flash_read
                                    483 ;	-----------------------------------------
      0002C8                        484 _flash_read:
                                    485 ;	flash.c:74: flash_set_address(address);
      0002C8 12 02 0F         [24]  486 	lcall	_flash_set_address
                                    487 ;	flash.c:77: CTRL_PORT &= ~(CHIP_ENABLE | OUTPUT_ENABLE);
      0002CB 53 B0 9F         [24]  488 	anl	_P3,#0x9f
                                    489 ;	flash.c:78: char data = DATA_PORT;
      0002CE AF 80            [24]  490 	mov	r7,_P0
                                    491 ;	flash.c:81: flash_init();
      0002D0 C0 07            [24]  492 	push	ar7
      0002D2 12 02 0B         [24]  493 	lcall	_flash_init
      0002D5 D0 07            [24]  494 	pop	ar7
                                    495 ;	flash.c:82: return data;
      0002D7 8F 82            [24]  496 	mov	dpl,r7
                                    497 ;	flash.c:83: }
      0002D9 22               [24]  498 	ret
                                    499 ;------------------------------------------------------------
                                    500 ;Allocation info for local variables in function 'flash_erase'
                                    501 ;------------------------------------------------------------
                                    502 ;addr                      Allocated to registers r5 r6 r7 
                                    503 ;------------------------------------------------------------
                                    504 ;	flash.c:87: void flash_erase(address_t *addr)
                                    505 ;	-----------------------------------------
                                    506 ;	 function flash_erase
                                    507 ;	-----------------------------------------
      0002DA                        508 _flash_erase:
                                    509 ;	flash.c:89: flash_set_address(addr);
      0002DA 12 02 0F         [24]  510 	lcall	_flash_set_address
                                    511 ;	flash.c:91: CTRL_PORT &= ~(CHIP_ENABLE | WRITE_ENABLE);
      0002DD 53 B0 CF         [24]  512 	anl	_P3,#0xcf
                                    513 ;	flash.c:92: }
      0002E0 22               [24]  514 	ret
                                    515 ;------------------------------------------------------------
                                    516 ;Allocation info for local variables in function 'flash_delay'
                                    517 ;------------------------------------------------------------
                                    518 ;count                     Allocated to registers r7 
                                    519 ;i                         Allocated to registers r6 
                                    520 ;j                         Allocated to registers r5 
                                    521 ;------------------------------------------------------------
                                    522 ;	flash.c:96: void flash_delay(char count)
                                    523 ;	-----------------------------------------
                                    524 ;	 function flash_delay
                                    525 ;	-----------------------------------------
      0002E1                        526 _flash_delay:
      0002E1 AF 82            [24]  527 	mov	r7,dpl
                                    528 ;	flash.c:98: for (char i = 0; i < 0xFF; i++)
      0002E3 7E 00            [12]  529 	mov	r6,#0x00
      0002E5                        530 00107$:
      0002E5 BE FF 00         [24]  531 	cjne	r6,#0xff,00129$
      0002E8                        532 00129$:
      0002E8 50 0D            [24]  533 	jnc	00109$
                                    534 ;	flash.c:100: for (char j = 0; j < count; j++);
      0002EA 7D 00            [12]  535 	mov	r5,#0x00
      0002EC                        536 00104$:
      0002EC C3               [12]  537 	clr	c
      0002ED ED               [12]  538 	mov	a,r5
      0002EE 9F               [12]  539 	subb	a,r7
      0002EF 50 03            [24]  540 	jnc	00108$
      0002F1 0D               [12]  541 	inc	r5
      0002F2 80 F8            [24]  542 	sjmp	00104$
      0002F4                        543 00108$:
                                    544 ;	flash.c:98: for (char i = 0; i < 0xFF; i++)
      0002F4 0E               [12]  545 	inc	r6
      0002F5 80 EE            [24]  546 	sjmp	00107$
      0002F7                        547 00109$:
                                    548 ;	flash.c:102: }
      0002F7 22               [24]  549 	ret
                                    550 	.area CSEG    (CODE)
                                    551 	.area CONST   (CODE)
                                    552 	.area XINIT   (CODE)
                                    553 	.area CABS    (ABS,CODE)
