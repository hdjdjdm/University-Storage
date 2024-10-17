*****************************************************************************
*       Copyright (C) 1996-1997 Texas Instruments Incorporated
*                    All Rights Reserved
*       A13_FIR HAND ASSEMBLY - Example 5-59
*       From Programmer's Guide
*       FINITE IMPULSE RESPONSE FILTER - PERFORMS 2 SAMPLES AT A TIME
*                                      - EVEN n >= 2
*****************************************************************************
******* ASSEMBLY CODE: *******************
	.global _fir_asm
	.text
_fir_asm:
	STW	.D2	B10,*B15--	; push register
	STW	.D2	B11,*B15--	; push register
	STW	.D2	B12,*B15--	; push register
	STW	.D2	B13,*B15--	; push register
	STW	.D2	B14,*B15--	; push register
	STW	.D2	A10,*B15--	; push register
	STW	.D2	A11,*B15--	; push register
	STW	.D2	A12,*B15--	; push register
	STW	.D2	A13,*B15--	; push register
	STW	.D2	A14,*B15--	; push register
	STW	.D2	A15,*B15--	; push register

	MV	.L1X	B4,A0		; point to h[0] & h[1]
||	ADD	.D2	B4,4,B2		; point to h[2] & h[3]
||	MV	.L2X	A4,B1		; point to x[j] & x[j+1]
||	ADD	.D1	A4,4,A4		; point to x[j+2] & x[j+3]
||	MVK	.S2	200,B0		; set up loop counter ((128/8)*(100/2))

  	LDW	.D1	*A4++[2],B9	; x[j+i+2] & x[j+i+3]
||	LDW	.D2	*B1++[2],A10	; x[j+i+0] & x[j+i+1]
||	MVK	.S1	4,A1		; set pointer reset lp cntr

  	LDW	.D2	*B2++[2],B7	; h[i+2] & h[i+3]
||	LDW	.D1	*A0++[2],A8	; h[i+0] & h[i+1]
||	MVK	.S1	60,A3		; used to reset x ptr (16*4-4)
||	MVK	.S2	60,B14		; used to reset x ptr (16*4-4)

  	LDW	.D2	*B1++[2],A11	; x[j+i+4] & x[j+i+5]
||	LDW	.D1	*A4++[2],B10	; x[j+i+6] & x[j+i+7]
||[A1]	SUB	.L1	A1,1,A1		; dec pointer reset lp cntr
||	MVK	.S1	64,A5		; used to reset h ptr (16*4)
||	MVK	.S2	64,B5		; used to reset h ptr (16*4)
||	ADD	.L2X	A6,2,B6		; point to y[j+1]

  	LDW	.D1	*A0++[2],A9	; h[i+4] & h[i+5]
||	LDW	.D2	*B2++[2],B8	; h[i+6] & h[i+7]
||[!A1]	SUB	.S1	A4,A3,A4	; reset x ptr

  [!A1]	SUB	.S2	B1,B14,B1	; reset x ptr
||[!A1]	SUB	.S1	A0,A5,A0	; reset h ptr
||	LDH	.D2	*B1,A8		; x[j+i+8]

  	ADD	.S2X	A10,0,B8	; move to other reg file
||	MVK	.S1	5,A2		; set store lp cntr

  	MPYLH	.M2X	A8,B8,B4	; p10 = h[i+0]*x[j+i+1]
||[!A1]	SUB	.S2	B2,B5,B2	; reset h ptr
||	MPYHL	.M1X	A8,B9,A14	; p11 = h[i+1]*x[j+i+2]

  	MPY	.M1	A8,A10,A7	; p00 = h[i+0]*x[j+i+0]
||	MPYLH	.M2	B7,B9,B13	; p12 = h[i+2]*x[j+i+3]
||[A2]	SUB	.S1	A2,1,A2		; dec store lp cntr
||	ZERO	.L2	B11		; zero out initial accumulator

  [!A2]	SHR	.S2	B11,15,B11	; (Bsum1 >> 15)
||	MPY	.M2	B7,B9,B9	; p02 = h[i+2]*x[j+i+2]
||	MPYH	.M1	A8,A10,A10	; p01 = h[i+1]*x[j+i+1]
||[A2]	ADD	.L2	B4,B11,B4	; sum1(p10) = p10 + sum1
||	LDW	.D1	*A4++[2],B9	;* x[j+i+2] & x[j+i+3]
||	LDW	.D2	*B1++[2],A10	;* x[j+i+0] & x[j+i+1]
||	ZERO	.L1	A10		; zero out initial accumulator

LOOP:
  [!A2]	SHR	.S1	A10,15,A12	; (Asum0 >> 15)
||[B0]	SUB	.S2	B0,1,B0		; dec outer lp cntr
||	MPYH	.M2	B7,B9,B13	; p03 = h[i+3]*x[j+i+3]
||[A2]	ADD	.L1	A7,A10,A7	; sum0(p00) = p00 + sum0
||	MPYHL	.M1X	B7,A11,A10	; p13 = h[i+3]*x[j+i+4]
||	ADD	.L2X	A14,B4,B7	; sum1 += p11
||	LDW	.D2	*B2++[2],B7	;* h[i+2] & h[i+3]
||	LDW	.D1	*A0++[2],A8	;* h[i+0] & h[i+1]

  	ADD	.L1	A10,A7,A13	; sum0 += p01
||	MPYHL	.M2X	A9,B10,B12	; p15 = h[i+5]*x[j+i+6]
||	MPYLH	.M1	A9,A11,A10	; p14 = h[i+4]*x[j+i+5]
||	ADD	.L2	B13,B7,B7	; sum1 +=  p12
||	LDW	.D2	*B1++[2],A11	;* x[j+i+4] & x[j+i+5]
||	LDW	.D1	*A4++[2],B10	;* x[j+i+6] & x[j+i+7]
||[A1]	SUB	.S1	A1,1,A1		;* dec pointer reset lp cntr

  [B0]	B	.S2	LOOP		; Branch outer loop
||	MPY	.M1	A9,A11,A11	; p04 = h[i+4]*x[j+i+4]
||	ADD	.L1X	B9,A13,A13	; sum0 += p02
||	MPYLH	.M2	B8,B10,B13	; p16 = h[i+6]*x[j+i+7]
||	ADD	.L2X	A10,B7,B7	; sum1 += p13
||	LDW	.D1	*A0++[2],A9	;* h[i+4] & h[i+5]
||	LDW	.D2	*B2++[2],B8	;* h[i+6] & h[i+7]
||[!A1]	SUB	.S1	A4,A3,A4	;* reset x ptr

  	MPY	.M2	B8,B10,B11	; p06 = h[i+6]*x[j+i+6]
||	MPYH	.M1	A9,A11,A11	; p05 = h[i+5]*x[j+i+5]
||	ADD	.L1X	B13,A13,A9	; sum0 += p03
||	ADD	.L2X	A10,B7,B7	; sum1 += p14
||[!A1]	SUB	.S2	B1,B14,B1	;* reset x ptr
||[!A1]	SUB	.S1	A0,A5,A0	;* reset h ptr
||	LDH	.D2	*B1,A8		;* x[j+i+8]

  [!A2]	MVK	.S1	4,A2		; reset store lp cntr
||	MPYH	.M2	B8,B10,B13	; p07 = h[i+7]*x[j+i+7]
||	ADD	.L1	A11,A9,A9	; sum0 += p04
||	MPYHL	.M1X	B8,A8,A9	; p17 = h[i+7]*x[j+i+8]
||	ADD	.S2	B12,B7,B10	; sum1 += p15
||[!A2]	STH	.D2	B11,*B6++[2]	; y[j+1] = (Bsum1 >> 15)
||[!A2]	STH	.D1	A12,*A6++[2]	; y[j] = (Asum0 >> 15)
||	ADD	.L2X	A10,0,B8	;* move to other reg file

  	ADD	.L1	A11,A9,A12	; sum0 += p05
||	ADD	.L2	B13,B10,B8	; sum1 += p16
||	MPYLH	.M2X	A8,B8,B4	;* p10 = h[i+0]*x[j+i+1]
||[!A1]	MVK	.S1	4,A1		;* reset pointer reset lp cntr
||[!A1]	SUB	.S2	B2,B5,B2	;* reset h ptr
||	MPYHL	.M1X	A8,B9,A14	;* p11 = h[i+1]*x[j+i+2]

  	ADD	.L2X	A9,B8,B11	; sum1 += p17
||	ADD	.L1X	B11,A12,A12	; sum0 += p06
||	MPY	.M1	A8,A10,A7	;* p00 = h[i+0]*x[j+i+0]
||	MPYLH	.M2	B7,B9,B13	;* p12 = h[i+2]*x[j+i+3]
||[A2]	SUB	.S1	A2,1,A2		;* dec store lp cntr

  	ADD	.L1X	B13,A12,A10	; sum0 += p07
||[!A2]	SHR	.S2	B11,15,B11	;* (Bsum1 >> 15)
||	MPY	.M2	B7,B9,B9	;* p02 = h[i+2]*x[j+i+2]
||	MPYH	.M1	A8,A10,A10	;* p01 = h[i+1]*x[j+i+1]
||[A2]	ADD	.L2	B4,B11,B4	;* sum1(p10) = p10 + sum1
||	LDW	.D1	*A4++[2],B9	;** x[j+i+2] & x[j+i+3]
||	LDW	.D2	*B1++[2],A10	;** x[j+i+0] & x[j+i+1]

  [!A2]	SHR	.S1	A10,15,A12	; (Asum0 >> 15)

  [!A2]	STH	.D2	B11,*B6++[2]	; y[j+1] = (Bsum1 >> 15)
||[!A2]	STH	.D1	A12,*A6++[2]	; y[j] = (Asum0 >> 15)

	LDW	.D2	*++B15,A15	; pop register

	LDW	.D2	*++B15,A14	; pop register

	LDW	.D2	*++B15,A13	; pop register

	LDW	.D2	*++B15,A12	; pop register

	LDW	.D2	*++B15,A11	; pop register

	LDW	.D2	*++B15,A10	; pop register

	LDW	.D2	*++B15,B14	; pop register

	LDW	.D2	*++B15,B13	; pop register

	LDW	.D2	*++B15,B12	; pop register

	LDW	.D2	*++B15,B11	; pop register
||	B	.S2	B3		; return

	LDW	.D2	*++B15,B10	; pop register

        NOP     4

