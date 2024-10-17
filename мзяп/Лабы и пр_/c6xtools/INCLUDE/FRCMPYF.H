/****************************************************************************/
/*  frcmpyf  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:07:56 EDT 1997 */

#ifndef __FRCMPYF__
#define __FRCMPYF__

#include "realfi.h"

#if (BPREAL == BPbigint)
extern biguns FRCMPYF(biguns l, biguns r);

#elif (BPREAL == (BPbigint*2))
extern int FRCMPYF(REAL_2UNS *p, REAL_2UNS *l, REAL_2UNS *r);

#else
   #error "FRCMPYF not yet implemented for this size REAL"
#endif

#endif /*__FRCMPYF__*/
