/*  Associate a file with an open file descriptor.                   */
/*                                John Hartmann 11 Feb 2015 13:40:13 */

/*********************************************************************/
/* FILE *fdopen(int fd, const char *mode);                           */
/*                                                                   */
/* In  UNIX  this  builds the userland FILE structure, but since the */
/* open  file  has  one  already, all we have to do is to decode the */
/* access  flags and obtain the file handle for the file descriptor; */
/* this checks that the access mode is OK.                           */
/*                                                                   */
/* Change activity:                                                  */
/*11 Feb 2015  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <stdio.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

FILE *
fdopen(int fd, const char *__restrict mode)
{
   int oflgs;
   int rv;
   struct __file * f;

   rv = __decofl(mode, &oflgs, 0);
   if (rv) return NULL;

   f = _getfile(fd, oflgs);

   return f;
}
