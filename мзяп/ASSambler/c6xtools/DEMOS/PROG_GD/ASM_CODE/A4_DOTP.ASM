****************************************************************************
*         Copyright (C) 1996-1997 Texas Instruments Incorporated
*                      All Rights Reserved
*         A4_DOTP HAND ASSEMBLY - Example 5-13
*         From Programmer's Guide
****************************************************************************
********* ASSEMBLY CODE: *******************
	.global _dotp_asm
	.text

_dotp_asm:
	MVK	.S1	57,A1		; set up loop counter

  [A1]	ADD	.S1	-1,A1,A1	; decrement loop counter
||	ZERO	.L1	A7		; zero out sum0 accumulator
||	ZERO	.L2	B7		; zero out sum1 accumulator

  [A1]	ADD	.S1	-1,A1,A1	;* decrement loop counter
||[A1]	B	.S2	LOOP		; branch to loop
||	ZERO	.L1	A6		; zero out mpy result
||	ZERO	.L2	B6		; zero out mpy result

  [A1]	ADD	.S1	-1,A1,A1	;** decrement loop counter
||[A1]	B	.S2	LOOP		;* branch to loop
||	ZERO	.L1	A2		; zero out ldw result
||	ZERO	.L2	B2		; zero out ldw result

  [A1]	ADD	.S1	-1,A1,A1	;*** decrement loop counter
||[A1]	B	.S2	LOOP		;** branch to loop

  [A1]	ADD	.S1	-1,A1,A1	;**** decrement loop counter
||[A1]	B	.S2	LOOP		;*** branch to loop

  [A1]	ADD	.S1	-1,A1,A1	;***** decrement loop counter
||[A1]	B	.S2	LOOP		;**** branch to loop

LOOP:
  	ADD	.L1	A6,A7,A7	; sum0 += (ai * bi)
||	ADD	.L2	B6,B7,B7	; sum1 += (ai+1 * bi+1)
||	MPY	.M1X	A2,B2,A6	;** ai * bi
||	MPYH	.M2X	A2,B2,B6	;** ai+1 * bi+1
||[A1]	ADD	.S1	-1,A1,A1	;****** decrement loop counter
||[A1]	B	.S2	LOOP		;***** branch to loop
||	LDW	.D1	*A4++,A2	;******* load ai & ai+1 from memory
||	LDW	.D2	*B4++,B2	;******* load bi & bi+1 from memory

	ADD	.L1X	A7,B7,A4	; sum = sum0 + sum1
||	B	.S2	B3

	NOP	5

********* END ASSEMBLY CODE ******************	
