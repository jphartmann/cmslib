/* Associate a new file with an open stream                          */
/*                                John Hartmann 10 Feb 2015 15:48:18 */

/*********************************************************************/
/* FILE *freopen(const char *path, const char *mode, FILE *stream);  */
/*                                                                   */
/* Change activity:                                                  */
/*10 Feb 2015  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

/*********************************************************************/
/* Reassociate  a  FILE  with  a  new  object,  often in response to */
/* redirection.   Testing shows that the stream argument must not be */
/* null on BSD or Linux, though it may refer to a closed file.       */
/*********************************************************************/

FILE *
freopen(
   const char * __restrict path,
   const char * __restrict mode,
   FILE * f)
{
   int oflags;
   int len;
   int rv;
   int fd = f->fd;
   int std = f->stdfile;              /* Should be on                */

   rv = __decofl(mode, &oflags, &len);
   if (rv) return NULL;

   assert(f);                    /* Don't just barf on the poor user */
   fflush(f);
   _fileclean(f);                     /* Release buffers             */
   memset(f, 0, sizeof(* f));         /* Wipe it thoroughly          */
   memcpy(f->ckwd, __FILECKWD, 4);
   f->fd = fd;
   f->stdfile = std;

   if (-1 == _openfile(f, path, oflags, mode+len)) return 0;
   return f;
}
