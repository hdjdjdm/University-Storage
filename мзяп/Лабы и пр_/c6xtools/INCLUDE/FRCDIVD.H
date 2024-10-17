/****************************************************************************/
/*  frcdivd  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:55 EDT 1997 */

#ifndef __FRCDIVF__
#define __FRCDIVF__

#include "realdi.h"

#if (BPREAL == BPbigint)
biguns FRCDIVF(biguns l, biguns r);
#elif (BPREAL == (BPbigint*2))
extern int FRCDIVF(REAL_2UNS *p, REAL_2UNS *l, REAL_2UNS *r);

#else
   #error "FRCDIVF not yet implemented for this size REAL"
#endif

#endif /*__FRCDIVF__*/
