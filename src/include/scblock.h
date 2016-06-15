#if !defined(__H_SCBLOCK)
#define __H_SCBLOCK

/* the  layout  below  is  correct  only on bigendian 31 bit systems */
/* which  may  or  may  not  run  CMS.   Otherwise  it is simply a C */
/* structure.                                                        */

/*                                                              @V6BD7G9 */
/*noprint                                                       @SG8859E */
/***      SCBLOCK - SUBCOMMAND CONTROL BLOCK                    @V6BD7G9 */
/*                                                              @V6BD7G9 */
/*            0 +-------------------+-------------------+       @V6BD7G9 */
/*              |      SCBFWPTR     |      SCBWKWRD     |       @V6BD7G9 */
/*            8 +-------------------+-------------------+       @V6BD7G9 */
/*              |                SCBNAME                |       @V6BD7G9 */
/*           10 +---------------------------------------+       @V6BD7G9 */
/*              |                SCBPSW                 |       @V6BD7G9 */
/*           18 +-------------------+-------------------+       @V6DF9DA */
/*              |       SCBXORG     |      SCBXLEN      |       @V6DF9DA */
/*           20 +----+--------------+-------------------+       @VA34091 */
/*              | F*2|  Available   |      SCBSEGID     |       @VA34091 */
/*           28 +----+--------------+-------------------+       @VA34091 */
/*              |       SCBSEGID    |      SCBTESTK     |       @VA34091 */
/*           30 +-------------------+-------------------+       @VA34091 */
/*                                                              @VA34091 */
/* NOTE: also change EXISBLK if the size of SCBLOCK changes.    @VA34091 */
/*                                                              @VA34091 */
/***      SCBLOCK - SUBCOMMAND CONTROL BLOCK                    @V6BD7G9 */
/*enoprint                                                      @SG8859E */
/*                                                              @V6BD7G9 */
/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - SCBLOCK                                               @SI1469E */
/*                                                              @SI1469E */
/* Description - Subcommand Control Block                       @SI1469E */
/*                                                              @SI1469E */
/* DSECT - SCBLOCK                                              @SI1469E */
/*                                                              @SI1469E */
/* Function - The SCBLOCK describes the dynamic                 @SI1469E */
/*            entry point for the SUBCOM function and is        @SI1469E */
/*            dynamically allocated from free storage by        @SI1469E */
/*            DMSITS.                                           @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
struct scblock
{
   struct scblock * scbfwptr; /* CHAIN POINTER TO NEXT SCBLOCK    @V6BD7G9 */
   void * scbwkwrd;            /* AVAILABLE FOR USER INFORMATION   @V6BD7G9 */
   unsigned char scbname[8];   /* NAME OF SUBCOMMAND ENVIRONMENT   @V6BD7G9 */
   union
   {
      double scbpsw[0];           /* STARTING PSW FOR SUBCOMMAND      @V6BD7G9 */
#if defined (__OSJ)
      __subcom * handler;             /* Handler if simulated        */
#endif
   };
   unsigned char scbint;       /* PSW INTERRUPT BITS               @VA59251 */
/*                                                              @VA38649 */
/* The following table shows the combination of bits            @VA38649 */
/* in SCBPSW that determine what the various INTTYPEs are.      @VA38649 */
/*                                                              @VA38649 */
/*noformat                                                      @SG8859E */
/* INTTYPE             |BIT 0|BIT 1|    |BIT 7|HEX value        @VA38649 */
/* --------------------------------------------------------     @VA38649 */
/* NONE                   0     0    ...   0     00             @VA38649 */
/* EXTERNAL               0     0    ...   1     01             @VA38649 */
/* NONCONSOLE             0     1    ...   0     40             @VA38649 */
/* NONCONSOLE & EXTERNAL  0     1    ...   1     41             @VA38649 */
/* CONSOLE                1     0    ...   0     80             @VA38649 */
/* CONSOLE & EXTERNAL     1     0    ...   1     81             @VA38649 */
/* IO                     1     1    ...   0     C0             @VA38649 */
/* ALL                    1     1    ...   1     C1             @VA38649 */
/*                                                              @VA38649 */
/*enoformat                                                     @SG8859E */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *@V6DF9DA */
/*        NUCX FIELDS.  THESE ARE PRESENT, BUT NOT USED,       *@V6DF9DA */
/*        IN SCBLOCKS ON THE NUCSCBLK CHAIN.                   *@V6DF9DA */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *@V6DF9DA */
   unsigned char scbkey;       /* PSW KEY                          @VA59251 */
   unsigned char scbsflag;     /* SYSTEM FLAG BYTE.                @V6SS0KB */
/*        WILL NOT BE AUTOMATICALLY DELETED DURING ABEND        @V6DF9DA */
/*        PROCESSING.                                           @V6DF9DA */
/*        WILL BE CALLED WITH "PURGE" ARGUMENT DURING ABEND     @V6DF9DA */
/*        PROCESSING.                                           @V6DF9DA */
/*                                 PROCESSING.                  @V6DF9DA */
/*                                 ROUTINE                      @V6GM4T6 */
/*                                 PROCESSING.                  @V6GM4T6 */
/*                                 EXTENSION WON'T BE DELETED   @VR100KB */
/*                                 DURING NUCXDROP ALL PROCESS  @VR100KB */
/*                                 EXTENSION CAN ALSO BE CALLED @V6GM3H9 */
/*                                 AS AN IMMEDIATE COMMAND      @V6GM3H9 */
/*                                 EXTENSION TEMPORARILY.       @VA17031 */
   unsigned char scbuflag;     /* USER FLAG BYTE.                  @V6SS0KB */
/*                                                              @V6DF9DA */
/*                                                              @V6DF9DA */
   void * scbentr;             /* ENTRY POINT ADDRESS IN PSW       @V6SS0KB */
/*                                                              @V6SS0KB */
   void * scbxorg;             /* ADDRESS WHERE NUCLEUS        @V6DF9DA */
/*        EXTENSION WAS LOADED IN FREE STORAGE.                 @V6DF9DA */
/*                                                              @V6DF9DA */
   int scbxlen;                /* LENGTH IN BYTES OF NUCLEUS   @V6DF9DA */
/*        EXTENSION.  MAY BE ZERO FOR SECONDARY ENTRY POINTS.   @V6DF9DA */
/*                                                              @V6DF9DA */
   unsigned char scbsflg2;     /* F*2 SECOND FLAG BYTE             @VA34091 */
/*        WHEN BOTH ON, EXTENSION IS AMODE ANY,                 @V6PXVLZ */
/*        WHEN BOTH OFF, EXTENSION IS AMODE SAME.               @V6PXVLZ */
/*                               invoked from the command line           */
   unsigned char __fill1[3];   /* RESERVED FOR FURTURE USE     @V6PXVLZ */
   unsigned char scbsegid[8];  /* LOGICAL SEGMENT IDENTIFIER       @V6RXPVC */
   int scbtestk;               /* thread execomm stack             @VR2LML7 */
};

enum
{
   scbsfsys = 0x80,            /* DENOTES "SYSTEM" ROUTINE --  @V6DF9DA */
   scbsfser = 0x40,            /* DENOTES "SERVICE" ROUTINE -- @V6DF9DA */
   scbsfabn = 0x20,            /* USED DURING ABEND            @V6DF9DA */
   scbsfend = 0x10,            /* DENOTES 'END OF COMMAND'     @V6GM4T6 */
   scbsfint = scbsfabn,        /* USED DURING END OF COMMAND   @V6GM4T6 */
   scbsperm = 0x08,            /* DENOTES THAT THIS NUCLEUS    @VR100KB */
   scbsfimm = 0x04,            /* DENOTES THAT THIS NUCLEUS    @V6GM3H9 */
   scbsfx = 0x02,              /* DENOTES A LOOK-ASIDE         @V6DF9DA */
   scbshide = 0x01,            /* USED TO HIDE A NUCLEUS       @VA17031 */
   scbsfa31 = 0x80,            /* EXTENSION IS AMODE 31        @V6PXVLZ */
   scbsfa24 = 0x40,            /* EXTENSION IS AMODE 24        @V6PXVLZ */
   scbsfseg = 0x20,            /* SEGMENT RESIDENT             @V6PXPVC */
   scbsfunc = 0x10,            /* Indicate function can not be     S5U29592 */
   scbsmt = 0x08,              /* mt subcom                      @V6PXPVC */
   scbstprv = 0x04,            /* thread private subcom          @V6PXPVC */
};
#endif
