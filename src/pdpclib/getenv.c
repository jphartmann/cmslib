/*                                                                   */
/*                                John Hartmann 24 Jun 2016 12:22:32 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdlib.h"
#include "string.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ char *getenv(const char *name)
{
   /* And for anything remotely unixy                                */

   char ** ep = environ;
   const size_t len = name ? strlen(name) : 0;

   if (!name || !ep || !len) return NULL;

   for (; *ep; ep++)
   {
      size_t i;
      char * var = *ep;

      for (i = 0; len>i; i++)
         if (name[i] != var[i]) break;

      if (len == i && '=' == var[i]) return var + i + 1;
   }
   return (NULL);
}
