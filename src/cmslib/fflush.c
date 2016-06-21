/* Flush buffered data to file                                       */
/*                                John Hartmann 20 Jan 2015 10:56:36 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>

int
fflush(FILE * f)
{
   int i;

   #if 0
   __sayf("flush %d", f ? fileno(f) : -1);
   __traceb();
   #endif
   if (f)
   {
      i = f->pac->flush(f);
      f->byteptr = 0;
      return -1 == i ? EOF : 0;
   }

   for (i=0; __NFILE > i; i++)
      if (__userFiles[i]) fflush(__userFiles[i]);
   return 0;
}
