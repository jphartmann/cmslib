/* Say with printf plist                                             */
/*                                John Hartmann 20 Jun 2011 18:09:59 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <cmsbase.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
__sayf(const char * format, ...)
{
   va_list arg;
   int len;
   char bfr[256];

   va_start(arg, format);
   len=vsnprintf(bfr, sizeof(bfr), format, arg);
   va_end(arg);

   __say(bfr, len);
   return len;
}
