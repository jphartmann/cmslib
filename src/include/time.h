/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  time.h - time header file.                                       */
/*                                                                   */
/*********************************************************************/

#ifndef __TIME_INCLUDED
#define __TIME_INCLUDED

#include <stddef.h>

#define CLOCKS_PER_SEC 1000
#define NULL ((void *)0)

typedef unsigned int clock_t;

struct timespec
{
   time_t   tv_sec;                   /* seconds                     */
   long     tv_nsec;                  /* nanoseconds                 */
};

typedef enum __clockid
{
   CLOCK_REALTIME,                   /* System-wide real-time clock. */
   CLOCK_MONOTONIC,
   CLOCK_MONOTONIC_RAW,      /* (since Linux 2.6.28; Linux-specific) */
   CLOCK_PROCESS_CPUTIME_ID, /* High-resolution per-process timer from the CPU. */
   CLOCK_THREAD_CPUTIME_ID,           /* Thread-speci                */
} clockid_t;

extern int _clkgett(clockid_t clk_id, struct timespec *tp);
#define clock_gettime _clkgett

struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

time_t time(time_t *timer);
clock_t clock(void);
double difftime(time_t time1, time_t time0);
time_t mktime(struct tm *timeptr);
char *asctime(const struct tm *timeptr);
char *ctime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
size_t strftime(char *s, size_t maxsize,
                const char *format, const struct tm *timeptr);
extern long __pkts2t(unsigned char * day, unsigned char * time);

#endif
