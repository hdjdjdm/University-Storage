/****************************************************************************/
/*  syntd  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Fri May 30 15:35:40 EDT 1997 */

#ifndef __syntd__
#define __syntd__

#if 0
/*---------------------------------------------------------------------------*/
/* Bind abstract REAL to "double" syntax.                                    */
/* Use built-in operators for unary -, +,-,*,/, >,<,>=,<=,==,!=, =           */
/* Use ANSI names for double version of math.h routines (sqrt, sin, ... etc) */
/*---------------------------------------------------------------------------*/
#endif

#define REAL double
#define EXPONENT_TYPE int

#if BPLEAN == 0
   #undef LEAN
#else /* since REAL is "double", assume next smallest is "float" */
   #define LEAN float
#endif

#define CNST(x) (x) /* constants within statements */
#define TSNC
#define KNST(x) x   /* constants within tables     */
#define TSNK

#include "numconst.h" /* NUMerical CONSTants used by some definitions below */

#if 0
/*---------------------------------------------------------------------------*/
/* Define Compiler Syntax For Basic Operations                               */
/*---------------------------------------------------------------------------*/
/* Names have form: <operation> F { 1 | 2 | 3 }?                             */
/* Where <operation> is one of:                                              */
/*    CPY  -- simple assignment                                              */
/*    NEG  -- negative                                                       */
/*    ABS  -- absolute value                                                 */
/*    SQR  -- square                                                         */
/*    INV  -- inverse (1/x)                                                  */
/*    ADD  -- plus                                                           */
/*    SUB  -- subtract                                                       */
/*    MPY  -- multiply                                                       */
/*    DIV  -- division                                                       */
/*    EQL  -- ==                                                             */
/*    NEQ  -- !=                                                             */
/*    GTR  -- >                                                              */
/*    GEQ  -- >=                                                             */
/*    LSS  -- <                                                              */
/*    LEQ  -- <=                                                             */
/*    EQZ  -- == 0.0                                                         */
/*    NEZ  -- != 0.0                                                         */
/*    GTZ  -- >  0.0                                                         */
/*    GEZ  -- >= 0.0                                                         */
/*    LSZ  -- <  0.0                                                         */
/*    LEZ  -- <= 0.0                                                         */
/* F means REAL                                                              */
/* If no 1,2 or 3 suffix then is function returning result.                  */
/* Optional 1,2 or 3 means 1-addr, 2-addr or 3-addr version:                 */
/*    1 -> right = operation right;                                          */
/*    2 -> dst   = operation right;      ( unary operations)                 */
/*         left  = left operation right; (binary operations)                 */
/*    3 -> dst   = left operation right;                                     */
/*---------------------------------------------------------------------------*/
#endif

#define CPYF(dst,right) dst=(right)

#define NEGF(right) (-(right))
#define ABSF(right) (LSSF(right,ZERO) ? NEGF(right) : (right))
#define SQRF(right) ((right) * (right))
#define INVF(right) DIVF(ONE,right)

#define ADDF(left,right) ((left)+(right))
#define SUBF(left,right) ((left)-(right))
#define MPYF(left,right) ((left)*(right))
#define DIVF(left,right) ((left)/(right))

#define NEGF2(dst,right) dst=(-(right))
#define ABSF2(dst,right) dst=(LSSF(right,ZERO)?NEGF(right):(right))
#define SQRF2(dst,right) dst=(right)*(right)
#define INVF2(dst,right) dst=INVF(right)

#define ADDF3(dst,left,right) dst=(left)+(right)
#define SUBF3(dst,left,right) dst=(left)-(right)
#define MPYF3(dst,left,right) dst=(left)*(right)
#define DIVF3(dst,left,right) dst=(left)/(right)

#define NEGF1(right) (right)=-(right)
#define ABSF1(right) if LSSF(right,ZERO) NEGF1(right)
#define SQRF1(right) (right)*=(right)
#define INVF1(right) (right)=INVF(right)

#define ADDF2(left,right) (left)+=(right)
#define SUBF2(left,right) (left)-=(right)
#define RSBF2(left,right) (left) =(right)-(left)
#define MPYF2(left,right) (left)*=(right)
#define DIVF2(left,right) (left)/=(right)

#define CMPF(left,right) ((left)<(right)?-1:((left)!=(right)))
#define CMPF3(dst,left,right) dst=CMPF(left,right)

#define EQLF(left,right) ((left)==(right))
#define NEQF(left,right) ((left)!=(right))
#define LEQF(left,right) ((left)<=(right))
#define GEQF(left,right) ((left)>=(right))
#define GTRF(left,right) ((left)>(right))
#define LSSF(left,right) ((left)<(right))

#define EQZF(left) EQLF(left,ZERO)
#define NEZF(left) NEQF(left,ZERO)
#define LEZF(left) LEQF(left,ZERO)
#define GEZF(left) GEQF(left,ZERO)
#define GTZF(left) GTRF(left,ZERO)
#define LSZF(left) LSSF(left,ZERO)



#if 0
/*---------------------------------------------------------------------------*/
/* Compose and Decompose REAL                                                */
/* integer <-> REAL conversion operations                                    */
/* REAL whole number conversions                                             */
/* REAL whole number conversions, caller KNOWS whole number fits in int      */
/* Exact Remainder                                                           */
/*---------------------------------------------------------------------------*/
/* Names have form: <operation> F { 1 | 2 | 3 }?                             */
/* Where <operation> is one of:                                              */
/*    SCL  -- f * RADIX**e                                                   */
/*    RIP  -- decompose x into f,e such that x == f*RADIX**e and 1/RADIX<=f<1*/
/*                                                                           */
/*    FIX  -- truncate towards zero and convert to int                       */
/*    FLT  -- convert int  to REAL                                           */
/*                                                                           */
/*    TNC  -- truncate towards 0                (x fits in int)              */
/*    RND  -- round to nearest whole number REAL(x fits in int)              */
/*    FLR  -- truncate towards minus infinity   (x fits in int)              */
/*    CEI  -- truncate towards plus  infinity   (x fits in int)              */
/*                                                                           */
/*    REM  -- *EXACT* remainder (big horrible by-hand divide routine)        */
/*                                                                           */
/* Note that the following whole number approximation rtns exist in math.h:  */
/*    TRUNCF -- truncate towards 0                (x any value)              */
/*    ROUNDF -- round to nearest whole number REAL(x any value)              */
/*    FLOORF -- truncate towards minus infinity   (x any value)              */
/*    CEILF  -- truncate towards plus  infinity   (x any value)              */
/*                                                                           */
/* F means REAL                                                              */
/* If no 1,2 or 3 suffix then is function returning result.                  */
/* Optional 1,2 or 3 means 1-addr, 2-addr or 3-addr version:                 */
/*    1 -> right = operation right;                                          */
/*    2 -> dst   = operation right;      ( unary operations)                 */
/*         left  = left operation right; (binary operations)                 */
/*    3 -> dst   = left operation right;                                     */
/*---------------------------------------------------------------------------*/
#endif

#define RIPF(x,f,e) f=FREXPF((x),&e)

#define SCLF(f,e)            LDEXPF((f),(e))
#define SCLF2(f,e)       f = LDEXPF((f),(e))
#define SCLF3(dst,f,e) dst = LDEXPF((f),(e))

#define FIXFC(x) ((char)(x))
#define FLTCF(x) ((REAL)(x))

#define FIXFB(x) ((unsigned char)(x))
#define FLTBF(x) ((REAL)(x))

#define FIXFSI(x) ((short)(x))
#define FLTSIF(x) ((REAL)(x)) 

#define FIXFUS(x) ((unsigned short)(x))
#define FLTUSF(x) ((REAL)(x))

#define FIXFI(x) ((int)(x))
#define FLTIF(x) ((REAL)(x))

#define FIXFU(x) ((unsigned)(x))
#define FLTUF(x) ((REAL)(x))

#define FIXFLI(x) ((long)(x))
#define FLTLIF(x) ((REAL)(x))

#define FIXFUL(x) ((unsigned long)(x))
#define FLTULF(x) ((REAL)(x))

#if 0
/* TNCF, RNDF, FLRF, CEIF, may all use FLTIF(FIXFI(f(x))).                */
/* Call sites must be sure to enforce several rules:                      */
/* 1. TRUNCF(f(x)) must not exceed the integer range.                     */
/* 2. if REAL does unbiased round-towards-even,                           */
/*    input x to RNDF must never equal +/- RADIX_to_Mantissa-1.           */
#endif
#ifndef RND_GLITCH
   #error "REAL format .h file must be included before REAL syntax .h file"
#endif
#if (RND_GLITCH)
   #define RND_MAX_P1 RND_P_GLITCH
   #define RND_MIN    RND_M_GLITCH
#else
   #define RND_MAX_P1 INT_MOST_POS_P1
   #define RND_MIN    INT_MOST_NEG
#endif
#ifndef FLT_FIX_Faster_Than_MODF
   #error "target props .h file must be included before REAL syntax .h file"
#endif
#if (FLT_FIX_Faster_Than_MODF)
   #define TNCF(x) (FLTIF(FIXFI(x)))

   #define RNDF(x) (GEZF(x)? \
                    FLTIF(FIXFI((ADDF((x),HALF)))) : \
                    FLTIF(FIXFI((SUBF((x),HALF)))))

   #define FLRF(x) (GEZF(x) ? \
                    (FLTIF(FIXFI(x))) : \
                     (EQLF(x,FLTIF(FIXFI(x))) ? \
                      x : \
                      (FLTIF(NEGF(FIXFI(ADDF(NEGF(x),ONE)))))))

   #define CEIF(x) (LEZF(x) ? \
                    (FLTIF(FIXFI(x))) : \
                     (EQLF(x,FLTIF(FIXFI(x))) ? \
                      x : \
                      (FLTIF(NEGF(FIXFI(SUBF(NEGF(x),ONE)))))))

#else /* call through to general purpose routines */
   #define TNCF(x) (TRUNCF(x))
   #define RNDF(x) (ROUNDF(x))
   #define FLRF(x) (FLOORF(x))
   #define CEIF(x) (CEILF(x))
#endif

#define FIXFI1(x) x=FIXFI(x)
#define FLTIF1(x) x=FLTIF(x)
#define FIXFU1(x) x=FIXFU(x)
#define FLTUF1(x) x=FLTUF(x)

#define TNCF1(x) x=TNCF(x)
#define RNDF1(x) x=RNDF(x)
#define FLRF1(x) x=FLRF(x)
#define CEIF1(x) x=CEIF(x)

#define FIXFI2(dst,right) dst=FIXFI(right)
#define FLTIF2(dst,right) dst=FLTIF(right)
#define FIXFU2(dst,right) dst=FIXFU(right)
#define FLTUF2(dst,right) dst=FLTUF(right)

#define TNCF2(dst,right) dst=TNCF(right)
#define RNDF2(dst,right) dst=RNDF(right)
#define FLRF2(dst,right) dst=FLRF(right)
#define CEIF2(dst,right) dst=CEIF(right)


#define REMF(right,left)           (FMODF(right,left))
#define REMF1(right,left)     right=FMODF(right,left)
#define REMF2(dst,right,left) dst  =FMODF(right,left)

#if 0
/*---------------------------------------------------------------------------*/
/* IEEE software support specific routines                                   */
/*---------------------------------------------------------------------------*/
#endif
#ifdef LEAN
   #define GROWF(x) ((REAL)(x)) /* grow from LEAN to REAL */
   #define SLIMF(x) ((LEAN)(x)) /* slim from REAL to LEAN */
#endif


#if 0
/*---------------------------------------------------------------------------*/
/* Polynomial evaluation loops macros.                                       */
/*---------------------------------------------------------------------------*/
/* Loops are used for all polynomials.  It is assumed that this              */
/* is more DSP-friendly given that DSP hardware/software has:                */
/*   . zero-overhead looping,                                                */
/*   . optimizations to software pipeline multiply-accumulate,               */
/*   . the lack of full-precision floating-immediate address mode,           */
/*   . relatively expensive fetch of non-tabular constants,                  */
/*   . the existance of auto-increment addressing for table access.          */
/*---------------------------------------------------------------------------*/

/* form of: r=(((K[0]*x + K[1])*x + K[2])*x); r not same as x */
#endif
#define POLYF(r,x,K,s) {int i; REAL *p=K;                             \
                        MPYF3(r,x,*p++);                              \
                        for (i=s-1; i>0; i--) MPYF3(r,x,ADDF(r,*p++));}

#if 0
/* extra add at the end */
/* form of: r=(((K[0]*x + K[1])*x + K[2])*x) + K[3];  r not same as x */
#endif
#define POLYaF(r,x,K,s) {int i; REAL *p=K;                             \
                         MPYF3(r,x,*p++);                              \
                         for (i=s-2; i>0; i--) MPYF3(r,x,ADDF(r,*p++));\
                         ADDF2(r,*p++);}

#if 0
/* form of: r=((K[0]+x)*x + K[1])*x + K[2]) * x) + K[3]; r not same as x */
#endif
#define POLYbF(r,x,K,s) {int i; REAL *p=K;                             \
                         ADDF3(r,x,*p++);                              \
                         for (i=s-1; i>0; i--) ADDF3(r,*p++,MPYF(x,r));}

#if 0
/*---------------------------------------------------------------------------*/
/* Bind The Names Of The Math Library Routines                               */
/*---------------------------------------------------------------------------*/
#endif
#define SQRTF(x)    sqrt(x)
#define RSQRTF(x)   rsqrt(x)
#define EXPF(x)     exp(x)
#define EXP2F(x)    exp2(x)
#define EXP10F(x)   exp10(x)
#define LOGF(x)     log(x)
#define LOG2F(x)    log2(x)
#define LOG10F(x)   log10(x)
#define POWF(x,y)   pow(x,y)
#define POWIF(x,i)  powi(x,i)
#define SINF(x)     sin(x)
#define COSF(x)     cos(x)
#define TANF(x)     tan(x)
#define COTF(x)     cot(x)
#define ASINF(x)    asin(x)
#define ACOSF(x)    acos(x)
#define ATANF(x)    atan(x)
#define ATAN2F(y,x) atan2(y,x)
#define ACOTF(x)    acot(x)
#define ACOT2F(x,y) acot2(x,y)
#define SINHF(x)    sinh(x)
#define COSHF(x)    cosh(x)
#define TANHF(x)    tanh(x)
#define COTHF(x)    coth(x)
#define ASINHF(x)   asinh(x)
#define ACOSHF(x)   acosh(x)
#define ATANHF(x)   atanh(x)
#define ACOTHF(x)   acoth(x)

#define CEILF(x)    ceil(x)
#define FLOORF(x)   floor(x)
#define TRUNCF(x)   _trunc(x)
#define ROUNDF(x)   _round(x)

#define FABSF(x)    fabs(x)

#define LDEXPF(x,n)   ldexp(x,n)
#define FREXPF(x,exp) frexp(x,exp)
#define MODFF(x,ip)   modf(x,ip)
#define FMODF(x,y)    fmod(x,y)

#endif /*__syntd__*/
