/* Return position in file.                                          */
/*                                John Hartmann 20 Jan 2015 10:57:58 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>

long
ftell(FILE * f)
{
   return f->offset;
}
