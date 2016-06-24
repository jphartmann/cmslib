/* Protocol requires this module                                     */
/*                                John Hartmann 15 Jan 2015 19:02:00 */

/*********************************************************************/
/* Change activity:                                                  */
/*15 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <cmsbase.h>
#include <cmsthreadglobal.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
main(int argc, char ** argv)
{
   #if 0
   __sayf("This is a simple hello.  thread block is 0x%zx bytes."
      "  Stack is %d pages.  Saved key %02x.  %d files %d atexits allocated."
      "  stdout %p.",
      sizeof(struct _cmsthreadglobal),
      __getgbl()->stacksize,
      __getgbl()->guardkey,
      __getgbl()->numfds,
      __getgbl()->atexitcount,
      stdout);
   __sayf("   array base %p stdin %p stdout %p stderr %p",
      __getgbl()->prealloc,
      __getgbl()->prealloc[0],
      __getgbl()->prealloc[1],
      __getgbl()->prealloc[2]
      );
   #endif
   printf("Hello, world!\n");
   return 0;
}
