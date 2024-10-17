/*****************************************************************************/
/* string.h   v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _STRING
#define _STRING
 
#ifndef NULL
#define NULL 0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef _INLINE 
#define __INLINE static inline
#else
#define __INLINE
#endif

__INLINE size_t  strlen(const char *_string);
__INLINE char   *strcpy(char *_dest, const char *_src);
__INLINE char   *strncpy(char *_to, const char *_from, size_t _n);
__INLINE char   *strcat(char *_string1, const char *_string2);
__INLINE char   *strncat(char *_to, const char *_from, size_t _n);
__INLINE char   *strchr(const char *_string, int _c);
__INLINE char   *strrchr(const char *_string, int _c);
__INLINE int     strcmp(const char *_string1, const char *_string2);
__INLINE int     strncmp(const char *_string1, const char *_string2, size_t _n);
        
         int     strcoll(const char *_string1, const char *_string2);
         size_t  strxfrm(char *_to, const char *_from, size_t _n);
         char   *strpbrk(const char *_string, const char *_chs);
         size_t  strspn(const char *_string, const char *_chs);
         size_t  strcspn(const char *_string, const char *_chs);
         char   *strstr(const char *_string1, const char *_string2);
         char   *strtok(char *_str1, const char *_str2);
         char   *strerror(int _errno);
        
         void   *memmove(void *_s1, const void *_s2, size_t _n);
	 void   *memcpy(void *_s1, const void *_s2, size_t _n);
__INLINE int     memcmp(const void *_cs, const void *_ct, size_t _n);
__INLINE void   *memchr(const void *_cs, int _c, size_t _n);
__INLINE void   *memset(void *_mem, int _ch, size_t _n);

#ifdef _INLINE

/****************************************************************************/
/*  strlen                                                                  */
/****************************************************************************/
static inline size_t strlen(const char *string)
{
   size_t      n = -1;
   const char *s = string - 1;

   do n++; while (*++s);
   return n;
}

/****************************************************************************/
/*  strcpy                                                                  */
/****************************************************************************/
static inline char *strcpy(char *dest, const char *src)
{
   register char       *d = dest - 1;
   register const char *s = src  - 1;

   while (*++d = *++s);
   return dest;
}

/****************************************************************************/
/*  strncpy                                                                 */
/****************************************************************************/
static inline char *strncpy(char *dest, const char *src, size_t n)
{
    if (n)
    {
	char       *d = dest - 1;
	const char *s = src  - 1;

	while ((*++d = *++s) && --n);              /* COPY STRING         */
	if (n-- > 1) do *++d = '\0'; while (--n);  /* TERMINATION PADDING */
    }
    return dest;
}

/****************************************************************************/
/*  strcat                                                                  */
/****************************************************************************/
static inline char *strcat(char *string1, const char *string2)
{
    char       *s1 = string1 - 1;
    const char *s2 = string2 - 1;

    while (*++s1);                     /* FIND END OF STRING   */
    s1--;                              /* BACK UP OVER NULL    */
    while (*++s1 = *++s2);             /* APPEND SECOND STRING */
    return string1;
}

/****************************************************************************/
/*  strncat                                                                 */
/****************************************************************************/
static inline char *strncat(char *dest, const char *src, size_t n)
{
    if (n) 
    {
	char       *d = dest - 1;
	const char *s = src  - 1;

	while (*++d);                    /* FIND END OF STRING   */
	d--;                             /* BACK UP OVER NULL    */
	while ((*++d = *++s) && --n);    /* APPEND SECOND STRING */
	*++d = 0;
    }
    return dest;
}

/****************************************************************************/
/*  strchr                                                                  */
/****************************************************************************/
static inline char *strchr(const char *string, int c)
{
    char        tch, ch = c;
    const char *s       = (char *) string - 1;

    for (;;)
    {
	if ((tch = *++s) == ch) return (char *) s;
	if (!tch)               return (char *) 0;
    }
}

/****************************************************************************/
/*  strrchr                                                                 */
/****************************************************************************/
static inline char *strrchr(const char *string, int c)
{
   char        tch, ch = c;
   char       *result  = 0;
   const char *s       = string - 1;

   for (;;)
   {
      if ((tch = *++s) == ch) result = (char *) s;
      if (!tch) break;
   }

   return result;
}

/****************************************************************************/
/*  strcmp                                                                  */
/****************************************************************************/
static inline int strcmp(const char *string1, const char *string2)
{
   const char *s1 = string1 - 1;
   const char *s2 = string2 - 1;
   char        cp1;
   char        cp2;

   while (((cp1 = *++s1) == (cp2 = *++s2)) && cp1);
   return cp1 - cp2;
}

/****************************************************************************/
/*  strncmp                                                                 */
/****************************************************************************/
static inline int strncmp(const char *string1, const char *string2, size_t n)
{
     if (n) 
     {
	 const char *s1 = string1 - 1;
	 const char *s2 = string2 - 1;
	 char        cp;
	 int         result;

	 do 
	    if (result = *++s1 - (cp = *++s2)) return result;
	 while (cp && --n);
     }
     return 0;
}

/****************************************************************************/
/*  memcmp      							    */
/****************************************************************************/
static inline int memcmp(const void *cs, const void *ct, size_t n)
{
    if (n)
    {
	const unsigned char *mem1 = (unsigned char *)cs - 1;
	const unsigned char *mem2 = (unsigned char *)ct - 1;
	int                  cp;
	
	while ((cp = *++mem1) == *++mem2 && --n);
	return cp - *mem2;
    }
    return 0;
}

/****************************************************************************/
/*  memchr                                                                  */
/****************************************************************************/
static inline void *memchr(const void *cs, int c, size_t n)
{
    if (n)
    {
	const unsigned char *mem = (unsigned char *)cs - 1;
	unsigned char        ch  = c;

	do if ( *++mem == ch ) return (void *)mem;
	while (--n);
    }
    return NULL;
}

/****************************************************************************/
/*  memset                                                                  */
/****************************************************************************/
static inline void *memset(void *s, int c, size_t n)
{
    register char *m = (char *)s - 1;

    while (n--) *++m = c;
    return s;
}

#endif

#undef __INLINE

#endif

