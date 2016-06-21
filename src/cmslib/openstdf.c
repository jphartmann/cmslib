/* Open standard file descriptors 0..2                               */
/*                                John Hartmann 11 May 2014 11:22:55 */

/*********************************************************************/
/* Open  the default standard files so we can freopen them later for */
/* redirect.   Called  from  __go390 and from stack allocate, if the */
/* standard files are used.                                          */
/*                                                                   */
/* Change activity:                                                  */
/*11 May 2014  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <stdio.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

void
__opnstd(struct _cmsthreadglobal * gbl)
{
   int i;

#if 0
   __WERROR("numfds %d uf %p", gbl->numfds, gbl->userFiles);
#endif

   for (i=0; 3>i; i++)
   {
      FILE * f;

      /* This  cannot  fail.   And if it does we have no alternative */
      /* action.                                                     */
      f = fopen("*", (i ? "a" : "r"));
      if (f) f->stdfile = 1;          /* Never let go                */
      else
         __WERROR("Cannot open %d eno %d rsn %d %s",
            i, gbl->errno, gbl->errno_reason, gbl->errno_message);
   }
}
