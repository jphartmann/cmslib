/* CMS routines                                                      */
/*                                John Hartmann 30 Jun 2011 13:25:29 */

/*********************************************************************/
/* Change activity:                                                  */
/*30 Jun 2011  New module.                                           */
/*********************************************************************/

#include <linerd.h>
#include <stdio.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
__consrd(void * bfr, int len, unsigned char flag1, unsigned char flag2, int * regfb)
{
   struct linerd b =
   {
      "LINERD  ", bfr, len,
      flag1: flag1, flag2: flag2,       /* case=mixed wait=no          */
      fence: FENCE,
   };

   return __svc204(NULL, b.verb, 0, regfb);
}
