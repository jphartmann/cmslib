/* Interface to the zlib library to compress or expand               */
/*                                 John Hartmann 5 May 2014 11:08:57 */

/*********************************************************************/
/* Change activity:                                                  */
/* 5 May 2014  New module.                                           */
/*********************************************************************/

#include <zlib.h>
#include <cmspipe.h>
#include <stdio.h>
#include <cmsbase.h>

#define CLEVEL Z_DEFAULT_COMPRESSION

/* Forward declarations:                                             */
static int error(const char * msg, int rv);
static int primein(struct pipeanchor * panc, struct piperecord * pr, z_stream * zs);
/* End of forward declarations.                                      */

int
zlibfilt(struct pipeanchor * panc, struct pipeparms * args)
{
   const int expand = args->endrange;
   int rv;
   struct piperecord prec;
   z_stream zstream = {.opaque = 0, };
   unsigned char out[4096];
   int deflatesync = Z_NO_FLUSH;
   int inrv = 0;                      /* OK so far                   */

   __sayf("starting zlibstg.  Std err is %p", stderr);

   rv = expand ? inflateInit(&zstream) : deflateInit(&zstream, CLEVEL);
   __sayf("init rc %d\n", rv);
   if (Z_OK != rv) return error("init", rv);
   rv = pipcommit(panc, 0);
   if (rv)
   {
      __sayf("commit rc %d\n", rv);
      __say("Cannot commit", -1);
      rv = 0;
      goto error;
   }

   rv = primein(panc, &prec, &zstream);
   __sayf("prime rc %d\n", rv);
   if (rv)
   {
      if (12 == rv) rv = 0;
      goto error;
   }

   zstream.next_out = out;
   zstream.avail_out = sizeof(out);

   for(;;)
   {
      __sayf("avail in %d avail out %d", zstream.avail_in, zstream.avail_out);
      if (!zstream.avail_in && !inrv)
      {
         prec.length = 0;
         rv = pipinput(panc, &prec);
         if (rv) return error("pipinput", rv);
         inrv = rv = primein(panc, &prec, &zstream);
         if (12 == rv) deflatesync = Z_FINISH;
         else if (rv) goto error;
      }
      if (!zstream.avail_out)
      {
         prec.ptr = out;
         prec.length = sizeof(out);
         rv = pipoutput(panc, &prec);
         if (12 == rv)
         {
            rv = 0;
            goto error;
         }
         if (rv)
         {
            error("pipeout", rv);
            goto error;
         }
         zstream.next_out = out;
         zstream.avail_out = sizeof(out);
      }

      rv = expand
         ? inflate(&zstream, Z_SYNC_FLUSH)
         : deflate(&zstream, deflatesync);

      switch (rv)
      {
         case Z_STREAM_END:
            prec.ptr = out;
            prec.length = sizeof(out) - zstream.avail_out;
            rv = pipoutput(panc, &prec);
            goto error;
      }
   }

error:
   if(expand) inflateEnd(&zstream);
   else deflateEnd(&zstream);
   return rv;
}

static int
primein(struct pipeanchor * panc, struct piperecord * pr, z_stream * zs)
{
   int rv = piplocate(panc, pr);
   if (rv)
   {
      if (12 == rv) return rv;
      return error("locate", rv);
   }

   zs->next_in = pr->ptr;
   zs->avail_in = pr->length;
   return 0;
}

static int
error(const char * msg, int rv)
{
   __sayf("Error on %s: %d", msg, rv);
   return 10;
}
