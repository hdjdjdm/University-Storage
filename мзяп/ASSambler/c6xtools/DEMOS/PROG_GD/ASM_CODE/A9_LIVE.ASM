**************************************************************************
*               Copyright (C) 1996-1997 Texas Instruments Incorporated.
*                            All Rights Reserved
*               A9_LIVE HAND ASSEMBLY - Example 5-40
*               From Programmer's Guide
**************************************************************************

********* ASSEMBLY CODE: *******************
	.global _live_long_asm
	.text

_live_long_asm:

	LDH	.D1	*A4++,A0	; load ai from memory
||	LDH	.D2	*B4++,B0	; load bi from memory

	MVK	.S2	100,B2		; set up loop counter
||	STW	.D2	B10,*B15--	; push register

	LDH	.D1	*A4++,A0	;* load ai from memory
||	LDH	.D2	*B4++,B0	;* load bi from memory

	ZERO	.S1	A1		; zero out accumulator
||	ZERO	.S2	B1		; zero out accumulator

	LDH	.D1	*A4++,A0	;** load ai from memory
||	LDH	.D2	*B4++,B0	;** load bi from memory

   [B2]	SUB	.S2	B2,1,B2		; decrement loop counter

	MPY	.M1	A0,A6,A3	; a0 = ai * c
||	MPY	.M2X	B0,A6,B10	; b0 = bi * ci
||	LDH	.D1	*A4++,A0	;*** load ai from memory
||	LDH	.D2	*B4++,B0	;*** load bi from memory

   [B2]	SUB	.S2	B2,1,B2		; decrement loop counter
|| [B2]	B	.S1	LOOP		; branch to loop

	SHR	.S1	A3,15,A5	; a1 = a0 >> 15
||	SHR	.S2	B10,15,B5	; b1 = b0 >> 15
||	MPY	.M1	A0,A6,A3	;* a0 = ai * c
||	MPY	.M2X	B0,A6,B10	;* b0 = bi * ci
||	LDH	.D1	*A4++,A0	;**** load ai from memory
||	LDH	.D2	*B4++,B0	;**** load bi from memory

	MPY	.M1X	A5,B6,A7	; a2 = a1 * d
||	MV	.D1	A3,A2		; save a0 across iterations
||	MPY	.M2X	B5,A8,B7	; b2 = b1 * e
||	MV	.D2	B10,B8		; save b0 across iterations
|| [B2]	SUB	.S2	B2,1,B2		;* decrement loop counter
|| [B2]	B	.S1	LOOP		;* branch to loop

	SHR	.S1	A3,15,A5	;* a1 = a0 >> 15
||	SHR	.S2	B10,15,B5	;* b1 = b0 >> 15
||	MPY	.M1	A0,A6,A3	;** a0 = ai * c
||	MPY	.M2X	B0,A6,B10	;** b0 = bi * ci
||	LDH	.D1	*A4++,A0	;***** load ai from memory
||	LDH	.D2	*B4++,B0	;***** load bi from memory

LOOP:
	ADD	.L1	A7,A2,A9	;* a3 = a2 + a0
||	ADD	.L2	B7,B8,B9	;* b3 = b2 + b0
||	MPY	.M1X	A5,B6,A7	;* a2 = a1 * d
||	MV	.D1	A3,A2		;* save a0 across iterations
||	MPY	.M2X	B5,A8,B7	;* b2 = b1 * e
||	MV	.D2	B10,B8		;* save b0 across iterations
|| [B2]	SUB	.S2	B2,1,B2		;** decrement loop counter
|| [B2]	B	.S1	LOOP		;** branch to loop

	ADD	.L1	A1,A9,A1	; sum0 += a3
||	ADD	.L2	B1,B9,B1	; sum1 += b3
||	SHR	.S1	A3,15,A5	;** a1 = a0 >> 15
||	SHR	.S2	B10,15,B5	;** b1 = b0 >> 15
||	MPY	.M1	A0,A6,A3	;*** a0 = ai * c
||	MPY	.M2X	B0,A6,B10	;*** b0 = bi * ci
||	LDH	.D1	*A4++,A0	;****** load ai from memory
||	LDH	.D2	*B4++,B0	;****** load bi from memory
	; Branch occurs here

	ADD	.L1X	A1,B1,A4	; sum = sum0 + sum1
||	B	.S2	B3
||	LDW	.D2	*++B15,B10	; pop register

	NOP	5

********* END ASSEMBLY CODE ******************	
