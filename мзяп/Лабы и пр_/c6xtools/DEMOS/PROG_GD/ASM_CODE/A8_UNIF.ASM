******************************************************************************/
*         Copyright (C) 1996-1997 Texas Instruments Incorporated
*                      All Rights Reserved
*         A8_UNIF HAND ASSEMBLY - Example 5-36
*         From Programmer's Guide
******************************************************************************

********* ASSEMBLY CODE: *******************
	.global _unrolled_if_then_asm
	.text
_unrolled_if_then_asm:
	MVK	.S2	16,B0		; set up loop counter

  	LDH	.D1	*A4++,A5	; a[i]
||[B0]	ADD	.D2	-1,B0,B0	; decrement counter

  	LDH	.D1	*A4++,B5	; a[i+1]
||[B0]	B	.S2	LOOP		; for LOOP
||[B0]	ADD	.D2	-1,B0,B0	; decrement counter
||	SHL	.S1	A6,1,A6		; maski+1 = maski << 1;
||	AND	.L1X	B4,A6,A2	; condi = codeword & maski

  [A2]	MVK	.S1	1,A2		; !(!(condi))
||	AND	.L2X	B4,A6,B2	; condi+1 = codeword & maski+1
||	ZERO	.L1	A7		; zero accumulator

  [B2]	MVK	.S2	1,B2		; !(!(condi+1))
||	CMPEQ	.L1X	B6,A2,A1	; (theta == !(!(condi)))
||	SHL	.S1	A6,1,A6		; maski = maski+1 << 1;
||	LDH	.D1	*A4++,A5	;* a[i]
||	ZERO	.L2	B7		; zero accumulator

LOOP:
  	CMPEQ	.L2	B6,B2,B1	; (theta == !(!(condi+1)))
||[B0]	ADD	.D2	-1,B0,B0	; decrement counter
||	LDH	.D1	*A4++,B5	;* a[i+1]
||[B0]	B	.S2	LOOP		;* for LOOP
||	SHL	.S1	A6,1,A6		;* maski+1 = maski << 1;
||	AND	.L1X	B4,A6,A2	;* condi = codeword & maski

  [A1]	ADD	.L1	A7,A5,A7	; sum += a[i]
||[!A1]	SUB	.D1	A7,A5,A7	; sum -= a[i]
||[A2]	MVK	.S1	1,A2		;* !(!(condi))
||	AND	.L2X	B4,A6,B2	;* condi+1 = codeword & maski+1

  [B1]	ADD	.L2	B7,B5,B7	; sum += a[i+1]
||[!B1]	SUB	.D2	B7,B5,B7	; sum -= a[i+1]
||[B2]	MVK	.S2	1,B2		;* !(!(condi+1))
||	CMPEQ	.L1X	B6,A2,A1	;* (theta == !(!(condi)))
||	SHL	.S1	A6,1,A6		;* maski = maski+1 << 1;
||	LDH	.D1	*A4++,A5	;** a[i]
	; Branch occurs here

	ADD	.L1X	A7,B7,A4	; move to return register

	B	.S2	B3
	NOP	5

********* END ASSEMBLY CODE ******************	
