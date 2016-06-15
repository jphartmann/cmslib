#if !defined(_JPH_SVCSAVE_H)
   #define _JPH_SVCSAVE_H
/* FORMAT OF SYSTEM SAVE AREA                                            */
/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - SVCSAVE                                               @SI1469E */
/*                                                              @SI1469E */
/* Description - bilingual SVCSAVE macro                        @SI1469E */
/*                                                              @SI1469E */
/* DSECT - SSAVE                                                @SI1469E */
/*                                                              @SI1469E */
/* Function - map of the system save area. SSAVE                @SI1469E */
/*            is used by DMSITS to save the value of the SVC    @SI1469E */
/*            old PSW, the caller's registers, and other        @SI1469E */
/*            necessary control information required to         @SI1469E */
/*            process the SVC and return to the caller.         @SI1469E */
/*            Because SVC calls can be nested, several of       @SI1469E */
/*            these save areas can exist at one time. The       @SI1469E */
/*            system save area is dynamically allocated in      @SI1469E */
/*            protected free storage.                           @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
struct ssave
{
   unsigned char ovind;        /* OVERRIDE IND: 0,1,2,3   @VR200KB */
   unsigned char typflag;      /* SVC TYPE FLAG BYTE      @VR200KB */
   short code;                 /* SVC 203 CODE VALUE      @VR200KB */
   void * caller;              /* ADDRESS OF SVC CALLER   @VR200KB */
   unsigned char callee[8];    /* '                  NAME OF ROUTINE BEING CALLED */
   double oldpsw;              /* SVC OLDPSW OF CALLER    @VR200KB */
   void * nrmret;              /* ADDRESS FOR NORMAL RETUR@VR200KB */
   void * erret;               /* ADDRESS FOR ERROR RETURN@VR200KB */
   int egprs[0];               /* GENERAL REGS AT ENTRY TO SVC */
   int egpr0;                  /* R0                      @VR200KB */
   int egpr1;                  /* R1                      @VR200KB */
   int egpr2;                  /* R2                      @VR200KB */
   int egpr3;                  /* R3                      @VR200KB */
   int egpr4;                  /* R4                      @VR200KB */
   int egpr5;                  /* R5                      @VR200KB */
   int egpr6;                  /* R6                      @VR200KB */
   int egpr7;                  /* R7                      @VR200KB */
   int egpr8;                  /* R8                      @VR200KB */
   int egpr9;                  /* R9                      @VR200KB */
   int egpr10;                 /* R10                     @VR200KB */
   int egpr11;                 /* R11                     @VR200KB */
   int egpr12;                 /* R12                     @VR200KB */
   int egpr13;                 /* R13                     @VR200KB */
   int egpr14;                 /* R14                     @VR200KB */
   int egpr15;                 /* R15                     @VR200KB */
   double efprs[0];            /* FLOATING POINT REGS AT ENTRY */
   double efpr0;               /* FPR0                    @VR200KB */
   double efpr2;               /* FPR2                    @VR200KB */
   double efpr4;               /* FPR4                    @VR200KB */
   double efpr6;               /* FPR6                    @VR200KB */
   unsigned char chkwrd1;      /* CHECK WORD ONE */
   void * ssavenxt;            /* ADDRESS OF NEXT SSAVE AREA */
   void * ssaveprv;            /* ADDRESS OF PREVIOUS SSAVE AREA */
   void * usaveptr;            /* ADDRESS OF CORRESPONDING USER                           SAVE AREA */
   int ostemp;                 /* TEMP FOR OS SIMULATION ROUTINES */
/* 'DMSKEY' KEY STACK                                                    */
   unsigned char keyp;         /* NUMBER OF KEYS ON STACK */
   unsigned char keys[7];      /* KEY STACK               @VR200KB */
/* THE FOLLOWING FIELDS ARE FILLED IN ONLY BY DMSOVS, THE SVCTRACE       */
/* SUBROUTINE.                                                           */
   int xgpr0;                  /* EXTRA COPY OF EGPR0     @VR200KB */
   int xgpr1;                  /* EXTRA COPY OF EGPR1     @VR200KB */
   int xgpr15;                 /* EXTRA COPY OF EGPR15    @VR200KB */
   int xcount;                 /* EXTRA COPY OF SVCOUNT   @VR200KB */
   unsigned char chkwrd2;      /* SECOND CHECK WORD */
   int ssapsdpl;               /* CHAIN ANCHOR FOR PSDPL  @VR200KB */
/*                                      BLOCKS USED BY PARSER   @V6MUBSA */
   unsigned char ssacmdrs;     /* COMMAND RESOLUTION FLAG @VR200KB */
/*        EQU   X'08' - X'01'             RESERVED              @VA36272 */
   unsigned char ssasimfl;     /* CMS simulation flag     @VR200KB */
/*                                       DMSANCSV service at    @VA52070 */
/*                                       this SVC level         @VA52070 */
   unsigned char __fill1[2];   /* RESERVED                @VR200KB */
   int ssaprsub;               /* Private Subpool anchor  @VR200KB */
   int ssashsub;               /* Shared  Subpool anchor  @VR200KB */
/*                                                              @V6PXST4 */
   void * ssaplc;              /* PLIST COPY BLOCK        @VR200KB */
   int ssac6sa;                /* Save Control Reg. 6     @VR200KB */
   unsigned char ssaocode;     /* INTERRUPT CODE          @VR200KB */
   unsigned char __fill2[3];   /* RESERVED                @VR200KB */
   void * ssaprgbk;            /* Ptr to cmd set PRGBK    @VR200KB */
   int ssac14sa;               /* Save Control Reg. 14    @VR200KB */
   int ears[0];                /* Access Registers atentry@V6S80RS */
   int ear0;                   /* Access Register 0       @VR200KB */
   int ear1;                   /* Access Register 1       @VR200KB */
   int ear2;                   /* Access Register 2       @VR200KB */
   int ear3;                   /* Access Register 3       @VR200KB */
   int ear4;                   /* Access Register 4       @VR200KB */
   int ear5;                   /* Access Register 5       @VR200KB */
   int ear6;                   /* Access Register 6       @VR200KB */
   int ear7;                   /* Access Register 7       @VR200KB */
   int ear8;                   /* Access Register 8       @VR200KB */
   int ear9;                   /* Access Register 9       @VR200KB */
   int ear10;                  /* Access Register 10      @VR200KB */
   int ear11;                  /* Access Register 11      @VR200KB */
   int ear12;                  /* Access Register 12      @VR200KB */
   int ear13;                  /* Access Register 13      @VR200KB */
   int ear14;                  /* Access Register 14      @VR200KB */
   int ear15;                  /* Access Register 15      @VR200KB */
   void * sscelanc;            /* CEL Anchor              @VR200KB */
   void * sstempav;            /* CEL Anchor Vector saved @VA52070 */
   unsigned char ssacmdn[8];   /* '                  COMMAND NAME            @S9386EL */
   unsigned char ssaparm1[8];  /* '                  COMMAND PARMETER        @S9386EL */
/* FORMAT OF THE REGISTER SAVE AREA IN USERSAVE.  THIS IS       @V6PXST4 */
/* THE PART OF USERSAVE THAT THE USER CAN USE FOR REGISTERS.    @V6PXST4 */
/* THE USERSAVE MACRO DESCRIBES THE WHOLE AREA                  @V6PXST4 */
/* PASSED TO THE USER.                                          @V6PXST4 */
/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - SVCSAVE                                               @SI1469E */
/*                                                              @SI1469E */
/* Description - User Save Area                                 @SI1469E */
/*                                                              @SI1469E */
/* DSECT - USAVE                                                @SI1469E */
/*                                                              @SI1469E */
/* Function - USAVE is used by DMSITS to allocate and free      @SI1469E */
/*            save areas for other routines during SVC          @SI1469E */
/*            processing; it is pointed to by the USAVEPTR      @SI1469E */
/*            field in SSAVE.                                   @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
};

enum svcsave_enum
{
   tpfert = 0x80,              /* ERROR RETURN DESIRED */
   tpfns = 0x40,               /* NO SAVE AREA ALLOCATED */
   tpfr01 = 0x20,              /* RETURN CALLEE'S R0-R1 TO CALLER */
   tpfusr = 0x10,              /* 'USER' SVC CALL */
   tpfacb = 0x08,              /* OS VSAM SVC REQUEST */
   tpfsv3 = 0x02,              /* SVC 203 */
   tpfsvo = 0x01,              /* OS SIMULATION SVC */
#if 0
   ssaopswa = oldpsw+4,        /* ADDRESS IN SVC OLD PSW  @V6PXST4 */
#endif
   keymax = 7,                 /* MAXIMUM NUMBER OF KEYS IN STACK */
   ssacsrch = 0x80,            /* CMD SEARCH PERFORMED  @V6MUBSA */
   ssatrans = 0x40,            /* CMD NAME TRANSLATED   @V6MUBSA */
   ssasynon = 0x20,            /* CMD NAME SYNONYMED    @V6MUBSA */
   ssamdmap = 0x10,            /* CMD map repl ldr tbl  @VA36272 */
   ssasimcb = 0x80,            /* MVS/OS blocks defined   @V6PXKLR */
   ssasimpg = 0x40,            /* MVS/OS simulation prog. @V6PXKLR */
   ssasimrt = 0x20,            /* MVS/OS blocks returned. @V6PXKLR */
   ssasimx = 0x10,             /* MVS/OS XCTL in progress @V6PXKLR */
   ssasproc = 0x08,            /* process created         @VR2LML7 */
   ssasexec = 0x04,            /* exec svc level          @VR5FSL7 */
   ssacelsv = 0x01,            /* A call was made to the  @VA52070 */
};
#endif
