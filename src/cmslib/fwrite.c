/* Write to a file                                                   */
/*                                John Hartmann 20 Jan 2015 11:23:50 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>

/*********************************************************************/
/* A  fprintf changed to fwrite by the compiler.  Do it in character */
/* mode.                                                             */
/*********************************************************************/

size_t
fwrite(const void * ptr, size_t size, const size_t nmemb, FILE * f)
{
   int i;
   const char * b = ptr;
   int fd = fileno(f);

   #if 0
   __WERROR("fwrite fd %d file %p %zd x %zd %02x", fd, f, size, nmemb, b[0]);
   #endif
   if (f->eofInd || f->errorInd || 0 == size || 0== nmemb) return 0;
   for (i = 0; nmemb > i; i++)
   {
      int cnt = write(fd, b, size);

      #if 0
      __WERROR("Write rv %d", cnt);
      #endif
      if (-1 == cnt)
      {
         __WERROR("Cannot write %zd bytes '%*s' to fd %d file %p\n",
            size, (int) size, b, fileno(f), f);
         return -1;
      }
      b += cnt;
      if (f->eofInd || f->errorInd) break;
   }

   return i;
}
