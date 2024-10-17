/****************************************************************************/
/*         Copyright (C) 1996-1997 Texas Instruments Incorporated           */
/*                      All Rights Reserved                                 */
/* C3_DOTP      - DOT PRODUCT                                               */
/* To compile:  cl6x -qko3 c3_dotp.c dotp3.sa a3_dotp.asm -z -l lnk.cmd     */
/*                   -l rts6201.lib -o c3_dotp.out                          */
/****************************************************************************/
#include <stdio.h>
#include <time.h>

short a[100] = { 432, 30, 1839, -134, 0, 12460, 293, -1231, 527, 14491,
                2056, -6, 7, 0, -6, -12, -161, 0, 43, -15714,
                26, -11, 7, 4, -3875, 219, -1, 100, 604, -216,
                -8, -116, -1, -263, 3, -359, -690, -3595, 326, 0,
                7063, -809, 19, -3, 15745, -3267, 0, 7, -13, 484,
                194, -7309, -13390, -191, 13047, -11235, -107, 7741, 14, 869,
                -121, 3, 14, -184, 3793, -606, -1096, 3163, 221, 3327,
                3, -7, 1531, -168, 1, 3137, 196, -979, 7196, -62,
                -264, -1, 1, 9006, 5179, 19, 0, 530, -3, -1,
                -91, 0, 1, 1, -154, -466, 15, 811, -3222, -5762};
 
short b[100] = { 376, -5, -3, 1, -1883, 26, 3673, -1, 0, 9440,
                -1522, -2, 548, 33, 0, 0, 266, 7, 935, -89,
                635, 229, -29, 3464, 32, 40, -11796, -7881, -6419, -3,
                0, 1871, -4907, 1965, -628, 22, 10272, -2, -1, 30,
                -1, 1343, -1, -14604, 1962, -428, 124, -22, -2463, -14,
                28, -28321, -28, 1775, -389, 1774, 25, -56, 3587, 7,
                49, 1, 107, 0, -1, -6024, 1091, 347, 99, -742,
                -64, 15, -1, -237, 14814, 61, -4, -306, -300, -1,
                -1, -3, 5925, 8102, 4803, 1, 206, 16304, 6, -2,
                -1427, -69, -1584, -1871, 98, -1, 158, -1, -1122, 782};
 
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
    t_stub = time_stub(&ret_stub) - t_overhead;
    t_asm  = time_asm(&ret_asm)   - t_overhead;
    t_sa   = time_sa(&ret_sa)     - t_overhead;

    /************************************************************************/
    /* PRINT TIMING RESULTS                                                 */ 
    /************************************************************************/ 
    printf("DOT_PRODUCT1 Assembly Clock Cycles:           %d\n",
            t_asm - t_stub);
    printf("DOT_PRODUCT1 Assembly Optimizer Clock Cycles: %d\n", 
            t_sa - t_stub);
}

int dotp_stub(const short a[], const short b[])
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
    *i      = dotp_stub(a, b);
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
    *i      = dotp_asm(a, b);
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
    *i      = dotp_sa(a, b);
    t_stop  = clock();
    return  t_stop - t_start;
}

/* Sample C code
int dotp_c(const short a[], const short b[])
{
    int sum0, sum1, sum;
    int i;

    sum0 = 0;
    sum1 = 0;
    for(i=0; i<100; i+=2)
    {
        sum0 += (a[i] * b[i]);
        sum1 += (a[i+1] * b[i+1]);
    }
    sum = sum0 + sum1;
    return(sum);
}
*/

