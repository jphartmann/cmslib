/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  time.c - implementation of stuff in time.h                       */
/*                                                                   */
/*********************************************************************/

#include "time.h"
#include "stdarg.h"
#include "stdio.h"
#include "stddef.h"
#include <string.h>

/* just get VSE to use MVS for now */
#if defined(__VSE__)
#define __MVS__ 1
#endif

/* pdos and msdos use the same interface most of the time) */
#if defined(__PDOS__) && !defined(__MVS__)
#define __MSDOS__
#endif

#if defined(__ZVM__)
   #include <linerd.h>
   #include <diagnose.h>

/* Forward declarations:                                             */
static int gettimezoneoffset(void);
static void gettimezone(void);
/* End of forward declarations.                                      */

#elif defined(__MVS__) || defined(__CMS__)
#include "mvssupa.h"
#endif
#ifdef __OS2__
#include <os2.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif
#ifdef __MSDOS__
#ifdef __WATCOMC__
#define CTYP __cdecl
#else
#define CTYP
#endif
void CTYP __datetime(void *ptr);
#endif

#ifdef __gnu_linux__
unsigned long __time(unsigned long *);
#endif

static char *aday[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static char *day[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

static char *amonth[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static char *month[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

static char *__tzname[2] = { "" "" };

/* scalar date routines    --    public domain by Ray Gardner
** These will work over the range 1-01-01 thru 14699-12-31
** The functions written by Ray are isleap, months_to_days,
** years_to_days, ymd_to_scalar, scalar_to_ymd.
** modified slightly by Paul Edwards
*/

static int isleap(unsigned yr)
{
   return yr % 400 == 0 || (yr % 4 == 0 && yr % 100 != 0);
}

static unsigned months_to_days(unsigned month)
{
   return (month * 3057 - 3007) / 100;
}

static long years_to_days (unsigned yr)
{
   return yr * 365L + yr / 4 - yr / 100 + yr / 400;
}

static long ymd_to_scalar(unsigned yr, unsigned mo, unsigned day)
{
   long scalar;

   scalar = day + months_to_days(mo);
   if ( mo > 2 )                         /* adjust if past February */
      scalar -= isleap(yr) ? 1 : 2;
   yr--;
   scalar += years_to_days(yr);
   return (scalar);
}

/*********************************************************************/
/* Convert  a  4-byte  packed yyyymmdd and hhmmss to a seconds since */
/* the 1970 epoch.                                                   */
/*********************************************************************/

long
__pkts2t(unsigned char * day, unsigned char * time)
{
   long tv;
   static long epoch;

   int p2i(char b)
   {
      return ((0xf0 & b)>>4)*10 + (0xf & b);
   }

   if (!epoch) epoch=ymd_to_scalar(1970, 1, 1);

   tv = ymd_to_scalar(p2i(day[0])*100+p2i(day[1]), p2i(day[2]), p2i(day[3]));
   tv -= epoch;
   tv *= 86400;
   tv += (p2i(time[0])*60+p2i(time[1]))*60+p2i(time[2]);
   return tv;
}

static void scalar_to_ymd(long scalar,
                          unsigned *pyr,
                          unsigned *pmo,
                          unsigned *pday)
{
   unsigned n;                /* compute inverse of years_to_days() */

   n = (unsigned)((scalar * 400L) / 146097L);
   while (years_to_days(n) < scalar)
   {
      n++;
   }
   for ( n = (unsigned)((scalar * 400L) / 146097L); years_to_days(n) < scalar; )
      n++;                          /* 146097 == years_to_days(400) */
   *pyr = n;
   n = (unsigned)(scalar - years_to_days(n-1));
   if ( n > 59 ) {                       /* adjust if past February */
      n += 2;
      if ( isleap(*pyr) )
         n -= n > 62 ? 1 : 2;
   }
   *pmo = (n * 100 + 3007) / 3057;  /* inverse of months_to_days() */
   *pday = n - months_to_days(*pmo);
   return;
}

__PDPCLIB_API__ time_t time(time_t *timer)
{
    time_t tt;
#ifdef __OS2__
    DATETIME dt;
    APIRET rc;
#endif
#ifdef __WIN32__
    SYSTEMTIME dt;
#endif
#if defined(__MSDOS__)
    struct {
        int year;
        int month;
        int day;
        int hours;
        int minutes;
        int seconds;
        int hundredths;
    } dt;
#endif
#if defined(__MVS__) || defined(__CMS__)
#if !defined(__ZVM__)
    unsigned int clk[2];
#endif
#endif

#ifdef __OS2__
    rc = DosGetDateTime(&dt);
    if (rc != 0)
    {
        tt = (time_t)-1;
    }
    else
#endif
#ifdef __WIN32__
    GetSystemTime(&dt);
    tt = ymd_to_scalar(dt.wYear, dt.wMonth, dt.wDay)
         - ymd_to_scalar(1970, 1, 1);
    tt = tt * 24 + dt.wHour;
    tt = tt * 60 + dt.wMinute;
    tt = tt * 60 + dt.wSecond;
#endif
#if defined(__MSDOS__)
    __datetime(&dt);
#endif

#if defined(__ZVM__)
   {
      struct timeval tv;

      __timev(&tv);
      tt=tv.tv_sec;
   }
#elif defined(__MVS__) || defined(__CMS__)
    tt = __getclk(clk);
#elif defined(__gnu_linux__)
    tt = __time(NULL);
#elif !defined(__WIN32__)

    {
        tt = ymd_to_scalar(dt.year, dt.month, dt.day)
             - ymd_to_scalar(1970, 1, 1);
        tt = tt * 24 + dt.hours;
        tt = tt * 60 + dt.minutes;
        tt = tt * 60 + dt.seconds;
    }
#endif
    if (timer != NULL)
    {
        *timer = tt;
    }
    return (tt);
}

__PDPCLIB_API__ clock_t clock(void)
{
    return ((clock_t)-1);
}

__PDPCLIB_API__ double difftime(time_t time1, time_t time0)
{
    return ((double)(time1 - time0));
}

__PDPCLIB_API__ time_t mktime(struct tm *timeptr)
{
    time_t tt;

    if ((timeptr->tm_year < 70) || (timeptr->tm_year > 120))
    {
        tt = (time_t)-1;
    }
    else
    {
        tt = ymd_to_scalar(timeptr->tm_year + 1900,
                           timeptr->tm_mon + 1,
                           timeptr->tm_mday)
             - ymd_to_scalar(1970, 1, 1);
        tt = tt * 24 + timeptr->tm_hour;
        tt = tt * 60 + timeptr->tm_min;
        tt = tt * 60 + timeptr->tm_sec;
    }
    *timeptr = *gmtime(&tt);
    return (tt);
}

__PDPCLIB_API__ char *asctime(const struct tm *timeptr)
{
   #if 0
These initialisers are four bytes.  It simply doesnt work
    static const char wday_name[7][3] = {
          "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const char mon_name[12][3] = {
          "Jan", "Feb", "Mar", "Apr", "May", "Jun",
          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
   #endif
    static char result[26];

    sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
          aday[timeptr->tm_wday],
          amonth[timeptr->tm_mon],
          timeptr->tm_mday, timeptr->tm_hour,
          timeptr->tm_min, timeptr->tm_sec,
          1900 + timeptr->tm_year);
    return result;
}

__PDPCLIB_API__ char *ctime(const time_t *timer)
{
    return (asctime(localtime(timer)));
}

__PDPCLIB_API__ struct tm *
localtime(const time_t *timer)
{
#ifdef __MVS__
    time_t t;
    int o;
    int r;

    t = *timer;
    o = __gettz(); /* this function returns the local timezone
                      offset in 1.048576 second increments. The
                      maximum offset people have managed to define
                      is 14 hours (Kirribati) and when mulplied
                      by 16384, this doesn't exceed a 32-bit
                      signed integer, so we're safe.

                      Note that we have to take care of rounding
                      on top of that too though. */
    o = o * 16384;
    r = o % 15625;
    o /= 15625;
    if ((o > 0) && (r > 7812))
    {
        o++;
    }
    else if ((o < 0) && (r < -7812))
    {
        o--;
    }
    t += o;
    return (gmtime(&t));
#elif defined(__ZVM__)
   time_t t = *timer;


   t+=gettimezoneoffset();
   return (gmtime(&t));

#else
    return (gmtime(timer));
#endif
}

/* dow - written by Paul Edwards, 1993-01-31 */
/* Released to the Public Domain */
/* This routine will work over the range 1-01-01 to 32767-12-31.
   It assumes the current calendar system has always been in
   place in that time.  If you pass 0 or negative years, then
   it produces results on the assumption that there is a year
   0.  It should always produce a value in the range of 0..6
   if a valid month and day have been passed, no matter what
   the year is.  However, it has not been tested for negative
   years, because the results are meaningless anyway.  It is
   mainly to stop people playing silly buggers and causing
   the macro to crash on negative years. */

#define dow(y,m,d) \
  ((((((m)+9)%12+1)<<4)%27 + (d) + 1 + \
  ((y)%400+400) + ((y)%400+400)/4 - ((y)%400+400)/100 + \
  (((m)<=2) ? ( \
  (((((y)%4)==0) && (((y)%100)!=0)) || (((y)%400)==0)) \
  ? 5 : 6) : 0)) % 7)

static struct tm tms;

__PDPCLIB_API__ struct tm *gmtime(const time_t *timer)
{
    unsigned yr, mo, da;
    unsigned long secs;
    unsigned long days;

    days = *timer / (60L*60*24);
    secs = *timer % (60L*60*24);
    scalar_to_ymd(days + ymd_to_scalar(1970, 1, 1), &yr, &mo, &da);
    tms.tm_year = yr - 1900;
    tms.tm_mon = mo - 1;
    tms.tm_mday = da;
    tms.tm_yday = (int)(ymd_to_scalar(tms.tm_year + 1900, mo, da)
                  - ymd_to_scalar(tms.tm_year + 1900, 1, 1));
    tms.tm_wday = dow(tms.tm_year + 1900, mo, da);
    tms.tm_isdst = -1;
    tms.tm_sec = (int)(secs % 60);
    secs /= 60;
    tms.tm_min = (int)(secs % 60);
    secs /= 60;
    tms.tm_hour = (int)secs;
    return (&tms);
}

/*
 * strftime.c
 *
 * implements the iso c function strftime()
 *
 * written 1989-09-06 by jim nutt
 * released into the public domain by jim nutt
 *
 * modified 1989-10-21 by Rob Duff
 *
 * modified 1994-08-26 by Paul Edwards
 */
static char buf[26];

static void strfmt(char *str, const char *fmt, ...);

/**
 *
 * size_t strftime(char *str,
 *                 size_t maxs,
 *                 const char *fmt,
 *                 const struct tm *t)
 *
 *      this functions acts much like a sprintf for time/date output.
 *      given a pointer to an output buffer, a format string and a
 *      time, it copies the time to the output buffer formatted in
 *      accordance with the format string.  the parameters are used
 *      as follows:
 *
 *          str is a pointer to the output buffer, there should
 *          be at least maxs characters available at the address
 *          pointed to by str.
 *
 *          maxs is the maximum number of characters to be copied
 *          into the output buffer, included the '\0' terminator
 *
 *          fmt is the format string.  a percent sign (%) is used
 *          to indicate that the following character is a special
 *          format character.  the following are valid format
 *          characters:
 *
 *              %A      full weekday name (Monday)
 *              %a      abbreviated weekday name (Mon)
 *              %B      full month name (January)
 *              %b      abbreviated month name (Jan)
 *              %c      standard date and time representation
 *              %d      day-of-month (01-31)
 *              %H      hour (24 hour clock) (00-23)
 *              %I      hour (12 hour clock) (01-12)
 *              %j      day-of-year (001-366)
 *              %M      minute (00-59)
 *              %m      month (01-12)
 *              %p      local equivalent of AM or PM
 *              %S      second (00-59)
 *              %U      week-of-year, first day sunday (00-53)
 *              %W      week-of-year, first day monday (00-53)
 *              %w      weekday (0-6, sunday is 0)
 *              %X      standard time representation
 *              %x      standard date representation
 *              %Y      year with century
 *              %y      year without century (00-99)
 *              %Z      timezone name
 *              %%      percent sign
 *
 *      the standard date string is equivalent to:
 *
 *          %a %b %d %Y
 *
 *      the standard time string is equivalent to:
 *
 *          %H:%M:%S
 *
 *      the standard date and time string is equivalent to:
 *
 *          %a %b %d %H:%M:%S %Y
 *
 *      strftime returns the number of characters placed in the
 *      buffer, not including the terminating \0, or zero if more
 *      than maxs characters were produced.
 *
**/

__PDPCLIB_API__ size_t strftime(char *s,
                                size_t maxs,
                                const char *f,
                                const struct tm *t)
{
      int w;
      char *p, *q, *r;

      p = s;
      q = s + maxs - 1;
      while ((*f != '\0'))
      {
            if (*f++ == '%')
            {
                  r = buf;
                  switch (*f++)
                  {
                  case '%' :
                        r = "%";
                        break;

                  case 'a' :
                        r = aday[t->tm_wday];
                        break;

                  case 'A' :
                        r = day[t->tm_wday];
                        break;

                  case 'b' :
                        r = amonth[t->tm_mon];
                        break;

                  case 'B' :
                        r = month[t->tm_mon];
                        break;

                  case 'c' :
                        strfmt(r, "%0 %0 %2 %2:%2:%2 %4",
                              aday[t->tm_wday], amonth[t->tm_mon],
                              t->tm_mday,t->tm_hour, t->tm_min,
                              t->tm_sec, t->tm_year+1900);
                        break;

                  case 'd' :
                        strfmt(r,"%2",t->tm_mday);
                        break;

                  case 'H' :
                        strfmt(r,"%2",t->tm_hour);
                        break;

                  case 'I' :
                        strfmt(r,"%2",(t->tm_hour%12)?t->tm_hour%12:12);
                        break;

                  case 'j' :
                        strfmt(r,"%3",t->tm_yday+1);
                        break;

                  case 'm' :
                        strfmt(r,"%2",t->tm_mon+1);
                        break;

                  case 'M' :
                        strfmt(r,"%2",t->tm_min);
                        break;

                  case 'p' :
                        r = (t->tm_hour>11)?"PM":"AM";
                        break;

                  case 'S' :
                        strfmt(r,"%2",t->tm_sec);
                        break;

                  case 'T' :  /* 24-hour clock */
                        sprintf(r, "%2d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
                        break;

                  case 'U' :
                        w = t->tm_yday/7;
                        if (t->tm_yday%7 > t->tm_wday)
                              w++;
                        strfmt(r, "%2", w);
                        break;

                  case 'W' :
                        w = t->tm_yday/7;
                        if (t->tm_yday%7 > (t->tm_wday+6)%7)
                              w++;
                        strfmt(r, "%2", w);
                        break;

                  case 'w' :
                        strfmt(r,"%1",t->tm_wday);
                        break;

                  case 'x' :
                        strfmt(r, "%3s %3s %2 %4", aday[t->tm_wday],
                              amonth[t->tm_mon], t->tm_mday, t->tm_year+1900);
                        break;

                  case 'X' :
                        strfmt(r, "%2:%2:%2", t->tm_hour,
                              t->tm_min, t->tm_sec);
                        break;

                  case 'y' :
                        strfmt(r,"%2",t->tm_year%100);
                        break;

                  case 'Y' :
                        strfmt(r,"%4",t->tm_year+1900);
                        break;

                  case 'Z' :
                        #if defined(__ZVM__)
                           if (!__tzname[0][0]) gettimezone();
                        #endif
                        r = (t->tm_isdst) ? __tzname[1] : __tzname[0];
                        break;

                  default:
                        buf[0] = '%';     /* reconstruct the format */
                        buf[1] = f[-1];
                        buf[2] = '\0';
                        if (buf[1] == 0)
                              f--;        /* back up if at end of string */
                  }
                  while (*r)
                  {
                        if (p == q)
                        {
                              *q = '\0';
                              return 0;
                        }
                        *p++ = *r++;
                  }
            }
            else
            {
                  if (p == q)
                  {
                        *q = '\0';
                        return 0;
                  }
                  *p++ = f[-1];
            }
      }
      *p = '\0';
      return (size_t)(p - s);
}

static int pow[5] = { 1, 10, 100, 1000, 10000 };

/**
 * static void strfmt(char *str, char *fmt);
 *
 * simple sprintf for strftime
 *
 * each format descriptor is of the form %n
 * where n goes from zero to four
 *
 * 0    -- string %s
 * 1..4 -- int %?.?d
 *
**/

static void strfmt(char *str, const char *fmt, ...)
{
      int ival, ilen;
      char *sval;
      va_list vp;

      va_start(vp, fmt);
      while (*fmt)
      {
            if (*fmt++ == '%')
            {
                  ilen = *fmt++ - '0';
                  if (ilen == 0)                /* zero means string arg */
                  {
                        sval = va_arg(vp, char*);
                        while (*sval)
                              *str++ = *sval++;
                  }
                  else                          /* always leading zeros */
                  {
                        ival = va_arg(vp, int);
                        while (ilen)
                        {
                              ival %= pow[ilen--];
                              *str++ = (char)('0' + ival / pow[ilen]);
                        }
                  }
            }
            else  *str++ = fmt[-1];
      }
      *str = '\0';
      va_end(vp);
}

#if defined (__ZVM__)
#include <sys/time.h>
#include <errno.h>

int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
   if (tv)
   {
      __timev(tv);
   #if 0
      unsigned long long tod;
      long long sec;

      asm("stck %0" : "=Q" (tod) );
      tod>>=12;                       /* In microsecoonds            */
      tod-=(70*365 + 70/4)*86400ll*1000000;
      sec=tod;                        /* Make it signed              */
      sec/=1000000;
      tv->tv_sec=sec;
      sec=tod;
      tv->tv_usec=sec%1000000;
   #endif
   }
   if (tz)
   {
      tz->tz_minuteswest = -gettimezoneoffset();
      tz->tz_dsttime = -1;
   }
   return 0;
}

static int
gettimezoneoffset(void)
{
   static int haveoffset;
   static int gmtoffset;

   if (0==haveoffset)
   {
      struct diag000 diag0;

      _diag000(&diag0, sizeof(diag0));
      haveoffset=1;
      gmtoffset=diag0.timezoneoffset;
   }

   return gmtoffset;
}

static void
gettimezone(void)
{
   char plist[5][8];                  /* One more for slop           */
   int rv;
   int regs[2];
   char bfr[256];
   static char tz[5];

   sprintf(plist[0], "%-8s%-8s%-8s%-8.8s", "IDENTIFY", "(", "LIFO", FENCESTR);
   rv=__svc204(0, plist[0], 0xa000, NULL);

   if (rv) return;

   rv = linerd_stack(bfr, sizeof(bfr), regs);
   if (rv) return;

   memcpy(tz,bfr+52, 4);
   __tzname[0] = tz;
   __tzname[1] = tz;
}
#endif
