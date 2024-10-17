/****************************************************************************/
/*  ieeed  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:56 EDT 1997 */

#ifndef __ieeed__
#define __ieeed__

#include <limits.h>

extern double _absd(double x);
extern double _negd(double x);

extern double _addd(double left, double right);
extern double _subd(double left, double right);
extern double _mpyd(double left, double right);
extern double _divd(double left, double right);

extern int _cmpd(double left,
                 double right); /* <0 if LT, 0 if EQ, >0 if GT     */
                                /* no correct result if NaN source */

extern int _eqld(double left, double right);
extern int _neqd(double left, double right);
extern int _leqd(double left, double right);
extern int _geqd(double left, double right);
extern int _lssd(double left, double right);
extern int _gtrd(double left, double right);


/* char <-> double */
extern double        _fltcd(  signed char x);
extern double        _fltbd(unsigned char x);
extern   signed char _fixdc(double x);
extern unsigned char _fixdb(double x);

/* short <-> double */
extern double         _fltsid(         short x);
extern double         _fltusd(unsigned short x);
extern short          _fixdsi(double x);
extern unsigned short _fixdus(double x);

/* int <-> double */
extern double   _fltid(int      x);
extern double   _fltud(unsigned x);
extern int      _fixdi(double x);
extern unsigned _fixdu(double x);

/* long <-> double */
extern double        _fltlid(         long x);
extern double        _fltuld(unsigned long x);
extern long          _fixdli(double x);
extern unsigned long _fixdul(double x);


/* float <-> double */
extern float  _cvtdf(double x); /* slim from double to float  */
extern double _cvtfd(float  x); /* grow from float  to double */

#endif /* __ieeed__ */






