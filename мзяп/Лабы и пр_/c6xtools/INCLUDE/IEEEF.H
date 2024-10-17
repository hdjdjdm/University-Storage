/****************************************************************************/
/*  ieeef  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:07:57 EDT 1997 */

#ifndef __ieeef__
#define __ieeef__

#include <limits.h>

extern float _absf(float x);
extern float _negf(float x);

extern float _addf(float left, float right);
extern float _subf(float left, float right);
extern float _mpyf(float left, float right);
extern float _divf(float left, float right);

extern int _cmpf(float left,
                 float right); /* <0 if LT, 0 if EQ, >0 if GT     */
                               /* no correct result if NaN source */

extern int _eqlf(float left, float right);
extern int _neqf(float left, float right);
extern int _leqf(float left, float right);
extern int _geqf(float left, float right);
extern int _lssf(float left, float right);
extern int _gtrf(float left, float right);


/* char <-> float */
extern float         _fltcf(  signed char x);
extern float         _fltbf(unsigned char x);
extern   signed char _fixfc(float x);
extern unsigned char _fixfb(float x);

/* short <-> float */
extern float          _fltsif(         short x);
extern float          _fltusf(unsigned short x);
extern short          _fixfsi(float x);
extern unsigned short _fixfus(float x);

/* int <-> float */
extern float    _fltif(int      x);
extern float    _fltuf(unsigned x);
extern int      _fixfi(float x);
extern unsigned _fixfu(float x);

/* long <-> float */
extern float         _fltlif(         long x);
extern float         _fltulf(unsigned long x);
extern long          _fixfli(float x);
extern unsigned long _fixful(float x);

#endif /* __ieeef__ */
