void vec_mpy1(short y[], const short x[], short scaler)
{
    int         i;
 
    for (i = 0; i < 150; i++)
        y[i] += ((scaler * x[i]) >> 15);
}
