/* Realtime clock                                                    */
/*                                John Hartmann 29 Jul 2011 09:14:05 */

/*********************************************************************/
/* Change activity:                                                  */
/*29 Jul 2011  New module.                                           */
/*********************************************************************/

#include <time.h>
#include <diagnose.h>
#include <errno.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
_clkgett(clockid_t clk_id, struct timespec *tp)
{
   struct diag00c pt;

   switch (clk_id)
   {
      case CLOCK_REALTIME:           /* System-wide real-time clock. */
         break;
      case CLOCK_MONOTONIC:
         break;
      case CLOCK_MONOTONIC_RAW: /* (since Linux 2.6.28; Linux-specific) */
         break;
      case CLOCK_PROCESS_CPUTIME_ID: /* High-resolution per-process timer from the CPU. */
         _diag00c(&pt, 1);
         tp->tv_sec = pt.virtcpu.tv.tv_sec;
         tp->tv_nsec = 1000 * pt.virtcpu.tv.tv_usec;
         return 0;
      case CLOCK_THREAD_CPUTIME_ID:   /* Thread-speci                */
         break;
   }
   errno = EINVAL;
   return -1;
}
