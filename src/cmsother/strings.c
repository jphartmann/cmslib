/* Caseless compares                                                 */
/*                                John Hartmann 20 Jun 2011 11:35:14 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stddef.h>
#include <strings.h>
#include <ctype.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
strcasecmp(const char * s1, const char * s2)
{
   int r;

   while (*s1 && *s2)
   {
      r=*s1++ - *s2++;
      if (r) return r;
   }
   return *s1 - *s2;
}

int
strncasecmp(const char * s1, const char * s2, size_t length)
{
   int r;

   while (0 < length-- && *s1 && *s2)
   {
      r=*s1++ - *s2++;
      if (r) return r;
   }
   return *s1 - *s2;
}
