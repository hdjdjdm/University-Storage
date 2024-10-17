******************************************************************************/
*		Copyright (C) 1996-1997 Texas Instruments Incorporated
*                           All Rights Reserved
*              A7_IF HAND ASSEMBLY - Example 5-31
*              From Programmer's Guide
******************************************************************************

********* ASSEMBLY CODE: *******************
	.global _if_then_asm
	.text
_if_then_asm:
	MVK	.S2	32,B0		; set up loop counter

  [B0]	ADD	.L2	-1,B0,B0	; decrement counter

  [B0]	ADD	.L2	-1,B0,B0	; decrement counter
||[B0]	B	.S1	LOOP		; for LOOP
||	LDH	.D1	*A4++,A5	; a[i]

  	SHL	.S1	A6,1,A6		; mask = mask << 1;
||	AND	.S2X	B4,A6,B2	; cond = codeword & mask

  [B2]	MVK	.S2	1,B2		; !(!(cond))
||[B0]	ADD	.L2	-1,B0,B0	; decrement counter
||[B0]	B	.S1	LOOP		;* for LOOP
||	LDH	.D1	*A4++,A5	;* a[i]

  	CMPEQ	.L2	B6,B2,B1	; (theta == !(!(cond)))
||	SHL	.S1	A6,1,A6		;* mask = mask << 1;
||	AND	.S2X	B4,A6,B2	;* cond = codeword & mask
||	ZERO	.L1	A7		; zero out accumulator

LOOP:
  [B0]	ADD	.L2	-1,B0,B0	; decrement counter
||[B2]	MVK	.S2	1,B2		;* !(!(cond))
||[B0]	B	.S1	LOOP		;** for LOOP
||	LDH	.D1	*A4++,A5	;** a[i]

  [B1]	ADD	.L1	A7,A5,A7	; sum += a[i]
||[!B1]	SUB	.D1	A7,A5,A7	; sum -= a[i]
||	CMPEQ	.L2	B6,B2,B1	;* (theta == !(!(cond)))
||	SHL	.S1	A6,1,A6		;** mask = mask << 1;
||	AND	.S2X	B4,A6,B2	;** cond = codeword & mask
	; Branch occurs here

	MV	.L1	A7,A4		; move to return register

	B	.S2	B3
	NOP	5

********* END ASSEMBLY CODE ******************	
