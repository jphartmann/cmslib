/* Console file driver                                               */
/*                                John Hartmann 28 Jun 2011 14:43:28 */

/*********************************************************************/
/* Change activity:                                                  */
/*28 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>

#include <linerd.h>

#if !defined(DEBUG)
   #define DEBUG 0
#endif

/* Forward declarations:                                             */
static int devflush(FILE * f);
/* End of forward declarations.                                      */

static int
devopen(FILE * f, const char * name, int oflags, const char * mode)
{
   int rv =  0;

   if (f->buffer) __WERROR("Console buffer already allocated %p", f->buffer);
   else
   {
      rv = _allocbuf(f, 256);         /* Get us something            */

      #if 0
      __WERROR("Open console file %p fd %d rv %d buffer size %zd %p",
         f, f->fd, rv, f->buffersize, f->buffer);

     if (1 == f->fd)
     {
         char cmd[128];
         extern int system(char * str);

        sprintf(cmd, "CP TRACE STORE INTO %p", f);
        system(cmd);
     }
      #endif
   }
   return rv;
}

/*********************************************************************/
/* Issue the linerd macro to get a record.                           */
/*********************************************************************/

static ssize_t
devread(FILE * f)
{
   int rv;
   int regfb[2];

   if (256 > f->buffersize) _devextend(f, 256);
   rv = linerd_stack(f->buffer, f->buffersize, regfb);
   if (rv)
   {
      errno = EIO;
      f->errorInd = 1;
      return -1;
   }

#if DEBUG
   __WERROR("got %d bytes", regfb[0]);
#endif

   f->hiwater = regfb[0];             /* Bytes read                  */
   f->byteptr = 0;
   if (!f->hiwater) f->eofInd = 1;    /* Null line is EOF            */
   return regfb[0];
}

static ssize_t
devwrite(FILE * f)
{
   if (0==__say(f->buffer, f->byteptr))
   #if 0
   if (-1 != __sayf("%d: %.*s", f->fd, (int) f->byteptr, f->buffer))
   #endif
   {
      f->byteptr = 0;
      return 0;
   }
   errno = EIO;
   f->errorInd = 1;
   return -1;
}

static int
devextend(FILE * f, size_t add)
{
   #if 0
   __WERROR("Extending fd %d from %zd add %zd", f->fd, f->buffersize, add);
   #endif

   return _devextend(f, f->byteptr + add);
}

/*********************************************************************/
/* We do not write the buffer as it may be an incomplete line.       */
/*********************************************************************/

static int
devflush(FILE * f)
{
   if ((O_WRONLY & f->oflags) && f->byteptr) devwrite(f);
   else f->byteptr = f->hiwater + 1;  /* Read line                   */
   return 0;
}

static int
devclose(FILE * f)
{
   return 0;
}

struct __access _consacc=
{
   .type = "cons",
   open: devopen,
   read: devread,
   write: devwrite,
   extend: devextend,
   flush: devflush,
   close: devclose,
};
