/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/* C5_WVEC      - WEIGHTED VECTOR SUM                                       */
/* To compile:  cl6x -qko3 c5_wvec.c wvec5.sa a5_wvec.asm -z -l lnk.cmd     */
/*                   -l rts6201.lib -o c5_wvec.out                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

int m = 10000;
short c[100];

short a[100] = { 5836, -1, 1672, -5683, -41, 114, -817, 30, 1, 317,
                 14, -2, -6981, 326, 9234, -403, -7796, 1260, -8337, -8,
                 1037, -11, -119, 416, -6, -1, -45, -179, 646, -217,
                 0, -2273, -4, -57, 2581, 162, -500, -2, 4644, -340,
                 -29, -796, -12, 12, 117, 17, -31, 289, -6, 9,
                 55, -13954, 1320, -1, -1, -8006, 3, -1, 31427, -10,
                 -3220, 0, 620, 127, 0, 2, -14905, -2, 213, -1, 
                 7539, -1, 61, 0, 78, 5773, -1, -1, 1, 54,
                 1334, 0, 6, 103, -376, 6315, -35, 2, -30, -33,
                 6315, 465, 7273, 480, 100, -1, -1, 1, -77, 0 }; 
 
short b[100] = { -715, -153, 14, -4, -47, 2178, 6, -1, 3, 2018, 
                 388, 0, 1, 0, 36, -11, -141, 22, -1719, 2746,
                 -9116, -3668, 61, -6, -487, -46, -1, -4, -39, 588,
                 21, -13, -6, 63, -1, -324, -19, -12635, 12, -171,
                 141, -7417, 2, 0, 0, 3, -40, 14998, -4, 847, 
                 63, -12016, 3, 1887, 1, -5378, -331, -3, 12, -15855,
                 -1, -1915, -96, -284, 1, 73, 29, 61, 230, 3387,
                 -2, -113, -16, -20, 1867, -1620, 1668, 114, -300, -1,
                 118, -1722, -1618, -318, -2, 3935, 408, 0, 2703, -142,
                 650, 0, -89, -2, -6, 2783, 56, 24, 5, -2 };
 
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
    printf("WEIGHTED_VEC_SUM Assembly Clock Cycles:           %d\n",
            t_asm - t_stub);
    printf("WEIGHTED_VEC_SUM Assembly Optimizer Clock Cycles: %d\n",
            t_sa - t_stub);
}

int w_vec_stub(const short a[], const short b[], short c[], short m)
{
    asm("* comment to defeat inlining");
}

/****************************************************************************/
/* COMPUTE THE ELAPSED TIME OF THE STUB ROUTINE                             */
/****************************************************************************/
clock_t time_stub(int *i)
{
    clock_t t_start, t_stop;

    t_start = clock();
    *i      = w_vec_stub(a, b, c, m);
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
    *i      = w_vec_asm(a, b, c, m);
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
    *i      = w_vec_sa(a, b, c, m);
    t_stop  = clock();
    return  t_stop - t_start;
}

/*Sample C code
void w_vec_c(const short a[], const short b[], short c[], short m)
{
    int i;

    for (i=0; i<100; i++) 
    {
        c[i] = ((m * a[i]) >> 15) + b[i];
    }
}
*/
