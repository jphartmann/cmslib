/* A few constants for use by the assembler code                     */
/*                                John Hartmann 24 Jan 2015 11:24:32 */

/*********************************************************************/
/* This  allows  control blocks that are shadowed in assembler to be */
/* allocated at their correct size.  For example when more areas are */
/* added for C only.                                                 */
/*                                                                   */
/* Also  contains code to initialise the thread global area.  All we */
/* need is a bit of stack space.                                     */
/*                                                                   */
/* Change activity:                                                  */
/*24 Jan 2015  New module.                                           */
/*********************************************************************/

#include <sys/types.h>
#include <cmsthreadglobal.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

const size_t __cmstgs = sizeof(struct _cmsthreadglobal);

void
__cmstgi(struct _cmsthreadglobal * gbl)
{
   gbl->atexitcount = __INITIALEXITS;
   gbl->userExit = gbl->uexpre;

   gbl->numfds = __INITIALFDS;
   gbl->userFiles = gbl->prealloc;
}
