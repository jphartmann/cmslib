/* VM-specific remove()                                              */
/*                                 John Hartmann 1 Jul 2011 12:10:40 */

/*********************************************************************/
/* Change activity:                                                  */
/* 1 Jul 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <errno.h>

#include <cmsbase.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
remove(const char * fn)
{
   __sayf("Remove called.");
   errno = ENOENT;
   return -1;
}
