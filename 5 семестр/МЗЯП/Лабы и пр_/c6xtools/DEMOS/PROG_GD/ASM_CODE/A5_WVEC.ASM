******************************************************************************/
*      Copyright (C) 1996-1997 Texas Instruments Incorporated
*                   All Rights Reserved
*	A5_WVEC HAND ASSEMBLY - Example 5-21
*       From Programmer's Guide
******************************************************************************

********* ASSEMBLY CODE: *******************

	.global _w_vec_asm
	.text
_w_vec_asm:
	STW	.D2	B10,*B15--	; push B10

START:
  	LDW	.D1	*A4++,A2	; ai & ai+1

	ADD	.L2X	A6,2,B0		; set pointer to ci+1

  	LDW	.D2	*B4++,B2	; bi & bi+1
||	LDW	.D1	*A4++,A2	;* ai & ai+1

	MVK	.S2	-1,B10		; set to all 1s

  	LDW	.D2	*B4++,B2	;* bi & bi+1
||	LDW	.D1	*A4++,A2	;** ai & ai+1
||	MVK	.S1	49,A1		; set up loop counter
||	MVKH	.S2	0,B10		; clear upper 16 bits

  	MPY	.M1X	A2,B6,A5	; m * ai
||[A1]	SUB	.L1	A1,1,A1		; decrement loop counter

  	MPYHL	.M2X	A2,B6,B5	; m * ai+1
||[A1]	B	.S1	LOOP		; branch to loop
||	LDW	.D2	*B4++,B2	;** bi & bi+1
||	LDW	.D1	*A4++,A2	;*** ai & ai+1

  	SHR	.S1	A5,15,A7	; (m * ai) >> 15
||	AND	.L2	B2,B10,B8	; bi
||	MPY	.M1X	A2,B6,A5	;* m * ai
||[A1]	SUB	.L1	A1,1,A1		; decrement loop counter

  	SHR	.S2	B2,16,B1	; bi+1	
||	ADD	.L1X	A7,B8,A9	; ci = (m * ai) >> 15 + bi
||	MPYHL	.M2X	A2,B6,B5	;* m * ai+1
||[A1]	B	.S1	LOOP		;* branch to loop
||	LDW	.D2	*B4++,B2	;*** bi & bi+1
||	LDW	.D1	*A4++,A2	;**** ai & ai+1

  	SHR	.S2	B5,15,B7	; (m * ai+1) >> 15
||	STH	.D1	A9,*A6++[2]	; store ci
||	SHR	.S1	A5,15,A7	;* (m * ai) >> 15
||[A1]	SUB	.L1	A1,1,A1		; decrement loop counter
||	AND	.L2	B2,B10,B8	;* bi
||	MPY	.M1X	A2,B6,A5	;** m * ai

LOOP:
  	ADD	.L2	B7,B1,B9	; ci+1 = (m * ai+1) >> 15 + bi+1
||	SHR	.S2	B2,16,B1	;* bi+1	
||	ADD	.L1X	A7,B8,A9	;* ci = (m * ai) >> 15 + bi
||	MPYHL	.M2X	A2,B6,B5	;** m * ai+1
||[A1]	B	.S1	LOOP		;** branch to loop
||	LDW	.D2	*B4++,B2	;**** bi & bi+1
||	LDW	.D1	*A4++,A2	;***** ai & ai+1

  	STH	.D2	B9,*B0++[2]	; store ci+1
||[A1]	SUB	.L1	A1,1,A1		; decrement loop counter
||	SHR	.S2	B5,15,B7	;* (m * ai+1) >> 15
||	STH	.D1	A9,*A6++[2]	;* store ci
||	SHR	.S1	A5,15,A7	;** (m * ai) >> 15
||	AND	.L2	B2,B10,B8	;** bi
||	MPY	.M1X	A2,B6,A5	;*** m * ai
	; Branch occurs here
   
  	ADD	.L2	B7,B1,B9	; ci+1 = (m * ai+1) >> 15 + bi+1

END:
  	STH	.D2	B9,*B0		; store ci+1
||	B	.S2	B3

	LDW	.D2	*++B15,B10	; pop B10

	NOP	4

********* END ASSEMBLY CODE ******************	
