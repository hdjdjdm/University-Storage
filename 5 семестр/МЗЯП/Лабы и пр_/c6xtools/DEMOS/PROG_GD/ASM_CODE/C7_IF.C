/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/* C7_IF        - IF_THEN                                                   */
/* To compile:  cl6x -qko3 c7_if.c if7.sa a7_if.asm -z -l lnk.cmd           */
/*                   -l rts6201.lib -o c7_if.out                            */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

short x[32] = {  5140,    -1,  -12,  7666,    4, -221, -16,  -128,
                -6513, -1776, 7317,  3851, -572,  -70,  -1,  7753,
                 -897,   -23,  -14,    -1, -103,  214,  31,  7782,
                   39,     3,   -2, -1643,   -1,    0,  -3, -8027 };

short th = 0;
int code = 32, msk = 1; 
int ret_stub, ret_asm, ret_sa;

clock_t time_stub (int *i);
clock_t time_asm  (int *i);
clock_t time_sa   (int *i);

/****************************************************************************/
/* TOP LEVEL DRIVER FOR THE TEST.                                           */
/****************************************************************************/
int main()
{
    int i;
    clock_t t_overhead, t_start, t_stop, t_stub, t_asm, t_sa;
 
    /************************************************************************/
    /* COMPUTE THE OVERHEAD OF CALLING CLOCK TWICE TO GET TIMING INFO.      */
    /************************************************************************/
    t_start    = clock();
    t_stop     = clock();
    t_overhead = t_stop - t_start;

    /************************************************************************/
    /* CALL THE INDIVIDIUAL TIMING ROUTINES.                                */
    /************************************************************************/
    t_stub    = time_stub(&ret_stub) - t_overhead;
    t_asm     = time_asm(&ret_asm)   - t_overhead;
    t_sa      = time_sa(&ret_sa)     - t_overhead;
    
    /************************************************************************/
    /* PRINT TIMING RESULTS                                                 */ 
    /************************************************************************/ 
    printf("IF_THEN Assembly Clock Cycles:           %d\n", t_asm - t_stub);
    printf("IF_THEN Assembly Optimizer Clock Cycles: %d\n", t_sa  - t_stub);
}

int if_then_stub(const short a[], int codeword, int mask, short theta)
{
    int i;
  
    asm("* comment to defeat inlining");
    return(i);
}

/****************************************************************************/
/* COMPUTE THE ELAPSED TIME OF THE STUB ROUTINE                             */
/****************************************************************************/
clock_t time_stub(int *i)
{
    clock_t t_start, t_stop;

    t_start = clock();
    *i      = if_then_stub(x, code, msk, th);
    t_stop  = clock();
    return  t_stop - t_start;
}

/****************************************************************************/
/* COMPUTE THE ELAPSED TIME OF THE HAND CODED ASSEMBLY ROUTINE              */
/****************************************************************************/
clock_t time_asm(int *i)
{
    clock_t t_start, t_stop;

    t_start = clock();
    *i      = if_then_asm(x, code, msk, th);
    t_stop  = clock();
    return  t_stop - t_start;
}

/****************************************************************************/
/* COMPUTE THE ELAPSED TIME OF THE ASSEMBLY OPTIMIZER ROUTINE               */
/****************************************************************************/
clock_t time_sa(int *i)
{
    clock_t t_start, t_stop;

    t_start = clock();
    *i      = if_then_sa(x, code, msk, th);
    t_stop  = clock();
    return  t_stop - t_start;
}

/*Sample C code
int if_then(const short a[], int codeword, int mask, short theta)
{
    int i,sum, cond;

    sum = 0;
    for (i = 0; i < 32; i++)
    {
        cond = codeword & mask;
        if (theta  ==  !(!(cond)))
            sum += a[i];
        else
            sum -= a[i];
        mask = mask << 1;
    }
    return(sum);
}
*/
