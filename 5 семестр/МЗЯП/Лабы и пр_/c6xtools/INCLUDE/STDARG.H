/*****************************************************************************/
/* stdarg.h   v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _STDARG
#define _STDARG

typedef char *va_list;
 
/********************************************************************/
/* WARNING - va_arg will not work for "float" type, must use double */
/* ALSO NOTE THAT DOUBLES MUST BE DOUBLE WORD ALIGNED               */
/********************************************************************/
#define va_end(_ap)
  
#define va_start(_ap, _parmN) \
         (_ap = ((char *)&(_parmN)) + (sizeof(_parmN) < 4 ? 4 : sizeof(_parmN)))

#ifdef _TMS320C6200
#define va_arg(_ap, _type)                                       \
         (sizeof(_type) == sizeof(double)                        \
             ? ((_ap += 8), (*(_type *)(_ap - 8)))               \
	     : ((_ap += 4), (*(_type *)(_ap - 4))))
#else
#define va_arg(_ap, _type)                                       \
         ((sizeof(_type) == sizeof(double)                       \
             ? ((_ap = (void *)(((int)_ap + 7) & ~7)),           \
	        (_ap += 8), (*(_type *)(_ap - 8)))               \
	     : ((_ap += 4), (*(_type *)(_ap - 4)))))
#endif

#endif
