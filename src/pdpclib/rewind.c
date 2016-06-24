/*                                                                   */
/*                                John Hartmann 24 Jun 2016 15:21:27 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdio.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ void rewind(FILE *stream)
{
    fseek(stream, 0L, SEEK_SET);
    return;
}
