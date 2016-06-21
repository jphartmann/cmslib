/* Read n pieces of m data bytes                                     */
/*                                John Hartmann 20 Jan 2015 10:49:35 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <unistd.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

/*********************************************************************/
/* Read n pieces of data m bytes wide.                               */
/*                                                                   */
/* If the file is binary, just read n records.                       */
/*********************************************************************/

size_t
fread(void * ptr, const size_t size, const size_t nmemb, FILE * f)
{
   char * b = ptr;
   int i;
   ssize_t rv;

   if (0 == size || 0== nmemb) return 0;

   for (i = 0; nmemb > i && !f->eofInd && !f->errorInd; i++)
   {
      /* __WERROR("Reading %zd bytes", size);                        */
      rv = read(fileno(f), b, size);
      /* __WERROR("rv %zd ", rv);                                    */
      if (-1 == rv || !rv) break;     /* Error or EOF                */
      b += rv;
   }

   return i;
}
