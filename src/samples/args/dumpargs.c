/* Dump arguements; test for correctly parsing in go390.c            */
/*                                John Hartmann 23 Jan 2015 21:41:20 */

/*********************************************************************/
/* Change activity:                                                  */
/*23 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
main(int argc, char ** argv)
{
   int i;

   printf("argc = %d\n", argc);
   for (i = 0; argc > i; i++) printf("argv[%2d] = '%s'\n", i, argv[i]);
   return 0;
}
