/****************************************************************************/
/*  formi64  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:54 EDT 1997 */

#ifndef __formi64__
#define __formi64__

#if 0 /* eliminate comments during source build */
/*---------------------------------------------------------------------------*/
/* Description of the IEEE 64-bit float format.                              */
/*                                                                           */
/* This file is used in conjunction with the c pre-processor to build        */
/* customized product sources.  It is carefully constructed so that comments */
/* are removed by the preprocessor and all expansions result in a minimum    */
/* disruption of surrounding code.                                           */
/*                                                                           */
/* All floating-point constants in this file must be expressed either        */
/* exactly or to *MORE* places than REAL_DIGITS (REAL_DIGITS+3 is suggested).*/
/*---------------------------------------------------------------------------*/
#endif

#if 0
/*---------------------------------------------------------------------------*/
/* REAL is described in terms of the canonical form:  +/- f * r**e           */
/* where: r is "radix",                                                      */
/*        e is "exponent" (an integer),                                      */
/*        f is fractional part (mantissa) and  1/r <= f < 1,                 */
/*---------------------------------------------------------------------------*/
#endif
#define REAL_RADIX     2 /* radix (r)                                        */
#define REAL_MANTISSA 53 /* radix digits in mantissa                         */
#define REAL_EMAX   1024 /* max e for which +/- f has MANTISSA digits        */
#define REAL_EMIN (-1021)/* min e for which +/- f has MANTISSA digits        */
#define REAL_DIGITS   15 /* FLRF(REAL_MANTISSA-1)*Ln_RADIX/Ln_10)            */
                                
#define Round_To_Even

#define IEEE /* don't define "IEEE" at all if not ieee format */

#if defined(Generate_Sources)
   #define if_IEEE_Hardware #ifdef IEEE_Hardware
   #define elsif_not_IEEE_Hardware #else
   #define endif_IEEE_Hardware #endif
#elif defined(IEEE_Hardware)
   #define if_IEEE_Hardware if (IEEE_Hardware) {
   #define elsif_not_IEEE_Hardware } else {
   #define endif_IEEE_Hardware }
#else
   #define if_IEEE_Hardware if (0) {
   #define elsif_not_IEEE_Hardware } else {
   #define endif_IEEE_Hardware }
#endif

#define REAL_EXP_BITS 11 /* bits in unsigned_exp_field */
#define REAL_FRC_BITS 52 /* bits in fraction_field     */
#define REAL_EXP_BIAS 1023/* exponent = unsigned_exp_field - REAL_EXP_BIAS */

#if BPLEAN==0 /* no next-smaller REAL */
   #undef LEAN_DIGITS
   #undef LEAN_EXP_BITS
   #undef LEAN_FRC_BITS
   #undef LEAN_EXP_BIAS
#elif BPLEAN==32 /* shape of next-smaller REAL (for grow/slim routines) */
   #define LEAN_DIGITS 6
   #define LEAN_EXP_BITS 8  /* bits in unsigned_exp_field */
   #define LEAN_FRC_BITS 23 /* bits in fraction_field     */
   #define LEAN_EXP_BIAS 127/* exponent=unsigned_exp_field-LEAN_EXP_BIAS */
#else
   #error "LEAN_* not yet defined for this size LEAN"
#endif

#if 0
/*---------------------------------------------------------------------------*/
/* Absolute extremes of floating point range.                                */
/* f need not have full MANTISSA digits, but do not                          */
/* include consideration of NAN's, ZEROs, infinities.                        */
/* Express to *MORE* places than REAL_DIGITS.                                */
/*---------------------------------------------------------------------------*/
#endif
#define REAL_MOST_POS  CNST( 1.7976931348623157e+308)
#define REAL_MOST_NEG  CNST(-1.7976931348623157e+308)

#ifdef Support_DENORM
   #define REAL_LEAST_POS CNST( 4.9406564584124654e-324) /* denormalized */
   #define REAL_LEAST_NEG CNST(-4.9406564584124654e-324) /* denormalized */
   #define LEAST_POS_INVERTABLE_NOT_LEAST_POS 1
#else
   #define REAL_LEAST_POS CNST( 2.225073858507201383e-308)
   #define REAL_LEAST_NEG CNST(-2.225073858507201383e-308)
   #define LEAST_POS_INVERTABLE_NOT_LEAST_POS 0
#endif

#define REAL_LEAST_POS_INVERTABLE CNST(2.225073858507201383e-308)
#if 0                 /* usually (-EMIN<EMAX) ? RADIX**(EMIN-1) : 1/MOST_POS */


/*---------------------------------------------------------------------------*/
/* Constants derived from RADIX & MANTISSA needed for math.h routines.       */
/* Express to *MORE* places than REAL_DIGITS.                                */
/*---------------------------------------------------------------------------*/
#endif
#define RADIX                    CNST( 2.0) /* FLTIF(REAL_RADIX   )          */
#define MANTISSA                 CNST(53.0) /* FLTIF(REAL_MANTISSA)          */

#define Ln_RADIX                 Ln_2   /* ln(RADIX)                         */
#define Sqrt_RADIX               Sqrt_2 /* sqrt(RADIX)                       */

#define RADIX_to(x)              SCLF(ONE,x) /* RADIX**x, x an integer       */

#define RADIX_to_Hlf_MANTISSA_M1 CNST(33554432.0)/* RADIX**((MANTISSA/2)-1)  */
#define RADIX_to_Hlf_MANTISSA_M2 CNST(16777216.0)/* RADIX**((MANTISSA/2)-2)  */
#define RADIX_to_Hlf_MANTISSA    CNST(67108864.0)/* RADIX**( MANTISSA/2   )  */
#define RADIX_to_MANTISSA        CNST(9007199254740992.0)/*RADIX**MANTISSA   */

#define One_Over_RADIX          CNST(0.5)/*                     RDX**(-1    )*/
#define RADIX_to_M_Hlf_MANTISSA CNST(1.490116119384765625e-08)/*RDX**(-MNT/2)*/
#define RADIX_to_One_M_MANTISSA CNST(2.220446049250313081e-16)/*RDX**(1-MNT )*/
#define RADIX_to_M_MANTISSA     CNST(1.110223024625156540e-16)/*RDX**( -MNT )*/
#define RADIX_to_EMIN           CNST(4.450147717014402766e-308)/*RDX**(EMIN )*/

#ifndef BPint
   #error "target props .h file must be included before REAL format .h file"
#endif
#define RND_GLITCH ((REAL_MANTISSA+1) <= BPint)
#define RND_P_GLITCH RADIX_to_MANTISSA
#define RND_M_GLITCH CNST(-9007199254740991.0) /* -(RADIX**MANTISSA-1) */

#define SQRT_Sz_Newtons  3 /* (int)FLOOR(LOG2((MANTISSA-1)/5))               */
#define SQRT_CW_Newtons  4 /* (int)CEIL (LOG2( MANTISSA     ))-2             */

#define EXP_Max CNST(7.097827128933838594e+02) /*ln(MOST_POS )*(1-RDX**-MNT) */
#define EXP_Min CNST(-7.077032713517040747e+02)/*ln(RDX**EMIN)*(1-RDX**-MNT) */

#define POW_Ovfl CNST( 11355.0) /* FLOOR(16*ln(MOST_POS)-1)                  */
#define POW_Unfl CNST(-11323.0) /* FLOOR(16*ln(RADIX**EMIN)+1)               */

#define TANH_Max CNST(1.906154746539849754e+01)/*(Ln_2+(MNT+1)*Ln_RADIX)/2   */

#endif /*__formi64__*/
