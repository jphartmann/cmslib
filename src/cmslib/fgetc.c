/* Read a character from a text file.                                */
/*                                John Hartmann 20 Jan 2015 10:53:16 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
fgetc(FILE * f)
{
   char c;
   size_t rv;

   if (f->eofInd || f->errorInd) return EOF;
   rv = fread(&c, 1, 1, f);
   if (1 == rv) return c;
   return EOF;
}
