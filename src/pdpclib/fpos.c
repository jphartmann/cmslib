/*                                                                   */
/*                                John Hartmann 24 Jun 2016 15:12:58 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdio.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ int fsetpos(FILE *stream, const fpos_t *pos)
{
    fseek(stream, *pos, SEEK_SET);
    return (0);
}

__PDPCLIB_API__ int fgetpos(FILE *stream, fpos_t *pos)
{
    *pos = ftell(stream);
    return (0);
}
