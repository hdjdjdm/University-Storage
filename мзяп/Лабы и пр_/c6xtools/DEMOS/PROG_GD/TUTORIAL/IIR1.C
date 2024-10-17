void iir1(const short *coefs, const short *input, short *optr, short *state)
{
    short                x;
    short                t;
    int                  n;
 
    x = input[0];
 
    for (n = 0; n < 50; n++)
    {
            t = x + ((coefs[2] * state[0] +
                      coefs[3] * state[1]) >> 15);
 
            x = t + ((coefs[0] * state[0] +
                      coefs[1] * state[1]) >> 15);
 
            state[1] = state[0];
            state[0] = t;
            coefs    += 4;  /* point to next filter coefs  */
            state   += 2;  /* point to next filter states */
        }
 
    *optr++ = x;
}
