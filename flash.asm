;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module flash
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _B
	.globl _ACC
	.globl _PSW
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _flash_program_PARM_2
	.globl _flash_init
	.globl _flash_set_address
	.globl _flash_program
	.globl _flash_read
	.globl _flash_erase
	.globl _flash_delay
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_flash_program_sdp_addr1_65537_12:
	.ds 3
_flash_program_sdp_addr2_65537_12:
	.ds 3
_flash_program_sdp_addr3_65537_12:
	.ds 3
_flash_program_PARM_2:
	.ds 3
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_program'
;------------------------------------------------------------
;sdp_addr1                 Allocated with name '_flash_program_sdp_addr1_65537_12'
;sdp_addr2                 Allocated with name '_flash_program_sdp_addr2_65537_12'
;sdp_addr3                 Allocated with name '_flash_program_sdp_addr3_65537_12'
;address                   Allocated with name '_flash_program_PARM_2'
;data                      Allocated to registers r7 
;------------------------------------------------------------
;	flash.c:35: static address_t sdp_addr1 = { 0x00, 0x55, 0x55 };
	mov	_flash_program_sdp_addr1_65537_12,#0x00
	mov	(_flash_program_sdp_addr1_65537_12 + 0x0001),#0x55
	mov	(_flash_program_sdp_addr1_65537_12 + 0x0002),#0x55
;	flash.c:36: static address_t sdp_addr2 = { 0x00, 0x2A, 0xAA };
	mov	_flash_program_sdp_addr2_65537_12,#0x00
	mov	(_flash_program_sdp_addr2_65537_12 + 0x0001),#0x2a
	mov	(_flash_program_sdp_addr2_65537_12 + 0x0002),#0xaa
;	flash.c:37: static address_t sdp_addr3 = { 0x00, 0x55, 0x55 };
	mov	_flash_program_sdp_addr3_65537_12,#0x00
	mov	(_flash_program_sdp_addr3_65537_12 + 0x0001),#0x55
	mov	(_flash_program_sdp_addr3_65537_12 + 0x0002),#0x55
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_init'
;------------------------------------------------------------
;	flash.c:5: void flash_init()
;	-----------------------------------------
;	 function flash_init
;	-----------------------------------------
_flash_init:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
;	flash.c:7: CTRL_PORT |= CHIP_ENABLE | OUTPUT_ENABLE | WRITE_ENABLE;
	orl	_P3,#0x70
;	flash.c:8: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_set_address'
;------------------------------------------------------------
;address                   Allocated to registers r5 r6 r7 
;high_bits                 Allocated to registers r5 
;------------------------------------------------------------
;	flash.c:12: void flash_set_address(address_t *address)
;	-----------------------------------------
;	 function flash_set_address
;	-----------------------------------------
_flash_set_address:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
;	flash.c:15: P1 = address->low;
	mov	a,#0x02
	add	a,r5
	mov	r2,a
	clr	a
	addc	a,r6
	mov	r3,a
	mov	ar4,r7
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_P1,a
;	flash.c:16: P2 = address->middle;
	mov	a,#0x01
	add	a,r5
	mov	r2,a
	clr	a
	addc	a,r6
	mov	r3,a
	mov	ar4,r7
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_P2,a
;	flash.c:19: char high_bits = address->high;
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
;	flash.c:20: P3 &= ~(7 << 2);
	anl	_P3,#0xe3
;	flash.c:21: high_bits &= 0x03; /* isolate first three bits */
	anl	ar5,#0x03
;	flash.c:22: high_bits <<= 2;   /* shift bits over to match port */
	mov	a,r5
	add	a,r5
;	flash.c:23: P3 |= high_bits;
	add	a,acc
	orl	_P3,a
;	flash.c:24: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_program'
;------------------------------------------------------------
;sdp_addr1                 Allocated with name '_flash_program_sdp_addr1_65537_12'
;sdp_addr2                 Allocated with name '_flash_program_sdp_addr2_65537_12'
;sdp_addr3                 Allocated with name '_flash_program_sdp_addr3_65537_12'
;address                   Allocated with name '_flash_program_PARM_2'
;data                      Allocated to registers r7 
;------------------------------------------------------------
;	flash.c:28: void flash_program(char data, address_t *address)
;	-----------------------------------------
;	 function flash_program
;	-----------------------------------------
_flash_program:
	mov	r7,dpl
;	flash.c:31: CTRL_PORT &= ~CHIP_ENABLE;
	anl	_P3,#0xdf
;	flash.c:32: flash_delay(TIME_QUICK);
	mov	dpl,#0xff
	push	ar7
	lcall	_flash_delay
;	flash.c:39: flash_set_address(&sdp_addr1);
	mov	dptr,#_flash_program_sdp_addr1_65537_12
	mov	b,#0x40
	lcall	_flash_set_address
;	flash.c:40: CTRL_PORT &= ~WRITE_ENABLE;    /* latch address */
	anl	_P3,#0xef
;	flash.c:41: DATA_PORT = 0xAA;
	mov	_P0,#0xaa
;	flash.c:42: CTRL_PORT |= WRITE_ENABLE;    /* latch data */
	orl	_P3,#0x10
;	flash.c:43: flash_delay(TIME_QUICK);
	mov	dpl,#0xff
	lcall	_flash_delay
;	flash.c:45: flash_set_address(&sdp_addr2);
	mov	dptr,#_flash_program_sdp_addr2_65537_12
	mov	b,#0x40
	lcall	_flash_set_address
;	flash.c:46: CTRL_PORT &= ~WRITE_ENABLE;
	anl	_P3,#0xef
;	flash.c:47: DATA_PORT = 0x55;
	mov	_P0,#0x55
;	flash.c:48: CTRL_PORT |= WRITE_ENABLE;
	orl	_P3,#0x10
;	flash.c:49: flash_delay(TIME_QUICK);
	mov	dpl,#0xff
	lcall	_flash_delay
;	flash.c:51: flash_set_address(&sdp_addr3);
	mov	dptr,#_flash_program_sdp_addr3_65537_12
	mov	b,#0x40
	lcall	_flash_set_address
;	flash.c:52: CTRL_PORT &= ~WRITE_ENABLE;
	anl	_P3,#0xef
;	flash.c:53: DATA_PORT = 0xA0;
	mov	_P0,#0xa0
;	flash.c:54: CTRL_PORT |= WRITE_ENABLE;
	orl	_P3,#0x10
;	flash.c:55: flash_delay(TIME_QUICK);
	mov	dpl,#0xff
	lcall	_flash_delay
;	flash.c:58: flash_set_address(address);
	mov	dpl,_flash_program_PARM_2
	mov	dph,(_flash_program_PARM_2 + 1)
	mov	b,(_flash_program_PARM_2 + 2)
	lcall	_flash_set_address
	pop	ar7
;	flash.c:59: CTRL_PORT &= ~WRITE_ENABLE;
	anl	_P3,#0xef
;	flash.c:60: DATA_PORT = data;
	mov	_P0,r7
;	flash.c:61: CTRL_PORT |= WRITE_ENABLE;
	orl	_P3,#0x10
;	flash.c:64: flash_delay(TIME_QUICK);
	mov	dpl,#0xff
	lcall	_flash_delay
;	flash.c:67: flash_init();
;	flash.c:68: }
	ljmp	_flash_init
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_read'
;------------------------------------------------------------
;address                   Allocated to registers r5 r6 r7 
;data                      Allocated to registers r7 
;------------------------------------------------------------
;	flash.c:72: char flash_read(address_t *address)
;	-----------------------------------------
;	 function flash_read
;	-----------------------------------------
_flash_read:
;	flash.c:74: flash_set_address(address);
	lcall	_flash_set_address
;	flash.c:77: CTRL_PORT &= ~(CHIP_ENABLE | OUTPUT_ENABLE);
	anl	_P3,#0x9f
;	flash.c:78: char data = DATA_PORT;
	mov	r7,_P0
;	flash.c:81: flash_init();
	push	ar7
	lcall	_flash_init
	pop	ar7
;	flash.c:82: return data;
	mov	dpl,r7
;	flash.c:83: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_erase'
;------------------------------------------------------------
;addr                      Allocated to registers r5 r6 r7 
;------------------------------------------------------------
;	flash.c:87: void flash_erase(address_t *addr)
;	-----------------------------------------
;	 function flash_erase
;	-----------------------------------------
_flash_erase:
;	flash.c:89: flash_set_address(addr);
	lcall	_flash_set_address
;	flash.c:91: CTRL_PORT &= ~(CHIP_ENABLE | WRITE_ENABLE);
	anl	_P3,#0xcf
;	flash.c:92: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'flash_delay'
;------------------------------------------------------------
;count                     Allocated to registers r7 
;i                         Allocated to registers r6 
;j                         Allocated to registers r5 
;------------------------------------------------------------
;	flash.c:96: void flash_delay(char count)
;	-----------------------------------------
;	 function flash_delay
;	-----------------------------------------
_flash_delay:
	mov	r7,dpl
;	flash.c:98: for (char i = 0; i < 0xFF; i++)
	mov	r6,#0x00
00107$:
	cjne	r6,#0xff,00129$
00129$:
	jnc	00109$
;	flash.c:100: for (char j = 0; j < count; j++);
	mov	r5,#0x00
00104$:
	clr	c
	mov	a,r5
	subb	a,r7
	jnc	00108$
	inc	r5
	sjmp	00104$
00108$:
;	flash.c:98: for (char i = 0; i < 0xFF; i++)
	inc	r6
	sjmp	00107$
00109$:
;	flash.c:102: }
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
