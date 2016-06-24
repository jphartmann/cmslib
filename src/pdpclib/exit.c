/* exit()                                                            */
/*                                John Hartmann 24 Jun 2016 12:13:47 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdlib.h"
#include "stdio.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ void exit(int status)
{
   int i;
#if defined(__ZVM__)
   #define exiting (__getgbl()->exiting)
#else
   static int exiting;
#endif

   if (exiting) __exit(status);
   exiting = 1;                       /* Prevent recursions          */

   for (i=0; __NATEXIT > i; i++)
      if (__userExit[i]) __userExit[i]();

   for (i=0; __NFILE > i; i++)
      if (__userFiles[i]) fclose(__userFiles[i]);

   __exit(status);
}
