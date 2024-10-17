/*****************************************************************************/
/* setjmp.h   v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _SETJMP
#define _SETJMP

/****************************************************************************/
/* SAVE AND RESTORE CONTEXT AREA.                                           */
/****************************************************************************/
typedef int jmp_buf[13];

int  _setjmp(jmp_buf _env); 
void longjmp(jmp_buf _env, int _val);

#define setjmp(_x) _setjmp(_x)

#endif

