/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/*                                                                          */
/* C_DOTP.C  -  Dot product example.                                        */
/*              Example from Programmer's Guide on optimizing C code.       */
/*                                                                          */
/* cl6x -qko3 c_dotp.c -z -llnk.cmd -lrts6201.lib -o c_dotp.out             */
/* load6x -q -k c_dotp.out                                                  */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

int dotprod1(const short *a, const short *b, unsigned int N);
int dotprod2(const int *a, const int *b, unsigned int N);

short a[] = { 0x011D, 0xFFFF, 0x007A, 0x018C, 0xFFAD, 0xF515, 0x0369, 0x0017,
              0x03DA, 0xFAC0, 0x000C, 0xEADD, 0xFFAE, 0x0A70, 0xFEFF, 0xFFFE,
              0x13FE, 0xFFF9, 0xFFEB, 0x0000, 0xFA82, 0xFFFF, 0x0005, 0x0070,
              0x010D, 0xFEE3, 0xF9E7, 0x00A7, 0x13D1, 0xDB90, 0xFFFF, 0xFFFE,
              0xFF00, 0x030F, 0x00FE, 0xFFF8, 0xFFFD, 0xFFFF, 0xFFF7, 0x0010};

short b[] = { 0x0E8F, 0x002F, 0x9C74, 0xFFFF, 0xFF0B, 0xFF78, 0xD09C,
              0x0188, 0x0001, 0x07BF, 0xFD64, 0x00C7, 0x0000, 0x0452,
              0xFF8E, 0x0001, 0xFFFE, 0xFF3C, 0x0007, 0xFFF8, 0x0233,
              0xF72B, 0x0004, 0x0000, 0xFF6B, 0x0370, 0x017D, 0xFD07,
              0x0000, 0xFFCE, 0x0000, 0x6504, 0xFFFD, 0xFFFF, 0xFFFB,
              0x01AA, 0xFF3E, 0x04AA, 0x00D4, 0xFF95 };

int ret1, ret2;

/****************************************************************************/
/* TOP LEVEL DRIVER FOR THE TEST.                                           */
/****************************************************************************/
int main()
{
    int i;
    clock_t t_overhead, t_start, t_stop;

    printf("BEGIN\n");
 
    /************************************************************************/
    /* COMPUTE THE OVERHEAD OF CALLING CLOCK TWICE TO GET TIMING INFO.      */
    /************************************************************************/
    t_start    = clock();
    t_stop     = clock();
    t_overhead = t_stop - t_start;

    /************************************************************************/
    /* TIME DOTPROD1                                                        */
    /************************************************************************/
    t_start = clock();
    ret1 = dotprod1(a, b, 40);
    t_stop = clock();
    printf("DOTPROD1: %d cycles\n", t_stop - t_start - t_overhead);

    /************************************************************************/
    /* TIME DOTPROD2                                                        */
    /************************************************************************/
    t_start = clock();
    ret2 = dotprod2((int*)a, (int*)b, 40);
    t_stop = clock();
    printf("DOTPROD2: %d cycles\n", t_stop - t_start - t_overhead);
    if (ret1 != ret2) printf("Result failure dotprod2()\n");

    printf("END\n");
}

/****************************************************************************/
/* DOTPROD1 - BASIC FORM.                                                   */
/****************************************************************************/
int dotprod1(const short *a, const short *b, unsigned int N)
{
    int i, sum = 0;

    for (i = 0; i < N; i++)
        sum += a[i] * b[i];

    return sum;
}

/****************************************************************************/
/* DOTPROD2 - USING INTRINSICS.                                             */
/****************************************************************************/
int dotprod2(const int *a, const int *b, unsigned int N)
{
    int i, sum1 = 0, sum2 = 0;
 
    for (i = 0; i < (N >> 1); i++)
    {
        sum1 += _mpy (a[i], b[i]);
        sum2 += _mpyh(a[i], b[i]);
    }
 
    return sum1 + sum2;
}
