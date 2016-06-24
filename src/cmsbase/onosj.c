/* Test whether running under OS/j                                   */
/*                                John Hartmann 24 Jun 2016 16:24:38 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "nucon.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
__onOSj(void)
{
   static const struct nucon * pnuc;

   return 'O' == pnuc->systemid[0];
}
