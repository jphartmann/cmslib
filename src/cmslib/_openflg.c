/* Decode open flags                                                 */
/*                                John Hartmann 11 Feb 2015 16:48:18 */

/*********************************************************************/
/* Turn  the  flag  string  for  fopen  into  the open flags used by */
/* open().   If  the  length feedback parameter is null, we scan the */
/* entire  string  and report errors.  If not null, we stop and feed */
/* back the length; the initial first character must validate.       */
/*                                                                   */
/* The SFS intents and corresponding mode strings are:               */
/*                                                                   */
/* NEW         [aw]+x                                                */
/* READ        r                                                     */
/* REPLACE     w+                                                    */
/* WRITE       [ar]+                                                 */
/*                                                                   */
/* SFS  does  not  support  write only, so somewhere there must be a */
/* mapping of modes not specified above, implicit or explicit.       */
/*                                                                   */
/* Change activity:                                                  */
/*11 Feb 2015  New module.                                           */
/*********************************************************************/

#include "cmspriv.h"
#include <fcntl.h>
#include <errno.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
__decofl(const char * mode, int * fb, int * lenfb)
{
   const char * omode = mode;
   char c[2] = {0};

   *fb = 0;
   switch (c[0] = *mode++)
   {
      case 'r':                       /* Read                        */
         *fb = O_RDONLY;
         break;
      case 'w':
         *fb = O_WRONLY | O_CREAT | O_TRUNC;
         break;
      case 'a':
         *fb = O_WRONLY | O_CREAT | O_APPEND;
         break;
      default:

         return _seterr(EINVAL, EINVAL, _einv_rsn_bad_mode1,
            "First character of fopen() mode string not r, w, or a.", c);
   }

   if ('b' == *mode)
   {
      mode++;
      (*fb) |= O_BINARY;
   }

   if ('+' == *mode)
   {
      mode++;
      (*fb) &= ~(O_RDONLY | O_WRONLY);
      (*fb) |= O_RDWR;
   }

   if ('b' == *mode)
   {
      mode++;
      (*fb) |= O_BINARY;
   }

   if ('x' == *mode)
   {
      mode++;
      (*fb) |= O_BINARY;
   }

   if (lenfb && ',' == *mode) mode++;
   else if (*mode)
      return _seterr(EINVAL, EINVAL, _einv_rsn_bad_mode_char,
         "Character of fopen() mode string not first is not expected.", mode);

   if (lenfb) *lenfb = omode - mode;
   return 0;
}
