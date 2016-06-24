/* Test reading standard input                                       */
/*                                 John Hartmann 4 Feb 2015 11:37:07 */

/*********************************************************************/
/* Change activity:                                                  */
/* 4 Feb 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
main(int argc, char ** argv)
{
   int chars = 0;
   int words = 0;
   int lines = 0;
   int inword = 0;

   while (!feof(stdin))
   {
      int c = getchar();
      switch (c)
      {
         case '\n':
            lines++;
         case ' ':
            inword = 0;
            break;
         case -1:                     /* EOF                         */
            goto done;
         default:
            if (inword) break;
            inword = 1;
            words++;
      }
      chars++;                        /* Line end counts as char     */
   }

done:
   printf("%d %d %d\n", lines, words, chars);
   return 0;
}
