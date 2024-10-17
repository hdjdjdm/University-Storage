/*****************************************************************************/
/* ctype.h    v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

/************************************************************************/
/*                                                                      */
/*  CHARACTER TYPING FUNCTIONS AND MACROS                               */
/*                                                                      */
/*  Note that in this implementation, either macros or functions may    */
/*  be used.  Macros are prefixed with an underscore.                   */
/*                                                                      */
/************************************************************************/
#ifndef _CTYPE
#define _CTYPE

extern unsigned char _ctypes_[];

#ifdef _INLINE
#define __INLINE static inline
#else
#define __INLINE
#endif

/************************************************************************/
/*   FUNCTION DEFINITIONS                                               */
/************************************************************************/
__INLINE int isalnum(int _c);
__INLINE int isalpha(int _c);
__INLINE int iscntrl(int _c);
__INLINE int isdigit(int _c);
__INLINE int isgraph(int _c);
__INLINE int islower(int _c);
__INLINE int isprint(int _c);
__INLINE int ispunct(int _c);
__INLINE int isspace(int _c);
__INLINE int isupper(int _c);
__INLINE int isxdigit(int _c);
__INLINE int isascii(int _c);

__INLINE int toupper(int _c);
__INLINE int tolower(int _c);
__INLINE int toascii(int _c);

/************************************************************************/
/*  MACRO DEFINITIONS                                                   */
/************************************************************************/
#define _U_   0x01
#define _L_   0x02
#define _N_   0x04
#define _S_   0x08
#define _P_   0x10
#define _C_   0x20
#define _H_   0x40
#define _B_   0x80

#define _isalnum(a)  (_ctypes_[(a)+1] & (_U_ | _L_ | _N_))
#define _isalpha(a)  (_ctypes_[(a)+1] & (_U_ | _L_))
#define _iscntrl(a)  (_ctypes_[(a)+1] & _C_)
#define _isdigit(a)  (_ctypes_[(a)+1] & _N_)
#define _isgraph(a)  (_ctypes_[(a)+1] & (_U_ | _L_ | _N_ | _P_))
#define _islower(a)  (_ctypes_[(a)+1] & _L_)
#define _isprint(a)  (_ctypes_[(a)+1] & (_B_ | _U_ | _L_ | _N_ | _P_))
#define _ispunct(a)  (_ctypes_[(a)+1] & _P_)
#define _isspace(a)  (_ctypes_[(a)+1] & _S_)
#define _isupper(a)  (_ctypes_[(a)+1] & _U_)
#define _isxdigit(a) (_ctypes_[(a)+1] & _H_)
#define _isascii(a)  (((a) & ~0x7F) == 0)

#define _toupper(b)  ((_islower(b)) ? (b) - ('a' - 'A') : (b))
#define _tolower(b)  ((_isupper(b)) ? (b) + ('a' - 'A') : (b))
#define _toascii(a)  ((a) & 0x7F)

#ifdef _INLINE
static inline int isalnum(int c)  { return(_isalnum(c)); }
static inline int isalpha(int c)  { return(_isalpha(c)); }
static inline int isascii(int c)  { return(_isascii(c)); }
static inline int iscntrl(int c)  { return(_iscntrl(c)); }
static inline int isdigit(int c)  { return(_isdigit(c)); }
static inline int isgraph(int c)  { return(_isgraph(c)); }
static inline int islower(int c)  { return(_islower(c)); }
static inline int isprint(int c)  { return(_isprint(c)); }
static inline int ispunct(int c)  { return(_ispunct(c)); }
static inline int isspace(int c)  { return(_isspace(c)); }
static inline int isupper(int c)  { return(_isupper(c)); }
static inline int isxdigit(int c) { return(_isxdigit(c));}
static inline int toascii(int c)  { return(_toascii(c)); }

/****************************************************************************/
/*  tolower                                                                 */
/****************************************************************************/
static inline int tolower(int ch)
{
   /*
    This code depends on two assumptions: (1) all of the letters of the
    alphabet of a given case are contiguous, and (2) the lower and upper
    case forms of each letter are displaced from each other by the same
    constant value.
   */

   if ( (unsigned int)(ch - 'A') <= (unsigned int)('Z' - 'A')) ch += 'a' - 'A';
   return ch;
}

/****************************************************************************/
/*  toupper                                                                 */
/****************************************************************************/
static inline int toupper(int ch)
{
   /*
    This code depends on two assumptions: (1) all of the letters of the
    alphabet of a given case are contiguous, and (2) the lower and upper
    case forms of each letter are displaced from each other by the same
    constant value.
   */

   if ( (unsigned int)(ch - 'a') <= (unsigned int)('z' - 'a')) ch -= 'a' - 'A';
   return ch;
}

#endif
#undef __INLINE

#endif
