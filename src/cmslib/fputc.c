/* Print a single character                                          */
/*                                John Hartmann 17 Feb 2015 11:26:00 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Feb 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
fputc(int c, FILE * f)
{
   int rv;
   char ch = c;

   #if 0
   __WERROR("file %p fd %d %02x", f, fileno(f), c);
   #endif
   rv = fwrite(&ch, 1, 1, f);
   return -1 == rv ? EOF :c;
}
