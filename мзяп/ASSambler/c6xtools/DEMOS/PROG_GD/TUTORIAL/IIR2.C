void iir2(const int *coefs, const short *input, short *optr, short *state)
{
    short                x;
    short                t;
    int                  n;
 
    x = input[0];
 
    for (n = 0; n < 50; n++)
    {
        t= x+((_mpy(coefs[1],state[0]) + _mpyhl(coefs[1],state[1])) >> 15);
        x= t+((_mpy(coefs[0],state[0]) + _mpyhl(coefs[0],state[1])) >> 15);
 
        state[1] = state[0];
        state[0] = t;
 
        coefs += 2;
        state += 2;
        }
 
     *optr++ = x;
}
