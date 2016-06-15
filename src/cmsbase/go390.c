/* C start-up for gcc390                                             */
/*                                John Hartmann 16 Jun 2011 09:14:22 */

/*********************************************************************/
/* Code  to  build  the  argc  argv  expected by main and set up the */
/* standard files with redirect.                                     */
/*                                                                   */
/* Also various constants for the library.                           */
/*                                                                   */
/* Change activity:                                                  */
/*30 Jul 2011  +++ Add redirection.                                  */
/*16 Jun 2011  New module.                                           */
/*********************************************************************/

#define _CMSNOMAIN
#include <cmsbase.h>
#include <eplist.h>
#include <usersave.h>
#include <nucon.h>
#include <svcsave.h>
#include <cmsthreadglobal.h>

#include <string.h>
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <csl.h>

#define WS " \t"

#define DEBUG 0

extern int main(int argc, char ** argv, char ** envp);
extern void __exit(int rc);
extern char ** environ;
extern void __halt(void * arg, ...);
extern void _diag008(const char * string, int length);

static const char * getenvstrs =
   "(end ?)"
   "?command GLOBALV SELECT ENVIRON LIST"
   "|drop 1"                          /* Drop select table is        */
   /* Endicott pipes have no substr                                  */
   "|spec 2-* 1"                      /* Drop leading blank          */
   "|c:count lines bytes"
   "|buffer"
   "|addrdw cms4"
   "|i: fanin 1 0"
   "|d: fanout"                       /* To fitting                  */
   "?c:"
   "|spec w1 d2c 1 w2 d2c n"
   "|i:"
   "?d:"
   ;

int __fpldbg;

/* Forward declarations:                                             */
static int ouroption(char * t);
static int scanopen(int fd, const char * name, const char * mode);
static int __cntargs(const char * s, int len, int * tc, int * bc, int * bsize, int debug);
static int __doargv(const char * s, int len, char ** av, char * t, int bsize, int debug);
static void readenv(FILE * p, void * vp, const int lines);
/* End of forward declarations.                                      */

/*********************************************************************/
/* Entry  from  CMS  via  run390  assembler  interface to set up the */
/* stack.                                                            */
/*                                                                   */
/* Note  that  all  allocas must be done in the main routine so that */
/* the stack storage remains intact.                                 */
/*********************************************************************/

int
cmsmain(struct eplist * epl, char (* pl)[8], struct usersave * us,
   struct _cmsthreadglobal * gbl)
{
   char ** ap;                        /* argv                        */
   char * tks;
   int len;
   char ** ev = NULL;                 /* Environment                 */
   int tokens;                        /* argc                        */
   int bytes;
   int bsize;                    /* Opaque between count and do args */
   int rv;

   if (!(useplist & us->usemflg))
   {
      __sayf("extended parameter list required");
      return EINVAL;
   }

   gbl->flag2 |= _errno_verbose | _errno_traceback;

   __opnstd(gbl);                     /* So we can freopen           */

   len = epl->eplargnd - epl->eplcmd; /* Not until we know extended plist there */
   rv = __cntargs(epl->eplcmd, len, &tokens, &bytes, &bsize, 0);
   if (rv) return rv;

   ap = alloca((tokens + 1) * sizeof(void *) + bytes);
   tks = (char *) (ap + tokens + 1);
   rv = __doargv(epl->eplcmd, len, ap, tks, bsize, 0);
   if (rv) return rv;

   while (ouroption(ap[1]))
   {
      ap[1] = ap[0];                  /* Move verb                   */
      ap++;                           /* Forget one word             */
      tokens--;
   }

   if (__fpldbg) __WERROR("%d tokens. first two '%s' '%s'.", tokens, ap[0], ap[1]);

   if (~_noenvironment & gbl->flag1)
   {
      __WERROR("FIXME:  Flags have surplus bits: %02x, gbl %p",
         gbl->flag1, gbl);
   }
   if (_noenvironment & gbl->flag1)
   {
      __WERROR("Not building environment; flags are %02x, gbl %p",
         gbl->flag1, gbl);
   }
   else
   {
      FILE * p = popen(getenvstrs, "rb");

      if (p)
      {
         struct
         {
            int bytes;
            int lines;
         } px = {37, 9};      /* Bytes then words            */
         int rv = -5;

         rv = fread(&px, 4, 2, p);
         if (2 != rv) __WERROR("Did not get two items for sizes.  rv=%d", rv);
         else
         {
            int toget = px.bytes + px.lines      /* Text plus a null */
               + sizeof(char *) * (1 + px.lines) + 4;
            void * vp = alloca(toget);

            ev = vp;
            if (vp) readenv(p, vp, px.lines);
            else __sayf("Could not allocate %d bytes for environment.", toget);
         }
         pclose(p);
      }
   }

   environ = ev;                      /* Global pointer              */

   rv = main(tokens, ap, ev);

   exit(rv);
}

/*********************************************************************/
/* Read environment from global pool ENVIRON                         */
/*********************************************************************/

static void
readenv(FILE * p, void * vp, const int lines)
{
   char ** envp = vp;
   char * strs = vp;
   int i;
   int rv;

   strs += (sizeof(char *)) * (lines + 1);
   envp[lines] = NULL;

   for (i=0; lines > i; i++)
   {
      int len;

      envp[i] = strs;
      rv = fread(&len, sizeof(len), 1, p);
      if (1 != rv)
      {
         __sayf("Did not get one item for length rv=%d", rv);
         break;
      }
      rv = fread(strs, len, 1, p);
      if (1 != rv)
      {
         __sayf("Did not get one item for data rv=%d", rv);
         break;
      }
      strs[len] = 0;
      strs += len+1;
   }
}

/*********************************************************************/
/* See if option is one of ours.                                     */
/*********************************************************************/

static int
ouroption(char * t)
{
   if (!strcmp(t, "--fpl-csl-verbose"))
      __csldbg = __csl_verbose;
   else if (!strcmp(t, "--fpl-csl-error"))
      __csldbg = __csl_error;
   else if (!strcmp(t, "--fpl-debug"))
      __fpldbg++;
   else return 0;                     /* Not one of ours             */
   return 1;
}

/*********************************************************************/
/* Process the redirect option.                                      */
/*********************************************************************/

static int
scanopen(int fd, const char * name, const char * mode)
{
   if (__NFILE <= fd)
   {
      __WERROR("File descriptor %d is not available for reopen.", fd);
      return 40;
   }
   FILE * f = __userFiles[fd];
   f = freopen(name, mode, f);
   if (!f)
   {
      __WERROR("Could not reopen '%s' mode %s for file descriptor %d:  %m.",
         name, mode, fd);
      return 41;
   }
   return 0;
}

#include "scanarg.c"
