/* Set error number and associated description.                      */
/*                                John Hartmann 11 Feb 2015 13:43:55 */

/*********************************************************************/
/* Change activity:                                                  */
/*11 Feb 2015  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <cmsbase.h>
#include <cmsthreadglobal.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
_seterr_(
   const int rv,                      /* Desired return value        */
   const int eno,                     /* errno                       */
   const int reason,                  /* Unique reason code          */
   const char * __restrict msg,       /* Message explaining trouble  */
   const char * __restrict object,    /* Object if any               */
   const char * fn,
   int line
   )
{
   struct _cmsthreadglobal * pt = __getgbl();

   if (!(_errno_hold & pt->flag2))
   {
      pt->errno = eno;
      pt->errno_reason = reason;
      pt->errno_message = msg;
   }
   else if (!(_errno_report_held & pt->flag2)) return rv;

   if (_errno_verbose & pt->flag2)
   {
      if (object)
         __sayf("%s(%d):  Setting errno %d (%m) for '%s' reason %d (%s)",
            fn, line, eno, object, reason, msg);
      else
         __sayf("%s(%d):  Setting errno %d (%m) reason %d (%s)",
            fn, line, eno, reason, msg);
   }
   if (_errno_traceback & pt->flag2) __traceb();

   return rv;
}
