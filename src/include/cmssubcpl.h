/* CMS SUBCOM parameter list                                         */
/*                                John Hartmann 13 Sep 2012 15:18:37 */

/*********************************************************************/
/* Change activity:                                                  */
/*13 Sep 2012  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_CMSSUBCPL_H)
   #define _JPH_CMSSUBCPL_H

#if !defined(__OSJ)
typedef int (__subcom)
   (struct usersave * usv, struct eplist * epl, void * vp);
#endif

struct scpl
{
   char verb[8];                      /* =SUBCOM                     */
   char name[8];                      /* subcommand name             */
   unsigned char flag1;               /* 0                           */
   unsigned char flag2;               /* 0xe0                        */
   unsigned char flag3;               /* 0                           */
   unsigned char flag4;               /* 0                           */
   __subcom * handler;   /* Handler/clear if 0/anchor 1/query ffffffff */
   void * userword;                   /* User word                   */
};

#endif
