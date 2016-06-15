/* VM-specific stuff                                                 */
/*                                John Hartmann 17 Jun 2011 11:50:20 */

/*********************************************************************/
/* The  abstraction  here  is  a  device type.  It is an object that */
/* implements   basic   device   functions,  such  as  open,  close, */
/* read/write at the record level.                                   */
/*                                                                   */
/* As  for  the  I/O  library,  we  have  two  layers here, the fxxx */
/* routines  eventually  boil  down  to  read()  and  write(), which */
/* operate  on  records.  Records are read and written by the record */
/* read  and write methods of the device.  Thus read and write block */
/* and deblock.                                                      */
/*                                                                   */
/* It  might  appear  that there might be various shortcuts, such at */
/* fgets()  reading to the end of the record (it does), but it might */
/* have been preceded by a read of n bytes, so it does not consume a */
/* record.                                                           */
/*                                                                   */
/* OLD NOTES:                                                        */
/*                                                                   */
/* The VM stuff works differently for binary and text files.         */
/*                                                                   */
/* For  read  of  text files, '\n' is inserted at record boundaries; */
/* you  cannot  have  a file that ends in an unterminated line.  For */
/* write,  the byte stream is broken at newlines.  They better match */
/* the  record  length  for  F  files.   Null records are a bit of a */
/* problem;  we  should  probably  write  a  single blank for such a */
/* beast.  Some day we might support ASCII carriage control.         */
/*                                                                   */
/* For  binary  files  read() and write() deal with one record for V */
/* files  and  a spanned record stream for F files.  fwrite writen n */
/* records; and fread reads n records.                               */
/*                                                                   */
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#include <cmsbase.h>
#include <csl.h>
#include <exsbuff.h>
#include <nucon.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
__onOSj(void)
{
   static const struct nucon * pnuc;

   return 'O' == pnuc->systemid[0];
}


FILE *
fdopen(int fd, const char *mode)
{
   if (0 > fd) return NULL;
   if (__NFILE <= fd) return NULL;
   return __userFiles[fd];
}

FILE *
fopen(const char *path, const char *mode)
{
   int olen;
   int oflags;
   int fd;
   int rv;

   rv = __decofl(mode, &oflags, &olen);
   if (rv) return NULL;

   fd = open(path, oflags | O_MODESTR, mode + olen);
   if (-1 == fd)
   {
      /* __sayf(__FILE__ ":  Unable to open '%s'.  %m", path);       */
      return NULL;
   }

   return __userFiles[fd];
}

int
_allocbuf(FILE * f, int size)
{
   f->buffer = malloc(size);

   if (f->buffer)
   {
      f->buffersize = size;
      return 0;
   }
   f->errorInd = 1;
   return errno = ENOMEM;
}

int
_devextend(FILE * f, int nusize)
{
   void * vp;

   assert(0 < nusize);
   if (O_RDONLY & f->oflags) return 0;   /* What are you doing here? */
   if (nusize <= f->buffersize) return 0;

   vp = realloc(f->buffer, nusize);

   if (!vp)
   {
      f->errorInd = 1;
      errno = ENOMEM;
      return -1;
   }

   f->buffer = vp;
   f->buffersize = nusize;
   return 0;
}
