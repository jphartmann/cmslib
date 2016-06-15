/*                                                                   */
/*                                John Hartmann 24 Jan 2015 16:21:38 */

/*********************************************************************/
/* Test driver for the scanner.                                      */
/*                                                                   */
/* This program can run on the workstation.                          */
/*                                                                   */
/* Change activity:                                                  */
/*24 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Forward declarations:                                             */
static int scanopen(int fd, const char * name, const char * mode);
/* End of forward declarations.                                      */

#define __sayf printf
#define FSMDEBUG 1

#include "scanarg.c"

int
main(int argc, char ** argv)
{
   int tokens = 0;
   int bytes = 0;
   void * vp;
   char ** ap;
   char * tks;
   int i;
   int rv;
   int wtok = -1;
   int wchr = -1;
   int wrc = 0;
   int wbs = 0;
   int bsize;
   int nmts;
   int debug = 0;

   if (1 < argc && !strcmp("-d", argv[1]))
   {
      debug = 1;
      argc--;
      argv++;
   }

   if (2 > argc)
   {
      fprintf(stderr, "No arguments specified.\n");
      return 4;
   }

   if (3 <= argc) wtok = strtol(argv[2], NULL, 10);
   if (4 <= argc) wchr = strtol(argv[3], NULL, 10);
   if (5 <= argc) wbs  = strtol(argv[4], NULL, 10);
   if (6 <= argc) wrc  = strtol(argv[5], NULL, 10);

   printf("Processing string >|%s|<", argv[1]);
   if (0 <= wtok || 0 <=wchr) printf(" want");
   if (0 <= wtok) printf(" %d tokens", wtok);
   if (0 <= wtok || 0 <=wchr) printf(" and");
   if (0 <=wchr) printf(" %d characters", wchr);
   printf(".");
   if (wrc) printf("  Expect pass 1 return code %d.", wrc);
   printf("\n");

   rv = __cntargs(argv[1], strlen(argv[1]), &tokens, &bytes, &bsize, debug);

   if (rv)
   {
      if (rv == wrc) printf("Pass 1 returns expected rv=%d.\n\n", rv);
      else printf("!>>> Pass 1 expect rv %d; got %d. <<<\n\n", wrc, rv);
      return rv;
   }

   if (3 < argc)
   {
      nmts = (tokens != wtok) + (bytes != wchr) + (bsize != wbs);
      if (nmts)
      {
         printf("!>>> Incorrect count%s:", nmts > 1 ? "s" : "");
         if (tokens != wtok) printf("  %d tokens wanted; got %d.", wtok, tokens);
         if (bytes != wchr) printf("  %d characters wanted; got %d.", wchr, bytes);
         if (bsize != wbs) printf("  %d characters wanted for filename buffer; got %d.", wbs, bsize);
         printf(" <<<\n\n");
         return 4;
      }
   }

   printf("Pass 1: %d tokens %d bytes %d filename buffer OK.\n", tokens, bytes, bsize);

   vp = malloc((tokens + 1) * sizeof(void *) + bytes);
   ap = vp;
   tks = (char *) (ap + tokens + 1);
   tokens = __doargv(argv[1], strlen(argv[1]), ap, tks, bsize, debug);

   printf("Pass 2:  argv %d\n", tokens);

   for (i = 0; ap[i]; i++)
      printf("%3d >>>%s<<<\n", i, ap[i]);

   printf("\n");
   return 0;
}

static int
scanopen(int fd, const char * name, const char * mode)
{
   printf("Open fd %d mode %s for '%s'\n", fd, mode, name);
   return 0;
}
