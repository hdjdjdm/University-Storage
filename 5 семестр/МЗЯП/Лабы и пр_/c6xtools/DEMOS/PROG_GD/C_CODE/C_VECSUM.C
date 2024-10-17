/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/*                                                                          */
/* C_VECSUM.C - Example from Programmer's Guide on optimizing C code.       */
/*                                                                          */
/* cl6x -qko3 c_vecsum.c -z -llnk.cmd -lrts6201.lib -o c_vecsum.out         */
/* load6x -q -k c_vecsum.out                                                */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

void vecsum1(short *sum, short *in1, short *in2, unsigned int N);
void vecsum2(short *sum, const short *in1, const short *in2, unsigned int N);
void vecsum3(short *sum, const short *in1, const short *in2, unsigned int N);
void vecsum4(short *sum, const short *in1, const short *in2, unsigned int N);
void vecsum5(short *sum, const short *in1, const short *in2, unsigned int N);
void vecsum6(int *sum, const int *in1, const int *in2, unsigned int N);

unsigned int n = 44;

short a[] = {
0x08D6, 0xF380, 0xF380, 0x0000, 0xF380, 0x0C80,
0x08D6, 0xF380, 0x0C80, 0x0C80, 0xF380, 0xF380,
0xF729, 0x0C80, 0x0C80, 0x0000, 0xF380, 0xF380,
0xF729, 0x0C80, 0xF380, 0xF380, 0x0C80, 0x0C80,
0x08D6, 0xF380, 0xF380, 0x0000, 0xF380, 0x0C80,
0x08D6, 0xF380, 0x0C80, 0x0C80, 0xF380, 0xF380,
0xF729, 0x0C80, 0x0C80, 0x0000, 0xF380, 0xF380,
0xF729, 0x0C80 };

short b[] = {
0x08D6, 0xF380, 0xF380, 0x0000, 0xF380, 0x0C80,
0x08D6, 0xF380, 0x0C80, 0x0C80, 0xF380, 0xF380,
0xF729, 0x0C80, 0x0C80, 0x0000, 0xF380, 0xF380,
0xF729, 0x0C80, 0xF380, 0xF380, 0x0C80, 0x0C80,
0x08D6, 0xF380, 0xF380, 0x0000, 0x0C80, 0x0C80,
0x08D6, 0xF380, 0x0C80, 0x0C80, 0xF380, 0xF380,
0xF729, 0x0C80, 0x0C80, 0x0000, 0xF380, 0xF380,
0xF729, 0x0C80 };

short c1[44];
short c[44];

/****************************************************************************/
/* TOP LEVEL DRIVER FOR THE TEST.                                           */
/****************************************************************************/
int main()
{
    int i;
    clock_t t_overhead, t_start, t_stop, t_vecsum;
 
    printf("BEGIN\n");

    /************************************************************************/
    /* COMPUTE THE OVERHEAD OF CALLING CLOCK TWICE TO GET TIMING INFO.      */
    /************************************************************************/
    t_start    = clock();
    t_stop     = clock();
    t_overhead = t_stop - t_start;

    /************************************************************************/
    /* TIME VECSUM1.                                                        */
    /************************************************************************/
    t_start = clock();
    vecsum1(c1, a, b, n);
    t_stop = clock();
    printf("VECSUM1: %d cycles\n", t_stop - t_start - t_overhead);

    /************************************************************************/
    /* TIME VECSUM2.                                                        */
    /************************************************************************/
    t_start = clock();
    vecsum2(c, a, b, n);
    t_stop = clock();
    printf("VECSUM2: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(c1, c, sizeof(c)) != 0) printf("Result failure vecsum2()\n");

    /************************************************************************/
    /* TIME VECSUM3.                                                        */
    /************************************************************************/
    t_start = clock();
    vecsum3(c, a, b, n);
    t_stop = clock();
    printf("VECSUM3: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(c1, c, sizeof(c)) != 0) printf("Result failure vecsum3()\n");

    /************************************************************************/
    /* TIME VECSUM4.                                                        */
    /************************************************************************/
    t_start = clock();
    vecsum4(c, a, b, n);
    t_stop = clock();
    printf("VECSUM4: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(c1, c, sizeof(c)) != 0) printf("Result failure vecsum4()\n");

    /************************************************************************/
    /* TIME VECSUM5.                                                        */
    /************************************************************************/
    t_start = clock();
    vecsum5(c, a, b, n);
    t_stop = clock();
    printf("VECSUM5: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(c1, c, sizeof(c)) != 0) printf("Result failure vecsum5()\n");

    /************************************************************************/
    /* TIME VECSUM6.                                                        */
    /************************************************************************/
    t_start = clock();
    vecsum6((int*)c, (int*)a, (int*)b, n);
    t_stop = clock();
    printf("VECSUM6: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(c1, c, sizeof(c)) != 0) printf("Result failure vecsum6()\n");

    printf("END\n");
}

/****************************************************************************/
/* BASIC VECSUM                                                             */
/****************************************************************************/
void vecsum1(short *sum, short *in1, short *in2, unsigned int N)
{
    int i;
 
    for (i = 0; i < N; i++)
        sum[i] = in1[i] + in2[i];
}

/****************************************************************************/
/* VECSUM WITH CONST KEYWORDS                                               */
/****************************************************************************/
void vecsum2(short *sum, const short *in1, const short *in2, unsigned int N)
{
    int i;
 
    for (i = 0; i < N; i++)
        sum[i] = in1[i] + in2[i];
}

/****************************************************************************/
/* VECSUM WITH CONST KEYWORDS AND _NASSERT()                                */
/****************************************************************************/
void vecsum3(short *sum, const short *in1, const short *in2, unsigned int N)
{
    int i;
 
    _nassert(N >= 20);
 
    for (i = 0; i < N; i++)
        sum[i] = in1[i] + in2[i];
}

/****************************************************************************/
/* VECSUM WITH CONST KEYWORDS , _NASSERT(), WORD READS                      */
/****************************************************************************/
void vecsum4(short *sum, const short *in1, const short *in2, unsigned int N)
{
    int i;
 
    const int *i_in1 = (const int *)in1;
    const int *i_in2 = (const int *)in2;
          int *i_sum = (int *)sum;
 
    _nassert(N >= 20);
 
    for (i = 0; i < (N >> 1); i++)
        i_sum[i] = _add2(i_in1[i], i_in2[i]);
}

/****************************************************************************/
/* VECSUM WITH CONST KEYWORDS , _NASSERT(), WORD READS, GENERIC VERSION     */
/****************************************************************************/
void vecsum5(short *sum, const short *in1, const short *in2, unsigned int N)
{
    int i;
 
    _nassert(N >= 20);
 
    if (((int)sum | (int)in2 | (int)in1) & 0x2)
    {
        for (i = 0; i < N; i++)
            sum[i] = in1[i] + in2[i];
    }
    else
    {
        const int *i_in1 = (const int *)in1;
        const int *i_in2 = (const int *)in2;
              int *i_sum = (int *)sum;
 
        for (i = 0; i < (N >> 1); i++)
            i_sum[i] = _add2(i_in1[i], i_in2[i]);
 
        if (N & 0x1) sum[i] = in1[i] + in2[i];
    }
}

/****************************************************************************/
/* VECSUM WITH CONST KEYWORDS , _NASSERT(), WORD READS, AND UNROLLED        */
/****************************************************************************/
void vecsum6(int *sum, const int *in1, const int *in2, unsigned int N)
{
    int i;
    int sz = N >> 2;
 
    _nassert(N >= 20);
 
    for (i = 0; i < sz; i += 2)
    {
        sum[i]   = _add2(in1[i]  , in2[i]);
        sum[i+1] = _add2(in1[i+1], in2[i+1]);
    }
}
