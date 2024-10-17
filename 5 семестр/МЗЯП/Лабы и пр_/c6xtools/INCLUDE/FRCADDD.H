/****************************************************************************/
/*  frcaddd  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:55 EDT 1997 */

#ifndef __FRCADDF__
#define __FRCADDF__

#include "realdi.h"

#if (BPREAL == BPbigint) /* use compiler support for bigint add */

#elif (BPREAL == (BPbigint*2))
extern int FRCADDF(int lx, REAL_2UNS *lf, 
                   int rx, REAL_2UNS *rf);
#else
   #error "FRCADDF not yet implemented for this size REAL"
#endif

#endif /* __FRCADDF__ */
