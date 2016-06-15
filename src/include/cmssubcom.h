/* CMS subcommand support.                                           */
/*                                 John Hartmann 6 Oct 2011 15:48:44 */

/*********************************************************************/
/* This is not a direct exposure of the SUBCOM macrom, as we need to */
/* be rather careful about the stack.  Thus, the program can declare */
/* subcommand callbacks; these will be active only while the program */
/* is  activly  in  CMSCALL  processing  entered  by  __svc204()  or */
/* anything that calls it.                                           */
/*                                                                   */
/* Change activity:                                                  */
/* 6 Oct 2011  New header file.                                      */
/*********************************************************************/

#if !defined(_JPH_CMSSUBCOM_H)
   #define _JPH_CMSSUBCOM_H

#include <eplist.h>
#include <usersave.h>

enum cmssubcomreason
{
   cmssub_ok,                         /* Done                        */
   cmssub_noname,                     /* Name null                   */
   cmssub_namelong,                   /* Name longer than 8          */
   cmssub_nohandle,                   /* Handle pointer null         */
   cmssub_nocallback,                 /* Callback is null            */
   cmssub_exists,                     /* Handler already active      */
   cmssub_nocore,                     /* Unable to allocate storage  */
   cmssub_badname,                    /* Name contains bad char      */
   cmssub_nocmscore,               /* CMS Unable to allocate storage */
   cmssub_badcms,                    /* Undocumented CMS return code */
   /* For delete                                                     */
   cmssub_nonesuch,                 /* No such subcommand registered */
   cmssub_gone,                       /* CMS does not know of it     */
};

typedef int (* cmssubcomcallback) (struct usersave * usave,
   struct eplist * epl, void * userword);

extern enum cmssubcomreason cmssubcr(const char * name, int flags,
   cmssubcomcallback cb,
   void * userword);

extern enum cmssubcomreason cmssubdl(const char * name);

#endif
