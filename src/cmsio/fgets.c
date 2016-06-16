/* Read a line from a text file.                                     */
/*                                John Hartmann 20 Jan 2015 10:51:20 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

char *
fgets(char *s, const int n, FILE *stream)
{
   int i;

   for (i=0; n-1>i; )
   {
      int c=fgetc(stream);

      if (EOF==c) break;
      s[i++]=c;
      if ('\n' == c) break;
   }
   s[i]=0;

   return i && 0 == ferror(stream) ? s : NULL;
}
