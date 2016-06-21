/* Interface to CSL routines                                         */
/*                                John Hartmann 20 Jun 2011 06:32:04 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New module.                                           */
/*********************************************************************/

#include <csl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include <cmsbase.h>

enum __csl_debug __csldbg;
int __cslrc;
int __cslrsn;

#include "csldec.c"

/* Forward declarations:                                             */
static void csldump(const int count, const char * name, const int ** plist);
/* End of forward declarations.                                      */

/*********************************************************************/
/* Build  plist in core and call the interface routine to set up the */
/* type-1 environment.                                               */
/*********************************************************************/

int
tocsl(const int count, const char * pname, ...)
{
   va_list arg;
   const int * plist[count+1];
   int i;
   static char * cslerrs[]=
   {
      "Routine was not loaded.",
      "Routine has been dropped.",
      "Insufficient virtual storage available.",
      "Too many parameters specified.",
      "Not enough parameters specified.",
      "CSL does not exist on the release.",
   };
   char name[9];

   sprintf(name, "%-8.8s", pname);      /* Get trailing blanks         */
   va_start(arg, pname);
   plist[0]=(int *) name;

   for (i=1; count >=i; i++)
   {
      plist[i] = va_arg(arg, void *);
   }
   plist[count] = (void *) (0x80000000 | (int) plist[count]);
   va_end(arg);

   i=__csl(plist);
   __cslrc=*plist[1];
   __cslrsn=*plist[2];

   if (0 > __cslrc) switch (__cslrc)
   {
      case -7:
      case -8:
      case -9:
      case -10:
      case -11:
      case -12:
         __sayf("CSL Error %d calling %.8s:  %s", __cslrc, name, cslerrs[-__cslrc - 7]);
         break;
   };

   switch (__csldbg)
   {
      case __csl_quiet:
         break;
      case __csl_error:
         if (0==__cslrc) break;
      case __csl_verbose:
         csldump(count, name, plist);
   }

   return i;
}

static int
cslcmp(const void * l, const void * r)
{
   const char * lc = (const char *) l;
   const struct cslcall * cc = (const struct cslcall *) r;

   #if 0
   __sayf("Key %.8s comp %.8s", lc, cc->name);
   #endif
   return memcmp(cc->name, lc, 8);
}

static void
csldump(const int count, const char * name, const int ** plist)
{
   extern struct cslcallinfo cslinfo;
   int i;
   const struct cslcall * cl;
   const struct cslparm * pm;
   char bfr[256];
   int len;
   const void * vp;
   const char * cp;
   int ip;
   int tcount;
   static char * dect[]=
   {
      "char",
      "fchr",
      "sbin",
      "table_char",
      "table_sbin",
   };

   cl = bsearch(name, cslinfo.calls, cslinfo.count, sizeof(struct cslcall), &cslcmp);
   if (cl)
      __sayf("%.8s rc %2d reason %5d count %d min %d max %d",
         name, __cslrc, __cslrsn, count, cl->minparms, cl->maxparms);
   else
   {
      __sayf("%.8s rc %2d reason %5d (not found)", name, __cslrc, __cslrsn);
      return;
   }

   for (pm = cl->first, i=1; count >= i; i++, pm++)
   {
      len=sprintf(bfr, "%2d %c%c%c %s ", i,
         "-r"[pm->required], "-i"[pm->input], "-o"[pm->output], dect[pm->type]);
      int j;

      vp=plist[i];
      #define SP(x...) len += sprintf(bfr+len, x)
      switch (pm->type)
      {
         case t_char:                 /* character                   */
            cp = vp;
            /* Character may also mean binary                        */
            for (j = 0; pm->length > j; j++)
               if (!isprint(0xff & cp[j]))
               {
                  j = -1;
                  break;
               }
            if (0 <= j)  SP("\"%.*s\"", pm->length, cp);
            else
            {
               SP("x'");
               for (j = 0; pm->length > j; j++)
               {
                  if (j && !(j % 8)) SP(" ");
                  SP("%02x", cp[j]);
               }
               SP("'");
            }
            break;
         case t_fchr:                 /* char with length            */
            cp = vp;
            ip = * plist[++i];
            len+=sprintf(bfr+len, "len %3d \"%.*s\"", ip, ip, cp);
            break;
         case t_sbin:                 /* integer                     */
            len+=sprintf(bfr+len, "%d", * plist[i]);
            break;
         case t_table_char:           /* Table of character args     */
         case t_table_sbin:           /* Table of signed bin args    */
            tcount = * plist[i];
            len += sprintf(bfr+len, "table of %d objects", tcount);
            i += tcount;
            break;
         default:
            assert(0);
      }
      __says(bfr, len);
   }
}

/*********************************************************************/
/* Call a function that has OS linkage                               */
/*********************************************************************/

int
oscall(int (* f)(void), int count, ...)
{
   va_list arg;
   void * plist[count];
   int i;

   va_start(arg, count);
   for (i=0; count > i; i++)
   {
      plist[i]=va_arg(arg, void *);
   }
   plist[count-1] = (void *) (0x80000000 | (int) plist[count-1]);
   va_end(arg);

   i=__oscall(f, plist);
   return i;
}
