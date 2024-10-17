/*****************************************************************************/
/* stddef.h   v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _STDDEF
#define _STDDEF

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef int ptrdiff_t;

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif

#define offsetof(_type, _ident) ((size_t)(&((_type *)0)->_ident))

#endif

