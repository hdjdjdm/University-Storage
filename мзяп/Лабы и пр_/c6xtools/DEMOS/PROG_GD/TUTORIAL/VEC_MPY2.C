void vec_mpy2(int y[], const int x[], short scaler)
{
    int          i, val;
    unsigned int temph, templ;
 
    for (i = 0; i < 75; i++)
    {
         val = x[i];
         templ   = (_mpy  (scaler, val) >> 15) & 0x0000ffff;
         temph   = (_mpylh(scaler, val) << 1 ) & 0xffff0000;
         y[i] = _add2(y[i], temph | templ);
    }
}
