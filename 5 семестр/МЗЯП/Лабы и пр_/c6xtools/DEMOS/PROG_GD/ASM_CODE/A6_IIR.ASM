******************************************************************************/
*		Copyright (C) 1996-1997 Texas Instruments Incorporated
*                           All Rights Reserved
*	        A6_IIR HAND ASSEMBLY - Example 5-27
*               From Programmer's Guide
********************************************************************

********* ASSEMBLY CODE: *******************

	.global _iir_asm
	.text
_iir_asm:
START:
  	LDH	.D1	*A4++,A2	; xi

  	LDH	.D1	*A4,A3		; xi+1

	LDH	.D2	*B4++,B2	; load y[0] outside of loop

	MVK	.S1	100,A1		; set up loop counter

  	LDH	.D1	*A4++,A2	;* xi

  [A1]	SUB	.L1	A1,1,A1		; decrement loop counter
||  	MPY	.M1	A6,A2,A5	; c1 * xi
||	LDH	.D1	*A4,A3		;* xi+1

  	MPY	.M1X	B6,A3,A7	; c2 * xi+1
||[A1]	B	.S1	LOOP		; branch to loop

  	MPY	.M2X	A8,B2,B7	; c3 * yi

LOOP:
  	ADD	.L1	A5,A7,A9	; c1 * xi + c2 * xi+1
||  	LDH	.D1	*A4++,A2	;** xi

	ADD	.L2X	B7,A9,B5	; c1 * xi + c2 * xi+1 + c3 * yi
||[A1]	SUB	.L1	A1,1,A1		;* decrement loop counter
||	MPY	.M1	A6,A2,A5	;* c1 * xi
||	LDH	.D1	*A4,A3		;** xi+1

  	SHR	.S2	B5,15,B2	; yi+1
||	MPY	.M1X	B6,A3,A7	;* c2 * xi+1
||[A1]	B	.S1	LOOP		;* branch to loop

  	STH	.D2	B2,*B4++	; store yi+1
||	MPY	.M2X	A8,B2,B7	;* c3 * yi
	; Branch occurs here

	B	.S2	B3

	NOP	5

********* END ASSEMBLY CODE ******************	
