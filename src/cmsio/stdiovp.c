/* Pipe device interface.                                            */
/*                                John Hartmann 28 Jun 2011 14:54:40 */

/*********************************************************************/
/* The  fitting  interface  provides  the  data  buffer on read, but */
/* requires  the  buffer to be stable on write.  In theory, the data */
/* buffer  might  be  required  to  be  stable forever, depending on */
/* pipeline topology.                                                */
/*                                                                   */
/* Change activity:                                                  */
/* 6 Oct 2011  jph Support binary.                                   */
/*28 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <fplpop.h>
#include <csl.h>

#if 1
   #define LOGIT(...)
#else
   #include <cmsbase.h>
   #define LOGIT(x...) __WERROR(x)
#endif

/* Forward declarations:                                             */
static int devflush(FILE * f);
static int devclose(FILE * f);
static ssize_t devwrite(FILE * f);
static int devextend(FILE * f, size_t add);
static ssize_t devread(FILE * f);
static int devopen(FILE * f, const char * name, int oflags, const char * mode);
/* End of forward declarations.                                      */

struct __access _pipeacc=
{
   .type = "pipe",
   open: devopen,
   read: devread,
   write: devwrite,
   extend: devextend,
   flush: devflush,
   close: devclose,
};

FILE *
popen(const char * cmd, const char * type)
{
   int dir;
   int bin = 0;
   FILE * f;
   int fd;
   char bfr[strlen(cmd) + 32];
   char * s=bfr;
   int speclen=0;
   static const char * fitting="fitting FPLPOPEN";
   void * parm;
   int rv;

   void load(const char * t)
   {
      while (*t) *s++ = *t++, speclen++;
   }

   LOGIT("popen %s command %s", type, cmd);
   if (0==strcmp("r", type)) dir=0;
   else if (0==strcmp("rb", type)) dir = 0, bin =  1;
   else if (0==strcmp("w", type)) dir=1;
   else if (0==strcmp("wb", type)) dir=1, bin =  1;
   else
   {
      LOGIT("bad type %s\n", type);
      return NULL;
   }

   cmd+=strspn(cmd, " ");
   if (!*cmd)
   {
      LOGIT("No pipeline text\n");
      return NULL;
   }

   if (dir)                           /* Fitting goes first          */
   {
      char c;

      if ('(' == *cmd)
         do (c = *s++ = *cmd++), speclen++; while (')' != c);
      load(fitting);
      load("|");
      load(cmd);
   }
   else
   {
      load(cmd);
      load("|");
      load(fitting);
   }

   LOGIT("pipe %d bytes: >%.*s<\n", speclen, speclen, bfr);

   parm = calloc(32, sizeof(double));
   if (!parm)
   {
      errno=ENOMEM;
      return NULL;
   }

   rv = _popen(parm, &dir, bfr, &speclen);
   if (rv)
   {
      LOGIT("_popen rv %d\n", rv);
      errno=EIO;
      goto failpop;
   }

   LOGIT("_popen ok\n");

   fd = _getafd();
   if (-1 == fd) goto failpope;
   LOGIT("have fd %d\n", fd);

   f = _getafile(fd);
   if (! f) goto failpope;
   LOGIT("have file %p for fd %d\n", f, fd);
   f->ftype=_f_pipe;
   f->oflags = (dir ? O_WRONLY : O_RDONLY) | (bin ? O_BINARY : 0) ;
   f->pac = & _pipeacc;
   f->accwork=parm;
   f->fd = fd;
   return f;

failpope:
   errno=ENOMEM;
   _pclose(parm);
failpop:
   free(parm);
   return NULL;
}

int
pclose(FILE * f)
{
   return fclose(f);
}


static int
devopen(FILE * f, const char * name, int oflags, const char * mode)
{
   return -1;
}

/*********************************************************************/
/* Read another record from the pipeline.  Read() comes here when it */
/* has emptied the current buffer.                                   */
/*                                                                   */
/* There  is  no point in allocating a buffer since the pipeline has */
/* the record buffered.                                              */
/*                                                                   */
/* The length is advisory.  For a pipe it is ignored.                */
/*********************************************************************/

static ssize_t
devread(FILE * f)
{
   unsigned char * bp;
   int bl;
   int rv = _pread(f->accwork, &bp, &bl);

   #if 0
   __WERROR("Pipe read rv %d bl %d", rv, bl);
   #endif
   if (4==rv)
   {
      f->eofInd=1;
      return 0;
   }
   if (rv)
   {
      f->sfsrc = rv;
      errno = EIO;
      return -1;
   }

   f->buffer = bp;
   f->byteptr = 0;
   f->hiwater = bl;
   return bl;
}

/*********************************************************************/
/* Write a line to the underlying interface.                         */
/*********************************************************************/

static ssize_t
devwrite(FILE * f)
{
   int rv;

   rv = _pwrite(f->accwork, f->buffer, &f->byteptr);
   if (rv)
   {
      errno=EIO;
      f->errorInd=1;
   }

   f->byteptr = 0;
   return rv;
}

static int
devextend(FILE * f, size_t add)
{
   if (O_RDONLY & f->oflags) return 0;   /* What are you doing here? */
   add += f->byteptr;
   if (add <= f->hiwater) return 0;   /* Have room                   */
   return _devextend(f, 2 * add);
}

static int
devflush(FILE * f)
{
   if (0 == (O_RDONLY & f->oflags) && f->byteptr) devwrite(f);
   return 0;
}

static int
devclose(FILE * f)
{
   _pclose(f->accwork);
   return 0;
}
