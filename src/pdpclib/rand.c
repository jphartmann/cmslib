/*                                                                   */
/*                                John Hartmann 17 Jun 2011 14:56:22 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdlib.h>
#include <stddef.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

static unsigned long myseed = 1;

__PDPCLIB_API__ void srand(unsigned int seed)
{
    myseed = seed;
    return;
}

__PDPCLIB_API__ int rand(void)
{
    int ret;

    myseed = myseed * 1103515245UL + 12345;
    ret = (int)((myseed >> 16) & 0x8fff);
    return (ret);
}
