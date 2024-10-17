/****************************************************************************/
/*  renormd  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:59 EDT 1997 */

#ifndef __RENORMF__
#define __RENORMF__

#include "realdi.h"

#if (BPREAL == BPbigint)
   /* #define COUNT_LZERO(nnn) DEFAULT_IS_UNDEFINED                          */
   /* If defined, must be macro that returns the count of the number of      */
   /* consecutive zero bits at the most significant end of nnn.              */
   /* If COUNT_LZERO is not defined, alternate implementations will be used. */


   /* int RENORMF(bigint ff, int ee)                                         */
   /* ff (0<ff<REAL_HIDDEN_BIT) is left shifted until ff >= REAL_HIDDEN_BIT. */
   /* At least one shift is required.                                        */
   /* ee is decremented by the number of shifts.                             */
   #ifdef Support_DENORM
      #ifdef COUNT_LZERO
         #define RENORMF(ff,ee) do {int tmp = \
                                   COUNT_LZERO(ff)-BPbigint+\
                                   (REAL_FRC_MSBs)+1;\
                                ff <<= tmp; ee -= tmp-1;} while(0)
      #else
         #define RENORMF(ff,ee) while ((ff <<= 1) < REAL_HIDDEN_BIT) ee -= 1
      #endif
   #endif

   /* int RENORM2F(bigint ff, int ee)                                        */
   /* ff (0<ff<REAL_HIDDEN_BIT*2) is left shifted until ff>=REAL_HIDDEN_BIT*2*/
   /* At least one shift is required.                                        */
   /* ee is decremented by the number of shifts.                             */
   #ifdef COUNT_LZERO
      #define RENORM2F(ff,ee) do {int tmp=\
                                COUNT_LZERO(ff)-BPbigint+\
                                (REAL_FRC_BITS%BPbigint)+2;\
                               ff <<= tmp; ee -= tmp;} while (0)
   #else
      #define RENORM2F(ff,ee) do ee -= 1; while ((ff <<= 1) < REAL_HIDDEN_BIT*2)
   #endif
#elif (BPREAL == (BPbigint*2))
   extern int RENORMF(REAL_2UNS *ff);
#else
   #error "RENORMF not yet implemented for this size REAL"
#endif

#endif /* __RENORMF__ */
