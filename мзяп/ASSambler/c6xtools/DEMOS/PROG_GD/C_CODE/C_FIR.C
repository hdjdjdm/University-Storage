/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/*                                                                          */
/* C_FIR.C - Example from Programmer's Guide on optimizing C code.          */
/*                                                                          */
/* cl6x -qko3 c_fir.c -z -llnk.cmd -lrts6201.lib -o c_fir.out               */
/* load6x -q -k c_fir.out                                                   */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

void fir1(const short x[], const short h[], short y[], int n, int m, int s);
void fir2(const int x[], const int h[], short y[], int n, int m, int s);

#define N  32
#define M  32
#define S  24

short y1[] =    { 0x0000, 0x0018, 0x8B84, 0xCD4C, 0x9713, 0x5719, 0x3E75, 
                  0x9ADB, 0xFD0A, 0x173C, 0xF544, 0x8C8D, 0x8B14, 0x354E, 
                  0xBF18, 0xC57C, 0x4D81, 0x239D, 0x85C6, 0xE58C, 0xEB0A, 
                  0x8D04, 0x8E4E, 0x86EF, 0x2956, 0xDC6C, 0xFB5D, 0xBEA3, 
                  0x6678, 0xB548, 0x4ACA, 0xA2F0 };

short y2[] =    { 0x0000, 0x0018, 0x8B84, 0xCD4C, 0x9713, 0x5719, 0x3E75, 
                  0x9ADB, 0xFD0A, 0x173C, 0xF544, 0x8C8D, 0x8B14, 0x354E, 
                  0xBF18, 0xC57C, 0x4D81, 0x239D, 0x85C6, 0xE58C, 0xEB0A, 
                  0x8D04, 0x8E4E, 0x86EF, 0x2956, 0xDC6C, 0xFB5D, 0xBEA3, 
                  0x6678, 0xB548, 0x4ACA, 0xA2F0 };

short x[] = { 0x1F6D, 0x7916, 0xD41B, 0xC0EC, 0x6BA0, 0xC5E3, 0x5100, 
              0xA2F9, 0x7E67, 0xF2C6, 0x51D5, 0x5044, 0x2986, 0x9461,
              0xC322, 0xCC46, 0x56A9, 0xFC65, 0x701C, 0x9645, 0x8EEC, 
              0xB80D, 0x7E24, 0x27D2, 0x7555, 0x0FA0, 0xF045, 0x784A,
              0x4B56, 0x88F2, 0x22B8, 0x7B57, 0x6B4E, 0x62E1, 0x5061, 
              0x9F6E, 0xCD07, 0x1CDA, 0x0E51, 0x4E50, 0x8638, 0xED54,
              0xCF45, 0x708C, 0x4402, 0x4A51, 0x6023, 0xE7FA, 0xD574, 
              0x65E2, 0x6C82, 0x123F, 0x9F09, 0xAAA2, 0xF821, 0x4D4D, 
              0x2727, 0x4238, 0xE66C, 0x6EE2, 0x8DA0, 0x92D8, 0x74FD, 
              0x4806, 0x0C33, 0xBBC1 };
 
short h[] = { 0xBC16, 0x2990, 0x7D0A, 0x1ABE, 0x342A, 0x5DA0, 0xD33B, 
              0xC7A6, 0x2E53, 0xAB24, 0x9E49, 0x18DE, 0x57DB, 0xD556, 
              0x89A2, 0x1DD4, 0x3AB6, 0x1B3A, 0xDE21, 0x2484, 0xBB04, 
              0xB721, 0xFF8B, 0x35F6, 0x9E92, 0x5F2B, 0xED14, 0x94BB, 
              0x0058, 0xC8BF, 0xC4DA, 0x4475 };

/****************************************************************************/
/* TOP LEVEL DRIVER FOR THE TEST.                                           */
/****************************************************************************/
int main()
{
    int i;
    clock_t t_overhead, t_start, t_stop, t_fir;
 
    /************************************************************************/
    /* COMPUTE THE OVERHEAD OF CALLING CLOCK TWICE TO GET TIMING INFO.      */
    /************************************************************************/
    t_start    = clock();
    t_stop     = clock();
    t_overhead = t_stop - t_start;

    /************************************************************************/
    /* TIME FIR1.                                                            */
    /************************************************************************/
    t_start = clock();
    fir1(x, h, y1, N, M, S);
    t_stop = clock();
    printf("FIR1: %d cycles\n", t_stop - t_start - t_overhead);
 
    /************************************************************************/
    /* TIME FIR2.                                                           */
    /************************************************************************/
    t_start = clock();
    fir2((int*)x, (int*)h, y2, N, M, S);
    t_stop = clock();
    printf("FIR2: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(y1, y2, sizeof(y1)) != 0) printf ("Result failure fir2()\n");
}

/****************************************************************************/
/* FIR1 - Basic form                                                        */
/****************************************************************************/
void fir1(const short x[], const short h[], short y[], int n, int m, int s)
{
    int  i, j;
    long y0;
    long round = 1L << (s - 1);
 
    for (j = 0; j < m; j++)
    {
        y0 = round;
 
        for (i = 0; i < n; i++)
            y0 += x[i + j] * h[i];
 
        y[j] = (int) (y0 >> s);
    }
}
 
/****************************************************************************/
/* FIR2 - optimized to use intrinsics and read words.                       */
/****************************************************************************/
void fir2(const int x[], const int h[], short y[], int n, int m, int s)
{
    int  i, j;
    long y0, y1;
    long round = 1L << (s - 1);
 
    _nassert(m >= 16);
    _nassert(n >= 16);
 
    for (j = 0; j < (m >> 1); j++)
    {
        y0 = y1 = round;
 
        for (i = 0; i < (n >> 1); i++)
        {
            y0 += _mpy  (x[i + j],     h[i]);
            y0 += _mpyh (x[i + j],     h[i]);
            y1 += _mpyhl(x[i + j],     h[i]);
            y1 += _mpylh(x[i + j + 1], h[i]);
        }
 
        *y++ = (int)(y0 >> s);
        *y++ = (int)(y1 >> s);
    }
}
