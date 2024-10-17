/*****************************************************************************/
/* assert.h   v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _ASSERT
#define _ASSERT

void _nassert(int), _assert(int, char *);
void _abort_msg(char *);

#define _STR(x)  __STR(x)
#define __STR(x) #x

#if defined(NDEBUG)
#define assert(_ignore) ((void)0)

#elif defined(NASSERT)
#define assert(_expr)   _nassert(_expr)

#else
#define assert(_expr)   _assert((_expr),                                   \
                   "Assertion failed, (" _STR(_expr) "), file " __FILE__ \
		   ", line " _STR(__LINE__) "\n")
#endif
#endif

