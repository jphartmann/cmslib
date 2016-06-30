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
   unsigned char out[4096];
   int rv;
   struct piperecord inrec;
   struct piperecord outrec = { out, sizeof(out) };
   z_stream zstream = {.opaque = 0, };
   int deflatesync = Z_NO_FLUSH;
   int inrv = 0;                      /* OK so far                   */

   rv = expand ? inflateInit(&zstream) : deflateInit(&zstream, CLEVEL);
   if (Z_OK != rv) return error("init", rv);
   rv = pipcommit(panc, 0);
   if (rv)
   {
      __sayf("commit rc %d\n", rv);
      rv = 0;
      goto error;
   }

   rv = primein(panc, &inrec, &zstream);
   if (rv)
   {
      if (12 == rv) rv = 0;
      goto error;
   }

   zstream.next_out = out;
   zstream.avail_out = sizeof(out);

   for(;;)
   {
      int ain, aout;

      if (!zstream.avail_in && !inrv)
      {
         inrec.length = 0;
         rv = pipinput(panc, &inrec);
         if (rv)
         {
            error("pipinput", rv);
            goto error;
         }
         inrv = rv = primein(panc, &inrec, &zstream);
         if (12 == rv)
         {
            deflatesync = Z_FINISH;
            rv = 0;
         }
         else if (rv) goto error;
      }
      if (!zstream.avail_out)
      {
         rv = pipoutput(panc, &outrec);
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
         outrec.length = sizeof(out);
         zstream.next_out = out;
         zstream.avail_out = sizeof(out);
      }

      ain = zstream.avail_in;
      aout = zstream.avail_out;

      rv = expand
         ? inflate(&zstream, Z_SYNC_FLUSH)
         : deflate(&zstream, deflatesync);

      switch (rv)
      {
         case Z_OK:
            break;
         case Z_STREAM_END:
            if (deflatesync != Z_FINISH)
            {
               /* Inflate  is  terminating  because  it  met  an end */
               /* marker.  Be sure to consume the last input record. */
               inrec.length = 0;
               rv = pipinput(panc, &inrec);
            }
            outrec.length = sizeof(out) - zstream.avail_out;
            if (outrec.length)
            {
               rv = pipoutput(panc, &outrec);
               if (rv && rv != 12) error("pipeout", rv);
            }

            goto error;
         default:
            __sayf("in/deflate rv %d", rv);
            goto error;
      }

      if (ain == zstream.avail_in && aout == zstream.avail_out)
      {
         __sayf("No data processed.  inrv %d avail in %d avail out %d",
            inrv, zstream.avail_in, zstream.avail_out);
         break;                       /* Don't loop                  */
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
