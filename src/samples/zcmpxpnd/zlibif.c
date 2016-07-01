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

/* Forward declarations:                                             */
static int primein(struct pipeanchor * panc, struct piperecord * pr, z_stream * zs);
static int process(struct pipeanchor * panc, struct pipeparms * args,
   const int expand, z_stream * pz);
/* End of forward declarations.                                      */

/*********************************************************************/
/* Initialise the z stream.  Close on exit.                          */
/*********************************************************************/

int
zlibfilt(struct pipeanchor * panc, struct pipeparms * args)
{
   const int expand = args->endrange;
   int rv;
   z_stream zstream = {.opaque = 0, };

   if (expand) rv = inflateInit(&zstream);
   else
   {
      int level = args->word.length;  /* -1 for default              */

      if (0 > level || 9 < level) level = Z_DEFAULT_COMPRESSION;
      rv = deflateInit(&zstream, level);
   }

   if (Z_OK != rv) return __sayf("Error %d on z Init.", rv), rv;

   rv = process(panc, args, expand, &zstream);

   if(expand) inflateEnd(&zstream);
   else deflateEnd(&zstream);

   return rv;
}

/*********************************************************************/
/* Main processing loop                                              */
/*********************************************************************/

static int
process(struct pipeanchor * panc, struct pipeparms * args,
   const int expand, z_stream * pz)
{
   unsigned char out[4096];
   struct piperecord inrec;
   struct piperecord outrec = { out, sizeof(out) };
   int deflatesync = Z_NO_FLUSH;
   int inrv = 0;                      /* OK so far                   */
   int rv;

   rv = pipcommit(panc, 0);
   if (rv) return 0;

   rv = primein(panc, &inrec, pz);
   if (rv) return 12 == rv ? 0 : rv;

   pz->next_out = out;
   pz->avail_out = sizeof(out);

   for(;;)
   {
      int ain, aout;

      if (!pz->avail_in && !inrv)
      {
         /* Release current record                                   */
         inrec.length = 0;
         rv = pipinput(panc, &inrec);
         if (rv) return rv;

         inrv = rv = primein(panc, &inrec, pz);
         if (rv)
         {
            if (12 != rv) return rv;
            deflatesync = Z_FINISH;
            rv = 0;
         }
      }
      if (!pz->avail_out)
      {
         rv = pipoutput(panc, &outrec);
         if (rv) return 12 == rv ? 0 : rv;

         outrec.length = sizeof(out);
         pz->next_out = out;
         pz->avail_out = sizeof(out);
      }

      ain = pz->avail_in;
      aout = pz->avail_out;

      rv = expand
         ? inflate(pz, Z_SYNC_FLUSH)
         : deflate(pz, deflatesync);

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
            outrec.length = sizeof(out) - pz->avail_out;
            if (outrec.length)
            {
               rv = pipoutput(panc, &outrec);
               if (rv) return 12 == rv ? 0 : rv;
            }

            return 0;
         default:
            __sayf("in/deflate rv %d", rv);
            return rv;
      }

      if (ain == pz->avail_in && aout == pz->avail_out)
      {
         __sayf("No data processed.  inrv %d avail in %d avail out %d",
            inrv, pz->avail_in, pz->avail_out);
         break;                       /* Don't loop                  */
      }
   }
   return 0;
}

/*********************************************************************/
/* Get next non-null record from the input.                          */
/*********************************************************************/

static int
primein(struct pipeanchor * panc, struct piperecord * pr, z_stream * zs)
{
   for (;;)
   {
      int rv = piplocate(panc, pr);

      if (rv) return rv;
      if (pr->length) break;
      rv = pipinput(panc, pr);
      if (rv) return rv;
   }

   zs->next_in = pr->ptr;
   zs->avail_in = pr->length;
   return 0;
}
