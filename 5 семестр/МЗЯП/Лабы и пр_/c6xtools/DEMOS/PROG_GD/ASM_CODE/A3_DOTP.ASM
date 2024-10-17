***********************************************************************
*         Copyright (C) 1996-1997 Texas Instruments Incorporated
*                      All Rights Reserved
*         A3_DOTP HAND ASSEMBLY - Example 5-8
*         From Programmer's Guide
***********************************************************************
********* ASSEMBLY CODE: *******************
	.global _dotp_asm
	.text

DOT_PRODUCT:

_dotp_asm:
	MVK	.S1	50,A1		; set up loop counter
||	ZERO	.L1	A7		; zero out sum0 accumulator
||	ZERO	.L2	B7		; zero out sum1 accumulator

LOOP:
	LDW	.D1	*A4++,A2	; load ai & ai+1 from memory
||	LDW	.D2	*B4++,B2	; load bi & bi+1 from memory

	SUB	.S1	A1,1,A1		; decrement loop counter

  [A1]	B	.S1	LOOP		; branch to loop

	NOP	2

	MPY	.M1X	A2,B2,A6	; ai * bi
||	MPYH	.M2X	A2,B2,B6	; ai+1 * bi+1

	NOP

	ADD	.L1	A6,A7,A7	; sum0+= (ai * bi)
||	ADD	.L2	B6,B7,B7	; sum1+= (ai+1 * bi+1)
	; Branch occurs here

	ADD	.L1X	A7,B7,A4	; sum = sum0 + sum1
||	B	.S2	B3

	NOP	5

********* END ASSEMBLY CODE ******************	
