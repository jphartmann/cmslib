/*                                                                   */
/*                                 John Hartmann 8 Jun 2011 09:47:53 */

/*********************************************************************/
/* Change activity:                                                  */
/* 8 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_TIME_H)
   #define _JPH_TIME_H

#include <sys/types.h>
#include <stddef.h>
struct timeval
{
   time_t tv_sec;
   int tv_usec;      /* Signed for timersub to work, if nothing else */
};

struct timezone
{
   int tz_minuteswest;                /* minutes west of Greenwich   */
   int tz_dsttime;                    /* type of DST correction      */
};

extern int gettimeofday(struct timeval *tv, struct timezone *tz);

#define timeradd(a, b, r)                                              \
   (r)->tv_sec = (a)->tv_sec + (b)->tv_sec;                            \
   if (1000000 >= ((r)->tv_usec = (a)->tv_usec + (b)->tv_usec))        \
   { ((r)->tv_sec)++; ((r)->tv_usec-=1000000); }

#define timersub(a, b, r)                                              \
   (r)->tv_sec = (a)->tv_sec - (b)->tv_sec;                            \
   if (0 > ((r)->tv_usec = (a)->tv_usec - (b)->tv_usec))               \
   { ((r)->tv_sec)--; ((r)->tv_usec+=1000000); }

#endif
