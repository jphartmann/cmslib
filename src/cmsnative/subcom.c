/* Allow application to register subcommand callbacks                */
/*                                 John Hartmann 6 Oct 2011 15:51:55 */

/*********************************************************************/
/* Change activity:                                                  */
/* 6 Oct 2011  New module.                                           */
/*********************************************************************/

#include <cmsbase.h>
#include <cmsthreadglobal.h>
#include <cmssubcom.h>
#include <scblock.h>

#include <stdlib.h>
#include <string.h>
#include <cmssubcpl.h>

struct cmssubcom
{
   char eye[4];
   #define SUBEYE "subc"
   struct _cmsthreadglobal * gbl;      /* For recursion               */
   struct cmssubcom * next;
   char name[8];
   cmssubcomcallback cb;
   void * userword;
};

extern __subcom __subcmd;
static struct cmssubcom * subcoms;

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

/*********************************************************************/
/* Register subcommand handler                                       */
/*********************************************************************/

enum cmssubcomreason
cmssubcr(const char * name, int flags, cmssubcomcallback cb,
   void * userword)
{
   int len;
   char nm[8];
   struct cmssubcom * sb;
   struct scpl pl = { "SUBCOM  ", flag2: 0xe0, };
   struct _cmsthreadglobal * gbl = __getgbl();
   int rv;

   #define ER(x) return (cmssub_ ## x)

   if (!name) ER(noname);
   len = strlen(name);
   if (8 < len) ER(namelong);
   if (!cb) ER(nocallback);
   memset(nm, ' ', sizeof(nm));
   memcpy(nm, name, len);

   for (sb = subcoms; sb; sb = sb->next)
   {
      if (!memcmp(nm, sb->name, 8)) ER(exists);
   }

   sb = calloc(1, sizeof(*sb));
   if (!sb) ER(nocore);

   memcpy(sb->eye, SUBEYE, 4);
   memcpy(sb->name, nm, 8);
   sb->cb = cb;
   sb->userword = userword;
   sb->gbl = gbl;
   memcpy(pl.name, sb->name, 8);
   pl.userword = sb;
   pl.handler = __subcmd;
   rv = __svc204(NULL, pl.verb, 0, NULL);

   switch (rv)
   {
      case 0:
         break;
      case 20:
         free(sb);
         ER(badname);
      case 25:
         free(sb);
         ER(nocmscore);
      default:
         free(sb);
         ER(badcms);
   }

   sb->next = subcoms;
   subcoms = sb;
   return cmssub_ok;
}

/*********************************************************************/
/* Dismantle subcommand.                                             */
/*********************************************************************/

enum cmssubcomreason
cmssubdl(const char * name)
{
   struct cmssubcom * sb;
   struct cmssubcom ** psb;
   struct scpl pl = { "SUBCOM  ", };
   int rv;
   int len;
   char nm[8];

   if (!name) ER(noname);
   len = strlen(name);
   if (8 < len) ER(namelong);
   for (psb = &subcoms; (sb = *psb); psb = &sb->next)
   {
      if (!memcmp(sb->name, name, 8)) break;
   }
   if (!sb) ER(nonesuch);
   *psb = sb->next;                   /* Unchain                     */
   memset(nm, ' ', sizeof(nm));
   memcpy(nm, name, len);
   memcpy(pl.name, sb->name, 8);
   rv = __svc204(NULL, pl.verb, 0, NULL);
   switch (rv)
   {
      case 0:
         break;
      case 1:
         ER(nonesuch);
      default:
         ER(badcms);
   }

   return cmssub_ok;
}


/*********************************************************************/
/* Exit to drive actual callback.                                    */
/*********************************************************************/

int
cmssubex(struct scblock * scb, struct cmssubcom * sb, struct usersave * usv,
   struct eplist * epl)
{
   /* __sayf("Invoking %s/n", sb->name);                             */
   return sb->cb(usv, epl, sb->userword);
}
