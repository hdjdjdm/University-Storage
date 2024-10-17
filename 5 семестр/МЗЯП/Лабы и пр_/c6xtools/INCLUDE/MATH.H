/****************************************************************************/
/*  math  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:58 EDT 1997 */

#ifndef __math__
#define __math__

#ifndef EDOM
#define EDOM   1
#endif

#ifndef ERANGE
#define ERANGE 2
#endif

#include <float.h>
#define HUGE_VAL DBL_MAX

#ifdef _INLINE
   #define __INLINE static inline
#else
   #define __INLINE extern
#endif

extern double sqrt (double x);
extern double exp  (double x);
extern double log  (double x);
extern double log10(double x);
extern double pow  (double x, double y);
extern double sin  (double x);
extern double cos  (double x);
extern double tan  (double x);
extern double asin (double x);
extern double acos (double x);
extern double atan (double x);
extern double atan2(double y, double x);
extern double sinh (double x);
extern double cosh (double x);
extern double tanh (double x);

__INLINE double ceil (double x);
__INLINE double floor(double x);

extern double fabs (double x);

extern double ldexp(double x, int n);
extern double frexp(double x, int *exp);
extern double modf (double x, double *ip);
extern double fmod (double x, double y);

/* An inline version of fmod that works for limited domain only */
/* See comments in implementation below */
static inline double _FMOD(double x, double y);

/* these present in many linked images, so we'll tell you about them. */
extern double _round(double x); /* round-to-nearest */
extern double _trunc(double x); /* truncate towards 0 */

#undef __INLINE

/* the ANSI-optional *f and *l routines */
#include <mathf.h>
#include <mathl.h>

#ifdef _TI_ENHANCED_MATH_H
#if 0
/* ------------------------------------------------- */
/* Routines below are an addition to ANSI math.h     */
/* Some (noted with "9x" in comment) will become ANSI*/
/* once C9x is approved.                             */
/* ------------------------------------------------- */
#endif

extern double rsqrt(double x); /*    == 1/sqrt(x) but *MUCH* faster         */
extern double exp2 (double x); /* 9x mathematically equiv to pow(2.0 ,x)    */
extern double exp10(double x); /*    mathematically equiv to pow(10.0,x)    */
extern double log2 (double x); /* 9x mathematically equiv to log(x)/log(2.0)*/

extern double powi(double x, int i); /* equiv to pow(x,(double)i) */

extern double cot  (double x);
extern double acot (double x);
extern double acot2(double x, double y);

extern double coth (double x);

extern double asinh(double x); /* 9x */
extern double acosh(double x); /* 9x */
extern double atanh(double x); /* 9x */
extern double acoth(double x);

#define round(x) _round(x) /* 9x round-to-nearest   */
#define trunc(x) _trunc(x) /* 9x truncate towards 0 */

#endif


#ifdef _INLINE
/****************************************************************************/
/*  Inline versions of floor, ceil, fmod                                    */
/****************************************************************************/

static inline double floor(double x) 
{
   double y; 
   return (modf(x, &y) < 0 ? y - 1 : y);
}

static inline double ceil(double x)
{
   double y; 
   return (modf(x, &y) > 0 ? y + 1 : y);
}

/* 
   The implementation below does not work correctly for all cases.
   Consider the case of fmod(Big, 3), for any Big > 2**(MANT_DIG+2).
   The correct result is one of 0,1, or 2.
   But the implementation below will *always* return 0 
   because the quotient is only an approximation.
*/
static inline double _FMOD(double x, double y)
{
   double d = fabs(x); 
   if (d - fabs(y) == d) return (0);
   modf(x/y, &d);  
   return (x - d * y);
}

#endif


#endif /* __math__ */
