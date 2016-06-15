/* Traceback                                                         */
/*                                John Hartmann 10 May 2014 13:30:00 */

/*********************************************************************/
/* Change activity:                                                  */
/*10 May 2014  New module.                                           */
/*********************************************************************/

#include <cmsbase.h>
#include <stdio.h>
#include <string.h>

struct offstable                /* Offsets in file related to source */
{
   unsigned short fileix;             /* Where to find it            */
   unsigned short line;               /* Line number                 */
   unsigned int fileoffs;             /* Where in module             */
};

struct modhead                        /* First bit of a module       */
{
   char fname[8];                     /* Base component              */
   char isodate[8];                   /* When assembled              */
   char time[8];                      /* do.                         */
   int fncount;                       /* Number of source files      */
   int * fnix;                        /* Index to file names         */
   char * fnames;                     /* File names.  Add fnix       */
   struct offstable * oft;            /* The offset table            */
};

struct gccstack
{
   struct gccstack * backchain;       /* Not usually stored          */
   int reserved;
   void * r2[4];                      /* Volatile regs not saved     */
   void * r6[10];                     /* Saved registers, as needed  */
   double fprs[4];                    /* Floating point              */
   /* Parameter area                                                 */
};

struct fplx
{
   int headoffs;                    /* Top of module               */
   char kw[4];                        /* = fplx                      */
};

/* Forward declarations:                                             */
static int printframe(struct gccstack * sp);
static void * stripam(void * vp);
/* End of forward declarations.                                      */

/*********************************************************************/
/* This  is  a  bit  tricky.   When a function is entered, the stack */
/* pointer   is   decremented,   but  not  other  initialisation  is */
/* performed.   Here  we  are lucky in storing the stack pointer and */
/* then  calling  a  function,  which  stores  R13  as  the  base of */
/* __traceb.  Or perhaps that was by design.                         */
/*********************************************************************/

void
__traceb(void)
{
   struct gccstack * sp = __stktop();

   __say("traceback:", -1);
   do
   {
      int fsize = printframe(sp);
      void * vp;
      char * cp;

      if (!fsize) return;
      cp = vp = sp;
      cp -= fsize;
      sp = vp = cp;
   } while (1);
}

static int
printframe(struct gccstack * sp)
{
   char * cb = stripam(sp->r6[13 - 6]);       /* Get base for caller */
   char * cr14 = stripam(sp->r6[14 - 6]);         /* Address of call */
   int nlen = 0;
   short int fsize;
   struct fplx * fplx = NULL;
   int i = 0;

   if (!cb)
   {
      __WERROR("No gpr13");
      return 0;
   }

   while (0x60 == cb[i]) i += 4;       /* STD                         */

   if (0xa7 != cb[i] || 0xfa != cb[i + 1])
   {
      __WERROR("No stack decrement %p + %x:  %02x%02x",
         cb, i, cb[i], cb[i + 1]);
      #if 0
      #endif
      return 0;
   }

   fsize = (cb[i + 2] << 8) | cb[i + 3];

   cb -= 2;                           /* Back up over BASR 13,0      */
   if (0x0d != cb[0] || 0xd0 != cb[1])
   {
      __WERROR("BASR 13,0: %02x%02x", cb[0], cb[1]);
      return 0;
   }

   cb -= 4;                           /* Back up over stm            */
   if (!memcmp(cb - 4, "fplx", 4))
   {
      void * vp = cb - 8;

      fplx = vp;
      cb -= 8;
   }

   while (!cb[-1]) cb--;
   if ('<' == *--cb && '<' == *--cb)
   {
      for (; '>' != cb[-1]; nlen++, cb--) ;            /* Nothing */
   }

   if (nlen && !fplx)
      __sayf("Function %.*s frame size %x", nlen, cb, -fsize);
   if (nlen && fplx)
   {
      char * mhead = fplx->kw - 4 - fplx->headoffs;
      void * vp = mhead;
      struct modhead * mh = vp;       /* First bit of a module       */
      int r14 = (int) cr14;
      struct offstable * ot = mh->oft;
      char chb[4096];

      chb[0] = 0;
      r14 -= (int) mhead;          /* Offset in module            */

      if (0 >= r14) __WERROR("Bad r14: %x call %p mhead %p",
         r14, cr14, mhead);
      else
      {
         while (ot[1].fileoffs < r14) ot++;
         sprintf(chb, " %s line %d",
            mh->fnames + mh->fnix[ot->fileix], ot->line);
      }

      __sayf("Function %-15.*s frame size %x file %.8s %.8s %.5s from %s",
         nlen, cb, -fsize, mh->fname, mh->isodate, mh->time, chb);
   }

   #if 0
   __WERROR("R13 %p %p %p", sp->r6[13 - 6], sp->r6[14 - 6], sp->r6[15 - 6]);
   #endif

   /* This guy is not null terminated.                               */
   if (7 == nlen && !memcmp("cmsmain", cb, 7)) return 0;     /* Done */
   return fsize;
}

static void *
stripam(void * vp)
{
   int i = (int) vp;

   i &= 0x7fffffff;

   return (void *) i;
}
