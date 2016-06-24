/*                                                                   */
/*                                John Hartmann 24 Jun 2016 15:14:37 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdio.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ void clearerr(FILE *stream)
{
    stream->errorInd = 0;
    stream->eofInd = 0;
    return;
}
