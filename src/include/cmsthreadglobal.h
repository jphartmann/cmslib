/* Runtime support global area.                                      */
/*                                 John Hartmann 6 Oct 2011 13:42:55 */

/*********************************************************************/
/* Area  on  top  of  the  [first]  stack  frame group.  This are is */
/* anchored in the user save area.  All stack frames have this, even */
/* those without a C library.                                        */
/*                                                                   */
/* When  using  multiple  stack  frames, the active frame pointer is */
/* saved  here  before  the  pointer  in the usersave is switched to */
/* point to another stack frame.                                     */
/*                                                                   */
/* Change activity:                                                  */
/* 6 Oct 2011  New header file.                                      */
/*********************************************************************/

#if !defined(_JPH_CMStGLOBAL_H)
   #define _JPH_CMStGLOBAL_H

struct _cmslibglobal;

enum _cmsgblflags
{
   _noenvironment     =  1,          /* Do not create an environment */
   _cmsactive         =  2,           /* In svc204.  currstack valid */
   _cmstg_fdsonheap   =  4, /* More file descriptors have been allocated */
   _cmstg_xitsonheap  =  8,      /* More atexits have been allocated */
};

enum _threadflag2
{
   _errno_verbose    =  1,           /* Display message on errno set */
   _errno_traceback  =  2,            /* Also display traceback      */
   /* This  is  used  eg when to undo some action in preparation for */
   /* reporting an error.                                            */
   _errno_hold       =  4,            /* Do not report errors        */
   _errno_report_held = 8,       /* Report anyhow (but do not store) */
};

typedef void (* __uexit)();

#define __INITIALFDS 10
#define __INITIALEXITS 4

/*********************************************************************/
/* Anything  from  here to and including at pstv is to be considered */
/* cast in concrete and under glass in Gentofte.  This also includes */
/* the enum _cmsgblflags                                             */
/*********************************************************************/

struct _cmsthreadglobal
{
   char id[8];                        /* = gcc390rt                  */
   int version, release, modification;
   int spare;
   /* Each  stack  frame  has  its own subpool; you may read that as */
   /* each thread has its own subpool.                               */
   char subpool[8];                   /* where to allocate           */
   struct cmslibglobal * libgbl;      /* To find anchor              */
   int stacksize;                  /* Actual allocation, in 4K pages */
   void * guardpage;                  /* Bottom of stack             */
   unsigned char guardkey;            /* Storage key of guard page   */
   unsigned char flag1;               /* Enum _cmsgblflags           */
   unsigned char flag2;               /* Enum _threadfalg2           */
   unsigned char res2;
   /* Lots of stuff must be disabled if the recursion count is >0 as */
   /* we need to do a cmsret to get back.  Long jumps stand out      */
   int recursion;                  /* Recursion count in this thread */
   void * environment;                /* Top of first stack frame    */
   void * currstack; /* Stack top (bottom really) when CMSCALL issued */
   void * pstv;               /* Pipeline services vector (mostly 0) */

   /* This is the open file table, indexed by file descriptor number */
   /* It  also  contains  the  FILE  structure,  so it is a bit of a */
   /* hybrid.                                                        */
   int numfds;               /* Number of file descriptors allocated */
   struct __file ** userFiles;        /* File pointers               */
   /* The inital allocation for this array.  The first three members */
   /* are never freed once allocated by __go390.  Thus references to */
   /* stdxxx return stable pointers.                                 */
   struct __file * prealloc[__INITIALFDS];     /* Initial allocation */

   int atexitcount;
   __uexit uexpre[__INITIALEXITS];

   /* End of area mapped in run390.copy                              */
   int errno;

   int exiting;
   __uexit * userExit;

   int errno_reason;                  /* Last reason code            */
   const char * errno_message;        /* Explanatory text            */
};

/* Return our global area                                            */
extern struct _cmsthreadglobal * __getgbl(void);

#endif
