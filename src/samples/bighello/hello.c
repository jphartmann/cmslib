/*                                                                   */
/*                                John Hartmann 16 Jun 2011 16:17:04 */

/*********************************************************************/
/* Change activity:                                                  */
/*16 Jun 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include <cmsbase.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

int
main(int argc, char ** argv)
{
   int i;
   FILE * f;
   char bfr[256];
   char * s;
   size_t lns=0;
   size_t bytes=0;
   struct timeval tv;
   struct tm * tm;
   int rv;

   printf("%d arguments.\n", argc);
   for (i=0; argc>i; i++)
      printf("%3i: %.50s\n", i, argv[i]);

   gettimeofday(&tv, NULL);
   tm=localtime(&tv.tv_sec);
   i = strftime(bfr, sizeof(bfr), "Time %T date %Y-%m-%d %w %a %Z", tm);
   printf("%s\n", bfr);
   printf("ctime %s tv %ld usec %d.  ",
      ctime(&tv.tv_sec), tv.tv_sec%86400, tv.tv_usec);

   printf("Sizeof int %ld long %ld size %ld\n",
      sizeof(int), sizeof(long), sizeof(lns));

   f=fopen("load.map", "r");
   if (!f && ENOENT == errno)
   {
      printf("coudn't open lower case load map; uppercasing.\n");
      f=fopen("LOAD.MAP", "r");
   }

   if (!f)
   {
      printf("coudn't open the load map: %m\n");
      exit (2);
   }

   printf("LOAD MAP file %p fd %d ... ", f, fileno(f));
   for (;;)
   {
      s = fgets(bfr, sizeof(bfr), f);
      if (!s) break;
      lns++, bytes+=strlen(bfr);
   }
   printf("%zd lines %zd bytes\n", lns, bytes);
   fclose(f);

   rv = fprintf(stderr, "This on std error\n");
   fprintf(stderr, "Got rv %d (bytes written to stderr)\n", rv);
   printf("This on stdout\n");

   f = popen("literal hello there|insert /Console:  /|cons|count lines|insert /Wrote /|cons", "w");
   if (!f) printf("popen fail %m\n");
   else
   {
      printf("pipe fd %d open\n", fileno(f));
      i = fputs("here goes\ntwo lines\n", f);
      if (ferror(f)) printf("fd %d %m", fileno(f));
      printf("closing pipe fd %d.\n", fileno(f));
      pclose(f);
   }

   errno = 0;
   printf("Should be one line only:  ");
   printf(" %m .. end of single line\n");
   return system("id");
}
