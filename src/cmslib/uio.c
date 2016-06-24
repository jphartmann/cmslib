/* Unix I/O routines.                                                */
/*                                 John Hartmann 2 Jul 2011 09:51:08 */

/*********************************************************************/
/* Change activity:                                                  */
/* 2 Jul 2011  New header file.                                      */
/*********************************************************************/

#include "cmspriv.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <cmsbase.h>

#define DEBUG 0

extern struct __access _consacc;
extern struct __access _pipeacc;
extern struct __access _sfsacc;


/* Forward declarations:                                             */
static void cleanfile(FILE * f);
/* End of forward declarations.                                      */


/*********************************************************************/
/* Open  a  file.   Assign  a  file  descriptor  and allocate a FILE */
/* structure.   Decode  enough of the file name to select the device */
/* handler; then go to the device-dependent open.                    */
/*********************************************************************/

int
open(const char * name, int oflags, ...)
{
   int fd = _getafd();
   FILE * f;
   va_list va;
   char * ostr = NULL;

   if (-1 == fd) return -1;

   f = _getafile(fd);
   if (!f) return -1;

   if (O_MODESTR & oflags)
   {
      va_start(va, oflags);
      ostr = va_arg(va, char *);
      va_end(va);
   }
   return _openfile(f, name, oflags, ostr);
}

int
_openfile(FILE * f, const char * name, int oflags, const char * ostr)
{
   int rv=0;
   struct __access * pacc[]=
   {
      0, &_consacc, &_pipeacc, &_sfsacc,
   };

   f->oflags = oflags;
   if (f->byteptr)
   {
      __WERROR("File %s byteptr %zd", name, f->byteptr);
      __traceb();
   }

   if (strchr(name, '.')) f->ftype = _f_sfs;
   else if (0==strcmp(name, "*")) f->ftype = _f_term;
   else if (__onOSj()) f->ftype = _f_sfs;
   else
   {
      __WERROR("Unable to determine file type for file name '%s'.", name);
      rv = ENOENT;
      goto bailout;
   }

   /* Indicate (on read) that NL has been transmitted.               */

   if (O_RDONLY & f->oflags) f->byteptr = 1;
   if ( 0== rv)
   {
      f->pac = pacc[f->ftype];

      rv = f->pac->open(f, name, oflags, ostr);
   }
   if (rv)
   {
bailout:
      cleanfile(f);
      errno = rv;
      return -1;
   }

   #if DEBUG
   __say("opened", 6);
   __WERROR("File %d open for %s %p size %zd; byteptr %zd.\n",
      f->fd, name, f, sizeof(FILE), f->byteptr);
   #endif
   return f->fd;
}

/*********************************************************************/
/* Close a file                                                      */
/*********************************************************************/

int
close (int fd)
{
   FILE * f;

   #if DEBUG
   __WERROR("Close fd %d", fd);
   __traceb();
   #endif
   f = _getfile(fd, -1);
   if (!f) return -1;

   fflush(f);
   cleanfile(f);
   return 0;
}

static void
cleanfile(FILE * f)
{
   int fd = f->fd;

   _fileclean(f);
   if (f->stdfile) return;
   __userFiles[fd] = NULL;
   free(f);
}

/*********************************************************************/
/* Clean out a file descriptor; also for reopen.                     */
/*********************************************************************/

void
_fileclean(FILE * f)
{
   if (f->isopen && f->pac) f->pac->close(f);
   f->isopen = 0;
   if (f->accwork) free(f->accwork);
   /* pipe interface inserts buffer from pipeline on read            */
   if (f->buffersize && f->buffer) free(f->buffer);
}

/*********************************************************************/
/* Read  reads  records from a file.  If the file is binary, we read */
/* at  most  one  record.   If  the file is text, we read as much as */
/* requested, first emptying the buffer and then taking records, all */
/* separated by newlines.                                            */
/*                                                                   */
/* Software that relies on EOF when less is read than requested will */
/* fail, as it will when the input is a pipe or a socket.            */
/*********************************************************************/

ssize_t
read(int filedes, void *buffer, const ssize_t size)
{
   FILE * f = _getfile(filedes, 0);
   char * const b = buffer;
   int i;
   int rv;

   if (!f) return -1;
   if (!size) return 0;

   #if DEBUG
   __WERROR("Read fd %d %s for %zd.", filedes, f->pac->type, size);
   #endif

   for (i = 0; size > i; )
   {
      if (f->eofInd) break;           /* Return 0 or what was read   */
      if (f->hiwater == f->byteptr)   /* Add line end to line?       */
      {
         if (!(O_BINARY & f->oflags)) /* Text file?                  */
            b[i++] = '\n';            /* Set line end                */
         f->byteptr++;                /* Indicate EOR regardless     */
      }
      else if (f->hiwater < f->byteptr)
      {
         rv = f->pac->read(f);        /* Replenish                   */
         if (-1 == rv) return -1;
         /* Iterate to test EOF after read.                          */
      }
      else b[i++] = f->buffer[f->byteptr++];
   }

   #if 0
   __WERROR("Read %s returns %d '%.*s' %02x%02x%02x%02x.",
      f->pac->type, i, i, b, b[0], b[1], b[2], b[3]);
   __traceb();
   #endif

   return i;
}

/*********************************************************************/
/* Write a number of bytes to a file.                                */
/*********************************************************************/

ssize_t
write(int filedes, const void *buffer, const ssize_t size)
{
   FILE * f = _getfile(filedes, 1);
   size_t i;
   const char * b = buffer;
   int rv;

   if (!f)
   {
      __WERROR("Cannot write %zd bytes '%.*s' to fd %d--filedescriptor is not open\n",
         size, (int) size, b, filedes);
      return -1;
   }

   #if DEBUG
   __WERROR("Fd %d ptr %zd cnt %zd %02x %.*s",
      filedes, f->byteptr, size, b[0], (int) size, b);
   #endif

   if (!size) return 0;
   /* f->pac->write(f, buffer, size);                                */

   #if 1 < DEBUG
   __WERROR("fd %d write %zd", filedes, size);
   #endif

   rv = f->pac->extend(f, size);
   if (rv)
   {
      __WERROR("Cannot allocate for fd %d rv %d  %m", f->fd, rv);
      return -1;
   }
   if (!f->buffer)
   {
      __WERROR("No buffer allocated for write fd %d %zd bytes", filedes, size);
      return -1;
   }

   /* FIXME:  Binary needs to flush buffer at lrecl                  */
   for (i = 0; size > i; i++)
   {
      if (((O_BINARY & f->oflags) && f->byteptr >= f->lrecl)
         || (!(O_BINARY & f->oflags) && '\n' == b[i]))
      {
         rv = f->pac->write(f);
         f->byteptr = 0;
      }
      if ((O_BINARY & f->oflags) || '\n' != b[i])
         f->buffer[f->byteptr++] = b[i];
   }

   return i;
}

/*********************************************************************/
/* Verify that a file descriptor indexes a valid file                */
/*********************************************************************/

struct __file *
_getfile(int fd, int acc)
{
   FILE * f = NULL;
   char bfr[128];

   if (0 <= fd
      && __NFILE > fd
      && (f = __userFiles[fd])
      && (-1 == acc || ((acc ? O_WRONLY | O_RDWR : O_RDONLY ) & f->oflags))
      && !memcmp(f->ckwd, __FILECKWD, 4))
      return f;

   if (f)
   {
      sprintf(bfr, "%d", fd);
      _seterr(EINVAL, EINVAL, _einv_rsn_bad_fd_acc,
         "File descriptor has not correct access type.", bfr);
   }
   else
   {
      sprintf(bfr, "%d", fd);
      _seterr(EINVAL, EINVAL, _einv_rsn_bad_fd_none,
         "File descriptor is not open or number out of range.", bfr);
   }
   return NULL;

   if (f) __WERROR("File descriptor %d %p not opened correctly."
      "  Want %s oflags %x WRONLY %x RDONLY %x RDWR %x ckwd '%.4s'",
      fd, f, (acc ? "write" : "read"), f->oflags, O_WRONLY, O_RDONLY, O_RDWR, f->ckwd);
   else __WERROR("Bad input file descriptor %d.  %d slots, no file; acc = %d; %p %p %p",
      fd, __NFILE, acc,
      __userFiles[0], __userFiles[1], __userFiles[2]);
   __traceb();
   errno = EBADF;
   __exit(48);
   return NULL;
}

/*********************************************************************/
/* Assign an unused file descriptor.                                 */
/*********************************************************************/

int
_getafd(void)
{
   int i;

   for (i=0; __NFILE > i; i++)
      if (NULL==__userFiles[i])
         return i;

   errno = EMFILE;
   return -1;
}

/*********************************************************************/
/* OPen a file structure on a file descriptor.                       */
/*********************************************************************/

FILE *
_getafile(int fd)
{
   FILE * f = calloc(1, sizeof(struct __file));

   if (!f)
   {
      errno = ENOMEM;
      return f;
   }
   _initafile(fd, f);
   return f;
}

void
_initafile(int fd, FILE * f)
{
   memcpy(f->ckwd, __FILECKWD, 4);
   f->ungetCh = -1;
   f->fd = fd;
   #if 0
   __WERROR("user files %p fd %d\n", __userFiles, fd);
   #endif
   __userFiles[f->fd] = f;
}

int
fstat(int fd, struct stat * st)
{
   FILE * f = _getfile(fd, -1);

   if (!f) return -1;

   memset(st, 0, sizeof(* st));
   return f->pac->fstat ? f->pac->fstat(f, st) : 0;
}

int
stat(const char * name, struct stat * st)
{
   int fd = open(name, O_RDONLY);
   int rv;

   if (0>fd) return fd;               /* Not there                   */
   rv = fstat(fd, st);
   close (fd);
   return rv;
}
