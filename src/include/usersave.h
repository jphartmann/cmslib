#if !defined(_JPH_USERSAVE_H)
   #define _JPH_USERSAVE_H
/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - USERSAVE                                              @SI1469E */
/*                                                              @SI1469E */
/* Description - User Save Area                                 @SI1469E */
/*                                                              @SI1469E */
/* DSECT - USERSAVE                                             @SI1469E */
/*                                                              @SI1469E */
/* Function - Maps the area pointed to by R13 upon              @SI1469E */
/*            entry to a program called by SVC.                 @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
struct usersave
{
   union
   {
      double __fill1[12];             /* Reserved for the user.      */
      struct
      {
         int smallsave[4];            /* Minimal save area up to R14 */
         int gcc390global[20];        /* For library use             */
      };
   };
   unsigned char usectyp;      /* Contains CALLTYP value. */
   unsigned char useuflg;      /* Contains UFLAGS value. */
   unsigned char __fill3[2];   /* Reserved for IBM use. */
   unsigned char usemflg;      /* Miscellaneous bits. */
/*                                  only valid if invoked by CMSCALL.    */
/*                                  CMSCALL issued              @VR1BR4Z */
   unsigned char __fill4[3];   /* Reserved for IBM use. */
};

enum usersave_enum
{
   usecms = 0x80,              /* Invoked by CMSCALL. */
   usea31 = 0x40,              /* Caller's AMODE is 31. */
   usescblk = 0x20,            /* SCBLOCK is available in R2. */
   useplist = 0x10,            /* Extended PLIST available in R0, */
   usear = 0x08,               /* Caller was in AR-mode when  @VR1BR4Z */
};
#endif
