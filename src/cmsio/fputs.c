/* Write a string to a file                                          */
/*                                John Hartmann 20 Jan 2015 10:54:24 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
fputs(const char * s, FILE * f)
{
   int rv;
   const size_t len = strlen(s);

   rv = write(fileno(f), s, len);
   if (-1 == rv)
      __WERROR("Cannot write %zd bytes bsize %zd to fd %d:  %m",
         len, f->buffersize, f->fd);

   return f->errorInd ? EOF : 1;
}
