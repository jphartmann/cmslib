/* Get resourceusage from diag C                                    */
/*                                 John Hartmann 1 Jul 2011 12:27:02 */

/*********************************************************************/
/* Change activity:                                                  */
/* 1 Jul 2011  New module.                                           */
/*********************************************************************/

#include <sys/time.h>
#include <sys/resource.h>
#include <cmsbase.h>
#include <diagnose.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
getrusage(int who, struct rusage *usage)
{
   struct diag00c bfr;

   _diag00c(&bfr, 1);
   usage -> ru_utime = bfr.virtcpu.tv;
   usage -> ru_stime = bfr.totcpu.tv;
   usage->ru_stime.tv_usec -= usage->ru_utime.tv_usec;
   if (0>usage->ru_stime.tv_usec)
   {
      usage->ru_stime.tv_usec += 1000000;
      usage->ru_stime.tv_sec--;
   }
   usage->ru_stime.tv_sec -= usage->ru_utime.tv_usec;
   return 0;
};
