*****************************************************************************
*       Copyright (C) 1996-1997 Texas Instruments Incorporated
*                    All Rights Reserved
*       A10_FIR HAND ASSEMBLY - Example 5-45
*       From Programmer's Guide
*       FINITE IMPULE RESPONSE FILTER - PERFORMS 2 SAMPLES AT A TIME
*                                     - EVEN n >= 2
*****************************************************************************
******* ASSEMBLY CODE: *******************
	.global _fir_asm
	.text
_fir_asm:
	MVK	.S1	50,A2		; set up outer loop counter

	MVK	.S1	80,A3		; used to rst x pointer each outer loop
||	MVK	.S2	82,B6		; used to rst h pointer each outer loop

OUTLOOP:
	LDH	.D1	*A4++[2],A0	; x0 = x[j]
||	ADD	.L2X	A4,2,B5		; set up pointer to x[j+1]
||	ADD	.D2	B4,2,B4		; set up pointer to h[1]
||	ADD	.L1X	B4,0,A5		; set up pointer to h[0]
||	MVK	.S2	16,B2		; set up inner loop counter
||[A2]	SUB	.S1	A2,1,A2		; decrement outer loop counter

  	LDH	.D1	*A5++[2],A1	; h0 = h[i]
||	LDH	.D2	*B5++[2],B1	; x1 = x[j+i+1]
||	ZERO	.L1	A9		; zero out sum0
||	ZERO	.L2	B9		; zero out sum1

  	LDH	.D2	*B4++[2],B0	; h1 = h[i+1]
||	LDH	.D1	*A4++[2],A0	; x0 = x[j+i+2]

  	LDH	.D1	*A5++[2],A1	;* h0 = h[i]
||	LDH	.D2	*B5++[2],B1	;* x1 = x[j+i+1]

  [B2]	SUB	.S2	B2,1,B2		; decrement inner loop counter
||  	LDH	.D2	*B4++[2],B0	;* h1 = h[i+1]
||	LDH	.D1	*A4++[2],A0	;* x0 = x[j+i+2]

  [B2]	B	.S2	LOOP		; branch to inner loop
||	LDH	.D1	*A5++[2],A1	;** h0 = h[i]
||	LDH	.D2	*B5++[2],B1	;** x1 = x[j+i+1]

  	MPY	.M1	A0,A1,A7	; x0 * h0
||[B2]	SUB	.S2	B2,1,B2		;* decrement inner loop counter
||	LDH	.D2	*B4++[2],B0	;** h1 = h[i+1]
||	LDH	.D1	*A4++[2],A0	;** x0 = x[j+i+2]

  	MPY	.M2	B1,B0,B7	; x1 * h1
||	MPY	.M1X	B1,A1,A8	; x1 * h0
||[B2]	B	.S2	LOOP		;* branch to inner loop
||	LDH	.D1	*A5++[2],A1	;*** h0 = h[i]
||	LDH	.D2	*B5++[2],B1	;*** x1 = x[j+i+1]

  	MV		A7,A7		
||	MPY	.M2X	A0,B0,B8	; x0 * h1
||	MPY	.M1	A0,A1,A7	;* x0 * h0
||[B2]	SUB	.S2	B2,1,B2		;** decrement inner loop counter
||	LDH	.D2	*B4++[2],B0	;*** h1 = h[i+1]
||	LDH	.D1	*A4++[2],A0	;*** x0 = x[j+i+2]

LOOP:
  	ADD	.L2X	A8,B9,B9	; sum1 += x1 * h0
||	ADD	.L1	A7,A9,A9	; sum0 += x0 * h0
||	MPY	.M2	B1,B0,B7	;* x1 * h1
||	MPY	.M1X	B1,A1,A8	;* x1 * h0
||[B2]	B	.S2	LOOP		;** branch to inner loop
||	LDH	.D1	*A5++[2],A1	;**** h0 = h[i]
||	LDH	.D2	*B5++[2],B1	;**** x1 = x[j+i+1]

  	ADD	.L1X	B7,A9,A9	; sum0 += x1 * h1
||	ADD	.L2	B8,B9,B9	; sum1 += x0 * h1
||	MPY	.M2X	A0,B0,B8	;* x0 * h1
||	MPY	.M1	A0,A1,A7	;** x0 * h0
||[B2]	SUB	.S2	B2,1,B2		;*** decrement inner loop counter
||	LDH	.D2	*B4++[2],B0	;**** h1 = h[i+1]
||	LDH	.D1	*A4++[2],A0	;**** x0 = x[j+i+2]
	; inner loop branch occurs here

  [A2]	B	.S1	OUTLOOP		; branch to outer loop
||	SUB	.L1	A4,A3,A4	; reset x pointer to x[j]
||	SUB	.L2	B4,B6,B4	; reset h pointer to h[0]

	SHR	.S1	A9,15,A9	; sum0 >> 15
||	SHR	.S2	B9,15,B9	; sum1 >> 15

	STH	.D1	A9,*A6++	; y[j] = sum0 >> 15

	STH	.D1	B9,*A6++	; y[j+1] = sum1 >> 15

	NOP	2			; branch delay slots
	; outer loop branch occurs here

	B	.S2	B3		; return

	NOP	5
