/* Pipeline hello world                                              */
/*                                John Hartmann 27 Jan 2015 13:59:59 */

/*********************************************************************/
/* Change activity:                                                  */
/*27 Jan 2015  New module.                                           */
/*********************************************************************/

#include <cmspipe.h>
#include <string.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
fplhello(struct pipeanchor * pa, struct pipeparms * args)
{
   struct piperecord hello = { "Hello, World of pipelines!", strlen(hello.ptr) };
   char token[8];
   int rv;
   int wl = 0;
   struct
   {
      char * fmt;
      int fmtlen;
      int  alen;
      char * upper;
   } pf =
   {
      "Word length %d: upper %s.",
      strlen(pf.fmt),
   };

   rv = pipoutput(pa, &hello);
   if (args->string.length)
   {
      rv |= pipoutput(pa, &args->string);
      wl = pipword(pa);
      if (args->word.length != wl) return 17;
      rv |= pipoutput(pa, &args->word);
      args->token = token;
      piputkn(pa);
      pf.alen = wl;
      pf.upper = token;
      fplgccpf(pa, 2, &pf);
      rv |= pipoutput(pa, &args->string);
   }
   pipshort(pa);
   return rv;
}
