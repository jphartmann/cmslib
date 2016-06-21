/* Close a file                                                      */
/*                                John Hartmann 20 Jan 2015 11:27:02 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>

int
fclose(FILE *fp)
{
   int rv;

   #if 0
   __sayf("fclose %d %d ", fileno(fp), fp->fd);
   #endif
   /* close does the flush; no need to do it twice                   */
   rv = fp->errorInd;
   close(fp->fd);
   return rv;
}
