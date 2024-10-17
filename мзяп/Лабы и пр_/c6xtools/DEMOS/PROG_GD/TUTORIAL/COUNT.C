#include <stdio.h>
#include <time.h>

main(int argc, char *argv[])
 
{
    const short coefs[150];
  short optr[150];
  short state[2];
  const short a[150];
  const short b[150];
  int c = 0;
  int dotp[1] = {0};
  int sum= 0;
  short y[150];
  short scalar = 3345;
  const short x[150];
  clock_t start, stop, overhead;

  start    = clock();
  stop     = clock();
  overhead = stop - start;

  start = clock();
  sum = mac1(a, b, c, dotp);
  stop = clock();
  printf("mac1 cycles: %d\n", stop - start - overhead);

  start = clock();
  vec_mpy1(y, x, scalar);
  stop = clock();
  printf("vec_mpy1 cycles: %d\n", stop - start - overhead);

  start = clock();
  iir1(coefs, x, optr, state);
  stop = clock();
  printf("iir1 cycles: %d\n", stop - start - overhead);
}
