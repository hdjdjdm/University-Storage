/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/* C6_IIR       - IIR FILTER                                                */
/* To compile:  cl6x -qko3 c6_iir.c iir6.sa a6_iir.asm -z -l lnk.cmd        */
/*                   -l rts6201.lib -o c6_iir.out                           */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

short a[100] = {5836, -1, 1672, -5683, -41, 114, -817, 30, 1, 317,
                  14, -2, -6981,  326, 9234, -403, -7796, 1260, -8337, -8,
                1037, -11, -119, 416, -6, -1, -45, -179, 646, -217,
                   0, -2273, -4, -57, 2581, 162, -500, -2, 4644, -340,
                 -29, -796, -12, 12, 117, 17, -31, 289, -6, 9,
                  55, -13954, 1320, -1, -1, -8006, 3, -1, 31427, -10,
                3220, 0, 620, 127, 0, 2, -14905, -2, 213, -1, 
                7539, -1, 61, 0, 78, 5773, -1, -1, 1, 54,
                1334, 0, 6, 103, -376, 6315, -35, 2, -30, -33,
                6315, 465, 7273, 480, 100, -1, -1, 1, -77, 0 }; 
 
short b[100], m1, m2, m3;

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
    printf("IIR Assembly Clock Cycles:           %d\n", t_asm - t_stub);
    printf("IIR Assembly Optimizer Clock Cycles: %d\n", t_sa  - t_stub);
}

int iir_stub(const short x[], short y[], short c1, short c2, short c3)
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
    *i      = iir_stub(a, b, m1, m2, m3);
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
    *i      = iir_asm(a, b, m1, m2, m3);
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
    *i      = iir_sa(a, b, m1, m2, m3);
    t_stop  = clock();
    return  t_stop - t_start;
}

/* Sample C code
void iir_c(const short x[], short y[], short c1, short c2, short c3)
{
    int i;

    for (i = 0; i < 100; i++) 
        y[i+1] = (c1 * x[i] + c2 * x[i+1] + c3 * y[i]) >> 15;
}
*/
