/* Abort                                                             */
/*                                John Hartmann 17 Jun 2011 15:35:57 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#if defined(__ZVM__)
   #include <cmsbase.h>
#endif

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ void abort(void)
{
#if defined(__ZVM__)
    __traceb();
#endif
    exit(EXIT_FAILURE);
#if !defined(__EMX__) && !defined(__GNUC__) && !defined(__WIN32__) \
  && !defined(__gnu_linux__)
    return;
#endif
}
