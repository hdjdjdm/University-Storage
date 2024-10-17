/****************************************************************************/
/*          Copyright (C) 1996-1997 Texas Instruments Incorporated          */
/*                       All Rights Reserved                                */
/* C9_LIVE      - LIVE_TOO_LONG                                             */
/* To compile:  cl6x -qko3 c9_live.c live9.sa a9_live.asm -z -l lnk.cmd     */
/*                   -l rts6201.lib -o c9_live.out                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

short a[100] = { -2, 668, -10, 6019, 531, -3950, -275, 54, -1, -41,
                 -6, -536, 1, 20, -10, -7564, 1918, -1095, 268, -3,
                 56, -25, 1069, 0, -20, 61, -2380, -1, 60, 6845,
                 250, -49, -3038, -1001, -3, -12596, 39, -6, 0, -23386,
                 -22, -74, 25, -5, -3847, 7007, -1, 12, -103, 12,
                 5, -353, 7, -186, 504, -549, 4, 11, -1, -23,
                 668, -691, -7822, 125, -3929, -1, -2077, 3, 121, -1,
                 -6, 0, -4, 1020, 517, -992, -1021, -12, 7050, 2,
                 5829, -124, 17, 213, -158, -114, -53, -2516, -1, -224,
                 2709, 772, -7603, 148, -6, -88, 198, 438, -124, -62 };
 
short b[100] = { 2837, -77, 0, -4824, -1, 786, -737, -14, -935, -3,
                 0, 2, -22, -1, 1, 0, 240, -6768, -1, -6086,
                 74, -1, -22, -1386, 10, 1193, 121, -54, -568, 215,
                 -5206, 1, 0, -2, 711, 1686, 0, -1, -17, -28424,
                 -47, 76, -185, 191, -57, 29, -17, 662, -1196, -81,
                 25072, 1656, 6, -43, 19920, -839, 265, -9, -22, 192,
                 23728, 29276, 327, 232, 714, -1, -1, 0, 537, 15445,
                 6, -81, -100, -619, -10993, 1, -9642, 107, -1000, -911,
                 -1483, -20, -11547, 3, -1432, -2, 1, 76, -546, -14713,
                 -19, 1, -1, 31, 0, -3106, 2, 1204, -455, -127 }; 

short c = 10, d = 12, e = 15;
 
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
    printf("LIVE_TOO_LONG Assembly Clock Cycles:           %d\n",
            t_asm - t_stub);
    printf("LIVE_TOO_LONG Assembly Optimizer Clock Cycles: %d\n",
            t_sa - t_stub);
}

int live_long_stub(const short a[], const short b[], short c, short d, short e)
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
    *i      = live_long_stub(a, b, c, d, e);
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
    *i      = live_long_asm(a, b, c, d, e);
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
    *i      = live_long_sa(a, b, c, d, e);
    t_stop  = clock();
    return  t_stop - t_start;
}

/* Sample C code
int live_long_c(const short a[], const short b[], short c, short d, short e)
{
    int  i, sum0, sum1, sum, a0, a2, a3, b0, b2, b3;
    short a1, b1;

    sum0 = 0;
    sum1 = 0;
    for(i=0; i<100; i++)
    {
        a0 = a[i] * c;
        a1 = a0 >> 15;
        a2 = a1 * d;
        a3 = a2 + a0;
        sum0 += a3;
        b0 = b[i] * c;
        b1 = b0 >> 15;
        b2 = b1 * e;
        b3 = b2 + b0;
        sum1 += b3;
    }
    sum = sum0 + sum1;
    return(sum);
}
*/

