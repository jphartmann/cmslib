/*                                                                   */
/*                                John Hartmann 24 Jun 2016 15:27:39 */

/*********************************************************************/
/* Change activity:                                                  */
/*24 Jun 2016  New module.                                           */
/*********************************************************************/

#include "stdio.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ int ungetc(int c, FILE *stream)
{
    if ((stream->ungetCh != -1) || (c == EOF))
    {
        return (EOF);
    }
    stream->ungetCh = (unsigned char)c;
#if !defined(__ZVM__)
    stream->quickText = 0;
    stream->quickBin = 0;
#endif
    return ((unsigned char)c);
}
