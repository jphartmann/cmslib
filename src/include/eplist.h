#if !defined(__H_EPLIST)
#define  __H_EPLIST

/*                                                              @V6DEFT4 */
/***      EPLIST - EXTENDED PLIST DSECT                         @V6DEFT4 */
/*                                                              @V6DEFT4 */
/*            0 +-------------------+-------------------+       @V6DEFT4 */
/*              |      EPLCMD       |      EPLARGBG     |       @V6DEFT4 */
/*            8 +-------------------+-------------------+       @V6DEFT4 */
/*              |     EPLARGND      |      EPLUWORD     |       @VA35924 */
/*           10 +-------------------+-------------------+       @V6DEFT4 */
/*              |     EPARGLST      |      EPFUNRET     |       @V6GMAL1 */
/*           18 +-------------------+-------------------+       @V6GMAL1 */
/*                                                              @V6DEFT4 */
/***      EPLIST - EXTENDED PLIST DSECT                         @V6DEFT4 */
/*                                                              @V6DEFT4 */
/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - EPLIST                                                @SI1469E */
/*                                                              @SI1469E */
/* Description - Extended Parameter List DSECT                  @SI1469E */
/*                                                              @SI1469E */
/* DSECT - EPLIST                                               @SI1469E */
/*                                                              @SI1469E */
/* Function - EPLIST maps the extended parameter list passed    @SI1469E */
/*            between modules. EPLIST is found in the EPLIST    @SI1469E */
/*            macro.                                            @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
struct eplist
{
   const char * eplcmd;              /* ADDRESS OF COMMAND TOKEN.         @V6DEFT4 */
   const char * eplargbg;            /* ADDR OF BEGINNING OF ARGUMENTS.   @V6DEFT4 */
   const char * eplargnd;            /* ADDR OF END OF ARGUMENTS.         @V6DEFT4 */
   void * epluword;            /* USER WORD                         @VA35924 */
/*                                                              @VA35924 */
   void * eparglst;            /* ADDRESS OF FUNCTION ARGUMENT LIST.@V6GMAL1 */
   void * epfunret;            /* ADDRESS FOR RETURN OF FUNCTION    @V6GMAL1 */
/*                            DATA.                             @V6GMAL1 */
   void * __fill1[2];          /* PADDING (FOR USE WITH SCAN MACRO) @VA35924 */
   const char eplscant[0];  /* BEGINNING OF TOKENIZED PLIST      @VA35924 */
/*                              BUILT BY SCAN MACRO.            @VA35924 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *@V6DEFT4 */
/*                                                             *@V6DEFT4 */
/*        THE EXTENDED PLIST FLAGS INDICATE THE PRESENCE       *@V6DEFT4 */
/*        OF AN EXTENDED PLIST IN REGISTER 0. THE HIGH         *@V6DEFT4 */
/*        ORDER BYTE OF REGISTER 1 WILL CONTAIN EITHER         *@V6DEFT4 */
/*        EPLCMDFL OR EPLFNCFL TO INDICATE THE EXTENDED        *@V6DEFT4 */
/*        PLIST IS AVAILABLE.  ONLY THE FIRST 4 WORDS          *@VR110KB */
/*        OF THE EXTENDED PLIST ARE AVAILABLE WITH THESE       *@V6GMAL1 */
/*        CODES.                                               *@V6GMAL1 */
/*                                                             *@V6GMAL1 */
/*        IF THE HIGH ORDER BYTE OF REGISTER 1 CONTAINS        *@V6GMAL1 */
/*        EPFUNSUB, THEN THE INVOCATION IS AN EXTERNAL         *@V6GMAL1 */
/*        FUNCTION/SUBROUTINE CALL FROM REX.  WITH THIS        *@V6GMAL1 */
/*        PLIST, ALL 6 WORDS OF THE PLIST ARE AVAILABLE.       *@V6GMAL1 */
/*        WORD 5 POINTS TO A LIST OF DOUBLE WORD ADLENS        *@V6GMAL1 */
/*        (ADDRESS-LENGTH PAIRS) WHICH DESCRIBE THE            *@V6GMAL1 */
/*        ARGUMENTS TO THE ROUTINE (EPARGLST).  WORD 6         *@V6GMAL1 */
/*        (EPFUNRET) IS THE LOCATION FOR THE CALLED            *@V6GMAL1 */
/*        ROUTINE TO STORE THE ADDRESS OF AN EVALBLOK          *@V6GMAL1 */
/*        TO RETURN DATA TO THE CALLING PROGRAM.               *@V6GMAL1 */
/*                                                             *@V6GMAL1 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *@V6DEFT4 */
/*                                                              @V6MUBSA */
/* FLAG DEFINITIONS.  EXCEPT AS NOTED, ONLY THE FIRST FOUR      @V6MUBSA */
/* WORDS OF THE EXTENDED PLIST ARE AVAILABLE.                   @V6MUBSA */
/*                       EPLIST                                 @V6MUBSA */
/* FLAG         VALUE    AVAIL? MEANING                         @V6MUBSA */
/*                              6 WORD EXTENDED PLIST PRESENT   @V6MUBSA */
};

enum eplist_enum
{
   eplcmdfl = 0x0b,            /* EXTENDED PLIST AVAILABLE FLAG.    @V6DEFT4 */
   eplfncfl = 0x01,            /* EXTENDED PLIST AVAILABLE FLAG.    @V6DEFT4 */
   epfunsub = 0x05,            /* EXTERNAL FUNCTION PLIST AVAILABLE @V6GMAL1 */
   eplfprog = 0x00,            /* N PROGRAM                         @V6MUBSA */
   eplfcmnd = 0x01,            /* Y ADDRESS COMMAND                 @V6MUBSA */
   eplfsbcm = 0x02,            /* Y SUBCOM                          @V6MUBSA */
   eplfnnue = 0x03,            /* Y NO NUCEXT, EXTENDED             @V6MUBSA */
   eplfnnut = 0x04,            /* N NO NUCEXT, TOKENIZED            @V6MUBSA */
   eplfrxfn = 0x05,            /* Y REXX EXTERNAL FUNCTION,         @V6MUBSA */
   eplfimmd = 0x06,            /* Y IMMEDIATE COMMAND               @V6MUBSA */
   eplfsrch = 0x0b,            /* Y COMMAND SEARCH                  @V6MUBSA */
   eplfexec = 0x10,            /* N INVOKED BY BPX1EXC              @VR5FSI6 */
   eplfendc = 0xfe,            /* N END OF COMMAND                  @V6MUBSA */
   eplfaben = 0xff,            /* N ABEND OR NUCXDROP               @V6MUBSA */
};
#endif
