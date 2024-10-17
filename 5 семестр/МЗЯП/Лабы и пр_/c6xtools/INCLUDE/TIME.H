/*****************************************************************************/
/* time.h     v1.10#                                                         */
/* Copyright (c) 1993-1997 Texas Instruments Incorporated                    */
/*****************************************************************************/

#ifndef _TIME
#define _TIME

#define CLOCKS_PER_SEC 200000000 /* 200 MHz */
#ifndef NULL
#define NULL      0
#endif

#if defined(_TMS320C6X)
typedef unsigned int clock_t;
typedef unsigned int time_t;
#else
typedef unsigned long clock_t;
typedef unsigned long time_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

struct tm {
	    unsigned int tm_sec;      /* seconds after the minute   - [0,59]  */
	    int          tm_min;      /* minutes after the hour     - [0,59]  */
	    int          tm_hour;     /* hours after the midnight   - [0,23]  */
	    int          tm_mday;     /* day of the month           - [1,31]  */
	    int          tm_mon;      /* months since January       - [0,11]  */
	    int          tm_year;     /* years since 1900                     */
	    int          tm_wday;     /* days since Sunday          - [0,6]   */
	    int          tm_yday;     /* days since Jan 1st         - [0,365] */
	    int          tm_isdst;    /* Daylight Savings Time flag           */
	  };

/*************************************************************************/
/* TIME ZONE STRUCTURE DEFINITION                                        */
/*************************************************************************/
typedef struct {
                 short   daylight;
		 time_t  timezone;
		 char    tzname[4];
		 char    dstname[4];
               } TZ;
extern TZ _tz;

#ifdef _INLINE
#define __INLINE static inline
#else
#define __INLINE
#endif

/****************************************************************************/
/* FUNCTION DECLARATIONS.  (NOTE : clock AND time ARE SYSTEM SPECIFIC)      */
/****************************************************************************/
         clock_t    clock(void);             
         time_t     time(time_t *_timer);   

         time_t     mktime(struct tm *_tptr);
         double     difftime(time_t _time1, time_t _time0);
__INLINE char      *ctime(const time_t *_timer);
         char      *asctime(const struct tm *_timeptr);
         struct tm *gmtime(const time_t *_timer);
         struct tm *localtime(const time_t *_timer);
         size_t     strftime(char *_out, size_t _maxsize, const char *_format,
                             const struct tm *_timeptr);

#ifdef _INLINE

/****************************************************************************/
/*  ctime                                                                   */
/****************************************************************************/
static inline char *ctime(const time_t *timer)
{
   return(asctime(localtime(timer)));
}

#endif
#undef __INLINE

#endif

