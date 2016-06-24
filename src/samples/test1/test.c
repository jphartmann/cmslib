/* Another test case                                                 */
/*                                 John Hartmann 6 Oct 2011 18:58:30 */

/*********************************************************************/
/* Change activity:                                                  */
/* 6 Oct 2011  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmsbase.h>
#include <eplist.h>
#include <cmssubcom.h>
#include <usersave.h>

static const char bfile[] = "test1.data";

/* Forward declarations:                                             */
static int sub(struct usersave * usv, struct eplist * epl, void * vp);
/* End of forward declarations.                                      */

int
main(int argc, char ** argv, char ** env)
{
   enum cmssubcomreason rsn;
   int rv;
   char * str = "metest howdy there";
   struct eplist epl = {str, str + 7, str + strlen(str), 0};
   struct
   {
      char pl[3*8];
      char f[8];
   } p =
   {
      "METEST  " "HOWDY   " "THERE   ",
      FENCE,
   };
   char subc[3][8] = {"EXEC    ", "SUBMAP  ", FENCE};
   #define SAY(x) __say(x, strlen(x))
   FILE * f;

   printf("env %p [0] %p [1] %p extern %p\n", env, env[0], env[1], environ);
   for (; env && *env; env++)
   {
      printf("%s\n", * env);
   }
   printf("var %s\n", getenv("var"));


   rsn = cmssubcr("METEST", 0, &sub, "abc");
   printf("Register subcom rv %d\n", rsn);
   if (rsn) return rsn;
   SAY("Subcom chain:");
   rv = __svc204(0, subc[0], 0, 0);
   printf("End of subcom chain.  SUBMAP rv %d\n", rv);

   rv = __svc204(&epl, p.pl, 2 << 24, 0);
   printf("Subcom rv %d 0x%x\n", rv, rv);

   rv = system("jrexx gotest");
   printf("jrexx rv %d\n", rv);
   rv = cmssubdl("METEST");
   printf("Delete RV %d.  Subcom chain after delete:\n", rv);
   __svc204(0, subc[0], 0, 0);

/*********************************************************************/
/* Read a file that contains the record number as an integer.        */
/*********************************************************************/

   f = fopen(bfile, "rb");
   if (!f) printf("Cannot open %s:  %m\n", bfile);
   else
   {
      int i = 0, k;
      int ok = 1;

      printf("opened %s. eof %d\n", bfile, feof(f));
      for (i = 1; !feof(f); i++)
      {
         int rv;

         k = -1;
         rv = fread(&k, sizeof(k), 1, f);
         if (ferror(f))
         {
            printf("Could not read record %d\n", i);
            ok = 0;
            break;
         }

         if (feof(f)) break;

         if (1 != rv)
         {
            printf("Did not get 4 bytes for %d.  Got %d.\n", i, rv);
            ok = 0;
            break;
         }
         if (i != k)
         {
            printf("Expect %d; got %d\n", i, k);
            ok = 0;
            break;
         }
      }
      fclose(f);
      if (ok) printf("%d records read from filled\n", i);
   }
   return 0;
}

static int
sub(struct usersave * usv, struct eplist * epl, void * vp)
{
   char * s = vp;
   int vl = epl->eplargbg - epl->eplcmd;
   int al = epl->eplargnd - epl->eplargbg;

   printf("epl %p vp %s %p %p %p %p\n", epl, s,
      epl->eplcmd, epl->eplargbg, epl->eplargnd, epl->epluword);
   printf("verb '%.*s' : '%.*s'\n", vl, epl->eplcmd, al, epl->eplargbg);
   return 0;
}
