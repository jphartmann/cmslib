/* Dump storage on the terminal                                      */
/*                                John Hartmann 20 Jun 2011 17:45:05 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <cmsbase.h>
#include <string.h>
#include <ctype.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

void
__dump(const void * p, int bytes)
{
   char bfr[256];
   char xla[17];
   const unsigned char * s=p;

   xla[16]=0;
   while (0<bytes)
   {
      int done = sprintf(bfr, "%8p ", s);
      int i, j;

      memset(xla, ' ', 16);
      for (i=0; 4>i; i++)
      {
         for (j=0; 4>j; j++)
         {
            if (0<bytes--)
            {
               xla[i*4+j] = isprint(*s) ? *s : '.';
               done += sprintf(bfr+done, "%02X", *s++);
            }
            else done += sprintf(bfr+done, "  ");
         }
         bfr[done++]=' ';
      }
      done += sprintf(bfr+done, "*%s*", xla);
      __say(bfr, done);
   }
}
