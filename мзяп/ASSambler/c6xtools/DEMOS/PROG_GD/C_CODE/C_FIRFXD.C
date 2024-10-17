/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/*                                                                          */
/* C_FIRFXD.C - Example from Programmer's Guide on optimizing C code.       */
/*                                                                          */
/* cl6x -qko3 c_firfxd.c -z -llnk.cmd -lrts6201.lib -o c_firfxd.out         */
/* load6x -q -k c_firfxd.out                                                */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

void fir_fxd1(const short input[], const short coefs[], short out[]);
void fir_fxd2(const short input[], const short coefs[], short out[]);

short optr1[] = {
0xE2A2,	 0x72E7,  0xA053,  0x7902,  0x1017,  0x6091,  0x311C,  0xB6BA,
0x3AF1,	 0x48DC,  0xAE9C,  0x4F4C,  0x237B,  0x5ACA,  0xD3DB,  0xF9C5,
0xDF5A,	 0x2F53,  0x67FD,  0x95EE,  0x4B10,  0x4EEF,  0xBEC1,  0xAECC,
0x8F7B,	 0xA912,  0x3603,  0xFD21,  0xA155,  0x1FA9,  0xBC3C,  0xE7E7,
0xC3B4,	 0xFAA0,  0x47FF,  0xFBDA,  0x0189,  0x715D,  0x5A7D,  0x76ED };

short optr2[] = {
0xE2A2,	 0x72E7,  0xA053,  0x7902,  0x1017,  0x6091,  0x311C,  0xB6BA,
0x3AF1,	 0x48DC,  0xAE9C,  0x4F4C,  0x237B,  0x5ACA,  0xD3DB,  0xF9C5,
0xDF5A,	 0x2F53,  0x67FD,  0x95EE,  0x4B10,  0x4EEF,  0xBEC1,  0xAECC,
0x8F7B,	 0xA912,  0x3603,  0xFD21,  0xA155,  0x1FA9,  0xBC3C,  0xE7E7,
0xC3B4,	 0xFAA0,  0x47FF,  0xFBDA,  0x0189,  0x715D,  0x5A7D,  0x76ED };

short iptr[] = {
0xB623,	 0x2544,  0x8400,  0xC1D1,  0x06AC,  0xA633,  0xE171,  0xF074,
0x64A8,	 0xED06,  0x98D4,  0x437E,  0x0C7B,  0xE012,  0x5DC8,  0xA6D4,
0x87E2,	 0xD4AB,  0xEF0A,  0x3316,  0x2C77,  0x05A1,  0x99F1,  0xAD23,
0x9B2F,	 0x1DBC,  0xB3F2,  0x0492,  0x43DE,  0xB546,  0x201B,  0xD638,
0xDBAF,	 0xCD80,  0xCF9A,  0xEAA7,  0xEAAE,  0x5429,  0x3C35,  0xB5AB,
0x4141,	 0xA5FC,  0xEED1,  0xD7CD,  0x7EA8,  0x0631,  0xF9ED,  0x9DD3,
0x8983,	 0x29F9,  0x7C26,  0x7F3C,  0x184B,  0xAD04,  0x22B4,  0xA1C6 };

short cptr[] = {
0x2DD5,	 0x9BFD,  0xA3E9,  0x54E9,  0x95D4,  0xEC0A,  0x42B7,  0x945B,
0x6955,	 0x004F,  0x4F29,  0x8A8C,  0x8E43,  0x266A,  0xA4E6,  0x092A };

/****************************************************************************/
/* TOP LEVEL DRIVER FOR THE TEST.                                           */
/****************************************************************************/
int main()
{
    int i;
    clock_t t_overhead, t_start, t_stop, t_fir_fxd;
 
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
    fir_fxd1(iptr, cptr, optr1);
    t_stop = clock();
    printf("FIR_FXD1: %d cycles\n", t_stop - t_start - t_overhead);
 
    /************************************************************************/
    /* TIME FIR2.                                                           */
    /************************************************************************/
    t_start = clock();
    fir_fxd2(iptr, cptr, optr2);
    t_stop = clock();
    printf("FIR_FXD2: %d cycles\n", t_stop - t_start - t_overhead);
    if (memcmp(optr1, optr2, sizeof(optr1)) != 0) printf ("Result failure\n");
	
}

/****************************************************************************/
/* FIR_FXD1 - Basic form                                                    */
/****************************************************************************/
void fir_fxd1(const short input[], const short coefs[], short out[])
{
    int i, j;
 
    for (i = 0; i < 40; i++)
    {
	int sum = 0;

        for (j = 0; j < 16; j++)
            sum += coefs[j] * input[i + 15 - j];
 
        out[i] = (sum >> 15);
    }
}
 
/****************************************************************************/
/* FIR_FXD2 - Optimized form.                                               */
/****************************************************************************/
void fir_fxd2(const short input[], const short coefs[], short out[])
{
    int i, j;
    int sum;
 
    for (i = 0; i < 40; i++)
    {
        sum  = coefs[0]  * input[i + 15];
        sum += coefs[1]  * input[i + 14];
        sum += coefs[2]  * input[i + 13];
        sum += coefs[3]  * input[i + 12];
        sum += coefs[4]  * input[i + 11];
        sum += coefs[5]  * input[i + 10];
        sum += coefs[6]  * input[i + 9];
        sum += coefs[7]  * input[i + 8];
        sum += coefs[8]  * input[i + 7];
        sum += coefs[9]  * input[i + 6];
        sum += coefs[10] * input[i + 5];
        sum += coefs[11] * input[i + 4];
        sum += coefs[12] * input[i + 3];
        sum += coefs[13] * input[i + 2];
        sum += coefs[14] * input[i + 1];
        sum += coefs[15] * input[i + 0];
 
        out[i] = (sum >> 15);
    }
}
