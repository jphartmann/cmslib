/* Open a file stream                                                */
/*                                John Hartmann 11 Feb 2015 13:40:01 */

/*********************************************************************/
/* FILE *fopen(const char *path, const char *mode);                  */
/*                                                                   */
/* Change activity:                                                  */
/*11 Feb 2015  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <stdio.h>
#include <fcntl.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

FILE *
fopen(const char * __restrict path, const char * __restrict mode)
{
   int oflgs;
   int len;
   int rv;
   int fd;
   struct __file * f;

   rv = __decofl(mode, &oflgs, &len);
   if (rv) return NULL;

   fd = open(path, oflgs, mode + len);
   if (-1 == fd) return 0;

   f = _getfile(fd, -1);
   return f;
}
