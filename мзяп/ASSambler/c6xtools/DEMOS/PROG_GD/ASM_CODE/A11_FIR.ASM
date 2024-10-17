**************************************************************************
*       Copyright (C) 1996-1997 Texas Instruments Incorporated
*                    All Rights Reserved
*       A11_FIR HAND ASSEMBLY - Example 5-50
*       From Programmer's Guide
*       FINITE IMPULSE RESPONSE FILTER - PERFORMS 2 SAMPLES AT A TIME
*                                      - EVEN n >= 2
**************************************************************************
******* ASSEMBLY CODE: *******************
	.global _fir_asm
	.text
_fir_asm:
	STW	.D2	B10,*B15--	; push register
||	MVK	.S1	50,A2		; set up outer loop counter

	MVK	.S1	62,A3		; used to rst x pointer each outer loop
||	MVK	.S2	64,B10		; used to rst h pointer each outer loop

OUTLOOP:
	LDH	.D1	*A4++,B5	; x0 = x[j]
||	ADD	.L2X	A4,4,B1		; set up pointer to x[j+2]
||	ADD	.L1X	B4,2,A8		; set up pointer to h[1]
||	MVK	.S2	8,B2		; set up inner loop counter
||[A2]	SUB	.S1	A2,1,A2		; decrement outer loop counter


  	LDH	.D2	*B1++[2],B0	; x2 = x[j+i+2]
||	LDH	.D1	*A4++[2],A0	; x1 = x[j+i+1]
||	ZERO	.L1	A9		; zero out sum0
||	ZERO	.L2	B9		; zero out sum1

  	LDH	.D1	*A8++[2],B6	; h1 = h[i+1]
||	LDH	.D2	*B4++[2],A1	; h0 = h[i]

  	LDH	.D1	*A4++[2],A5	; x3 = x[j+i+3]
||	LDH	.D2	*B1++[2],B5	; x0 = x[j+i+4]

  	LDH	.D2	*B4++[2],A7	; h2 = h[i+2]
||	LDH	.D1	*A8++[2],B8	; h3 = h[i+3]
||[B2]	SUB	.S2	B2,1,B2		; decrement loop counter

  	LDH	.D2	*B1++[2],B0	;* x2 = x[j+i+2]
||	LDH	.D1	*A4++[2],A0	;* x1 = x[j+i+1]

	LDH	.D1	*A8++[2],B6	;* h1 = h[i+1]
||	LDH	.D2	*B4++[2],A1	;* h0 = h[i]

  	MPY	.M1X	B5,A1,A0	; x0 * h0
||	MPY	.M2X	A0,B6,B6	; x1 * h1
||	LDH	.D1	*A4++[2],A5	;* x3 = x[j+i+3]
||	LDH	.D2	*B1++[2],B5	;* x0 = x[j+i+4]

  [B2]	B	.S1	LOOP		; branch to loop
||	MPY	.M2	B0,B6,B7	; x2 * h1
||	MPY	.M1	A0,A1,A1	; x1 * h0
||	LDH	.D2	*B4++[2],A7	;* h2 = h[i+2]
||	LDH	.D1	*A8++[2],B8	;* h3 = h[i+3]
||[B2]	SUB	.S2	B2,1,B2		;* decrement loop counter

  	ADD	.L1	A0,A9,A9	; sum0 += x0 * h0
||	MPY	.M2X	A5,B8,B8	; x3 * h3
||	MPY	.M1X	B0,A7,A5	; x2 * h2
||	LDH	.D2	*B1++[2],B0	;** x2 = x[j+i+2]
||	LDH	.D1	*A4++[2],A0	;** x1 = x[j+i+1]

LOOP:
  	ADD	.L2X	A1,B9,B9	; sum1 += x1 * h0
||	ADD	.L1X	B6,A9,A9	; sum0 += x1 * h1
||	MPY	.M2	B5,B8,B7	; x0 * h3
||	MPY	.M1	A5,A7,A7	; x3 * h2
||[B2]	LDH	.D1	*A8++[2],B6	;** h1 = h[i+1]
||[B2]	LDH	.D2	*B4++[2],A1	;** h0 = h[i]

  	ADD	.L2	B7,B9,B9	; sum1 += x2 * h1
||	ADD	.L1	A5,A9,A9	; sum0 += x2 * h2
||	MPY	.M1X	B5,A1,A0	;* x0 * h0
||	MPY	.M2X	A0,B6,B6	;* x1 * h1
||[B2]	LDH	.D1	*A4++[2],A5	;** x3 = x[j+i+3]
||[B2]	LDH	.D2	*B1++[2],B5	;** x0 = x[j+i+4]

  	ADD	.L2X	A7,B9,B9	; sum1 += x3 * h2
||	ADD	.L1X	B8,A9,A9	; sum0 += x3 * h3
||[B2]	B	.S1	LOOP		;* branch to loop
||	MPY	.M2	B0,B6,B7	;* x2 * h1
||	MPY	.M1	A0,A1,A1	;* x1 * h0
||[B2]	LDH	.D2	*B4++[2],A7	;** h2 = h[i+2]
||[B2]	LDH	.D1	*A8++[2],B8	;** h3 = h[i+3]
||[B2]	SUB	.S2	B2,1,B2		;** decrement loop counter

  	ADD	.L2	B7,B9,B9	; sum1 += x0 * h3
||	ADD	.L1	A0,A9,A9	;* sum0 += x0 * h0
||	MPY	.M2X	A5,B8,B8	;* x3 * h3
||	MPY	.M1X	B0,A7,A5	;* x2 * h2
||[B2]	LDH	.D2	*B1++[2],B0	;*** x2 = x[j+i+2]
||[B2]	LDH	.D1	*A4++[2],A0	;*** x1 = x[j+i+1]
	; inner loop branch occurs here

  [A2]	B	.S2	OUTLOOP		; branch to outer loop
||	SUB	.L1	A4,A3,A4	; reset x pointer to x[j]
||	SUB	.L2	B4,B10,B4	; reset h pointer to h[0]
||	SUB	.S1	A9,A0,A9	; sum0 -= x0 * h0 (eliminate last sum0)

	SHR	.S1	A9,15,A9	; sum0 >> 15
||	SHR	.S2	B9,15,B9	; sum1 >> 15

	STH	.D1	A9,*A6++	; y[j] = sum0 >> 15

	STH	.D1	B9,*A6++	; y[j+1] = sum1 >> 15

	NOP	2			; branch delay slots
	; outer loop branch occurs here

	B	.S2	B3		; return

	LDW	.D2	*++B15,B10	; pop register

	NOP	4
