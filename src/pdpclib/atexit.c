/*                                                                   */
/*                                John Hartmann 24 Jun 2016 12:20:33 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdlib.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ int atexit(void (*func)(void))
{
    int x;

    for (x = 0; x < __NATEXIT; x++)
    {
        if (__userExit[x] == 0)
        {
            __userExit[x] = func;
            return (0);
        }
    }
    return (-1);
}
