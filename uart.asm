;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module uart
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _strlen
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
	.globl _uart_init
	.globl _uart_print
	.globl _uart_print_esc
	.globl _uart_print_char
	.globl _uart_print_hex
	.globl _uart_isr
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
; overlayable bit register bank
;--------------------------------------------------------
	.area BIT_BANK	(REL,OVR,DATA)
bits:
	.ds 1
	b0 = bits[0]
	b1 = bits[1]
	b2 = bits[2]
	b3 = bits[3]
	b4 = bits[4]
	b5 = bits[5]
	b6 = bits[6]
	b7 = bits[7]
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_uart_print_str_65536_31:
	.ds 3
_uart_print_hex_hex_chars_65536_41:
	.ds 17
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
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
;Allocation info for local variables in function 'uart_print_hex'
;------------------------------------------------------------
;hex_chars                 Allocated with name '_uart_print_hex_hex_chars_65536_41'
;val                       Allocated to registers r7 
;------------------------------------------------------------
;	uart.c:65: static char hex_chars[] = "0123456789ABCDEF";
	mov	_uart_print_hex_hex_chars_65536_41,#0x30
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0001),#0x31
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0002),#0x32
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0003),#0x33
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0004),#0x34
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0005),#0x35
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0006),#0x36
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0007),#0x37
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0008),#0x38
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0009),#0x39
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000a),#0x41
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000b),#0x42
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000c),#0x43
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000d),#0x44
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000e),#0x45
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x000f),#0x46
	mov	(_uart_print_hex_hex_chars_65536_41 + 0x0010),#0x00
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
;Allocation info for local variables in function 'uart_init'
;------------------------------------------------------------
;	uart.c:6: void uart_init()
;	-----------------------------------------
;	 function uart_init
;	-----------------------------------------
_uart_init:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
;	uart.c:9: TMOD |= 0x20;   /* timer 1 in mode 2 (8-bit overflow) */
	orl	_TMOD,#0x20
;	uart.c:10: TH1   = 0xF5;   /* timer reload value for baud = 9600 */
	mov	_TH1,#0xf5
;	uart.c:11: PCON |= 0x80;   /* set SMOD1 */
	orl	_PCON,#0x80
;	uart.c:12: TCON |= 0x40;   /* enable timer */
	orl	_TCON,#0x40
;	uart.c:15: SCON  = 0x50;   /* mode 1 (8 bit tx/rx) + enable receive */
	mov	_SCON,#0x50
;	uart.c:18: EA = 1;
;	assignBit
	setb	_EA
;	uart.c:19: ES = 1;
;	assignBit
	setb	_ES
;	uart.c:20: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'uart_print'
;------------------------------------------------------------
;string                    Allocated to registers r5 r6 r7 
;str                       Allocated with name '_uart_print_str_65536_31'
;i                         Allocated to registers r6 r7 
;------------------------------------------------------------
;	uart.c:24: void uart_print(char *string)
;	-----------------------------------------
;	 function uart_print
;	-----------------------------------------
_uart_print:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
;	uart.c:27: const char *str = string;
	mov	_uart_print_str_65536_31,r5
	mov	(_uart_print_str_65536_31 + 1),r6
	mov	(_uart_print_str_65536_31 + 2),r7
;	uart.c:28: if (string == NULL)
	mov	a,r5
	orl	a,r6
	jnz	00111$
;	uart.c:30: str = "Error print string is null";
	mov	_uart_print_str_65536_31,#___str_0
	mov	(_uart_print_str_65536_31 + 1),#(___str_0 >> 8)
	mov	(_uart_print_str_65536_31 + 2),#0x80
;	uart.c:33: for (int i = 0; i < strlen(str); i++)
00111$:
	mov	r6,#0x00
	mov	r7,#0x00
00105$:
	mov	dpl,_uart_print_str_65536_31
	mov	dph,(_uart_print_str_65536_31 + 1)
	mov	b,(_uart_print_str_65536_31 + 2)
	push	ar7
	push	ar6
	lcall	_strlen
	mov	r1,dpl
	mov	r5,dph
	pop	ar6
	pop	ar7
	mov	ar0,r6
	mov	ar4,r7
	clr	c
	mov	a,r0
	subb	a,r1
	mov	a,r4
	subb	a,r5
	jnc	00107$
;	uart.c:35: uart_print_char(str[i]);
	mov	a,r6
	add	a,_uart_print_str_65536_31
	mov	r3,a
	mov	a,r7
	addc	a,(_uart_print_str_65536_31 + 1)
	mov	r4,a
	mov	r5,(_uart_print_str_65536_31 + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	lcall	__gptrget
	mov	dpl,a
	push	ar7
	push	ar6
	lcall	_uart_print_char
	pop	ar6
	pop	ar7
;	uart.c:33: for (int i = 0; i < strlen(str); i++)
	inc	r6
	cjne	r6,#0x00,00105$
	inc	r7
	sjmp	00105$
00107$:
;	uart.c:37: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'uart_print_esc'
;------------------------------------------------------------
;code                      Allocated to registers r5 r6 r7 
;------------------------------------------------------------
;	uart.c:41: void uart_print_esc(char *code)
;	-----------------------------------------
;	 function uart_print_esc
;	-----------------------------------------
_uart_print_esc:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
;	uart.c:43: if (code == NULL)
	mov	a,r5
	orl	a,r6
	jnz	00102$
;	uart.c:45: uart_print("Error escape code is null");
	mov	dptr,#___str_1
	mov	b,#0x80
;	uart.c:46: return;
	ljmp	_uart_print
00102$:
;	uart.c:48: uart_print_char(ESC_CHAR);
	mov	dpl,#0x1b
	push	ar7
	push	ar6
	push	ar5
	lcall	_uart_print_char
	pop	ar5
	pop	ar6
	pop	ar7
;	uart.c:49: uart_print(code);
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
;	uart.c:50: }
	ljmp	_uart_print
;------------------------------------------------------------
;Allocation info for local variables in function 'uart_print_char'
;------------------------------------------------------------
;ch                        Allocated to registers 
;------------------------------------------------------------
;	uart.c:54: void uart_print_char(char ch)
;	-----------------------------------------
;	 function uart_print_char
;	-----------------------------------------
_uart_print_char:
	mov	_SBUF,dpl
;	uart.c:57: while (TI == 0);
00101$:
;	uart.c:58: TI = 0;
;	assignBit
	jbc	_TI,00114$
	sjmp	00101$
00114$:
;	uart.c:59: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'uart_print_hex'
;------------------------------------------------------------
;hex_chars                 Allocated with name '_uart_print_hex_hex_chars_65536_41'
;val                       Allocated to registers r7 
;------------------------------------------------------------
;	uart.c:63: void uart_print_hex(char val)
;	-----------------------------------------
;	 function uart_print_hex
;	-----------------------------------------
_uart_print_hex:
;	uart.c:66: uart_print_char(hex_chars[val >> 4]);
	mov	a,dpl
	mov	r7,a
	swap	a
	anl	a,#0x0f
	add	a,#_uart_print_hex_hex_chars_65536_41
	mov	r1,a
	mov	dpl,@r1
	push	ar7
	lcall	_uart_print_char
	pop	ar7
;	uart.c:67: uart_print_char(hex_chars[val & 0x0F]);
	anl	ar7,#0x0f
	mov	a,r7
	add	a,#_uart_print_hex_hex_chars_65536_41
	mov	r1,a
	mov	dpl,@r1
;	uart.c:68: }
	ljmp	_uart_print_char
;------------------------------------------------------------
;Allocation info for local variables in function 'uart_isr'
;------------------------------------------------------------
;	uart.c:72: void uart_isr() __interrupt (4)
;	-----------------------------------------
;	 function uart_isr
;	-----------------------------------------
_uart_isr:
	push	bits
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+7)
	push	(0+6)
	push	(0+5)
	push	(0+4)
	push	(0+3)
	push	(0+2)
	push	(0+1)
	push	(0+0)
	push	psw
	mov	psw,#0x00
;	uart.c:74: if (RI)
;	uart.c:76: RI = 0;
;	assignBit
	jbc	_RI,00109$
	sjmp	00103$
00109$:
;	uart.c:77: uart_print_char(SBUF);
	mov	dpl,_SBUF
	lcall	_uart_print_char
00103$:
;	uart.c:79: }
	pop	psw
	pop	(0+0)
	pop	(0+1)
	pop	(0+2)
	pop	(0+3)
	pop	(0+4)
	pop	(0+5)
	pop	(0+6)
	pop	(0+7)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	pop	bits
	reti
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area CONST   (CODE)
___str_0:
	.ascii "Error print string is null"
	.db 0x00
	.area CSEG    (CODE)
	.area CONST   (CODE)
___str_1:
	.ascii "Error escape code is null"
	.db 0x00
	.area CSEG    (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
