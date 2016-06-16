/* Seek to specified position                                        */
/*                                John Hartmann 20 Jan 2015 10:58:57 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <errno.h>

int
fseek(FILE * f, long offset, int whence)
{
   __WERROR("FIXME:  Implement ftell");
   errno = EINVAL;
   return -1;
}
