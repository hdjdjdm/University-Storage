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
short scaler = 3345;
const short x[150];
 
sum = mac1(a, b, c, dotp);
vec_mpy1(y, x, scaler);
iir1(coefs, x, optr, state);

}
