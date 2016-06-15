#if !defined(_JPH_NUCON_H)
   #define _JPH_NUCON_H

struct psw31                          /* 31-bit mode psw             */
{
   unsigned char mask;
   unsigned char key;
   unsigned char pgmmask;
   unsigned char reserved;
   unsigned int ia;
};

/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - NUCON                                                 @SI1469E */
/*                                                              @SI1469E */
/* Description - Nucleus Constant Area                          @SI1469E */
/*                                                              @SI1469E */
/* DSECT - NUCON                                                @SI1469E */
/*                                                              @SI1469E */
/* Function - Defines fields in CMS storage page zero           @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
struct nucon
{
   double nucon[0];
/*        Fixed Storage Locations                              *@V6S00VB */
/*        These fields (from X'0 to X'200') are reserved for   *@V6S00VB */
/*        exclusive use of the hardware as defined by the      *@V6S00VB */
/*        architecture. None of these fields can have initial  *@V6S00VB */
/*        values. All initialization of this area must be done *@V6S00VB */
/*        at run time.                                         *@V6S00VB */
   struct psw31 rstnpsw;             /* Restart new PSW                  @VR200KB */
   struct psw31 rstopsw;             /* Restart old PSW                  @VR200KB */
/*------> GPI <-----------------------------------------------* @V6S00VB */
/*                        ACMSCVT                             * @V6S00VB */
/*        This is the address of CMSCVT, the simulated OS CVT.* @V6S00VB */
/*                                                            * @V6S00VB */
   int acmscvt;                /* Address of simulated OS CVT      @VR200KB */
/*------> End GPI <-------------------------------------------* @V6S00VB */
   int asysref;                /* Address of nucleus address table @VR200KB */
   struct psw31 extopsw;             /* External old PSW                 @VR200KB */
   struct psw31 svcopsw;             /* Supervisor call old PSW          @VR200KB */
   struct psw31 pgmopsw;             /* Program old PSW                  @VR200KB */
   struct psw31 mckopsw;             /* Machine-check old PSW            @VR200KB */
   struct psw31 ioopsw;              /* Input/output old PSW             @VR200KB */
   struct psw31 csw;                 /* Channel Status Word              @VR200KB */
   int caw;                    /* Channel Address Word             @VR200KB */
   int nucrsv1;                /* Reserved for hardware use        @VR200KB */
   int timer;                  /* Interval timer                   @VR200KB */
   int nucrsv2;                /* Reserved for hardware use        @VR200KB */
   struct psw31 extnpsw;             /* External new PSW                 @VR200KB */
   struct psw31 svcnpsw;             /* Supervisor call new PSW          @VR200KB */
   struct psw31 pgmnpsw;             /* Program new PSW                  @VR200KB */
   struct psw31 mcknpsw;             /* Machine-check new PSW            @VR200KB */
   struct psw31 ionpsw;              /* Input/output new PSW             @VR200KB */
   int nuceparm;               /* External interrupt parameter     @VR200KB */
   unsigned char nucpuadr[2];  /* CPU address                      @VR200KB */
   unsigned char nucexcde[2];  /* XA or XC external interrupt code @VR200KB */
   unsigned char nucrsv3;      /* Reserved for hardware use        @VR200KB */
   unsigned char nucsvilc;     /* *6 - SVC ILC                     @VR200KB */
   short nucsvcn;              /* N*7 - SVC Interrupt code         @VR200KB */
   unsigned char __fill3;      /* Unused part of program interrupt @VR200KB */
   unsigned char nucxailc;     /* XA or XC mode ILC                @VR200KB */
   unsigned char nucpgcde[2];  /* XA or XC program interrupt code  @VR200KB */
   int __fill4;                /* Reserved for hardware use        @VR200KB */
   short monclass;             /* N*1 - Monitor call class number  @VR200KB */
   short percode;              /* N*2 - Program event recorder code@VR200KB */
   int peraddr;                /* Program event recorder address   @VR200KB */
   int moncode;                /* Monitor call code                @VR200KB */
   unsigned char nucexaid;     /* Exception Access ID              @VR280KB */
   unsigned char __fill5[3];   /* Reserved for hardware use        @VR280KB */
   int __fill6;                /* Reserved for hardware use        @VR280KB */
   int nuctxcp;                /* Translation exception data       @VR200KB */
   int __fill7[3];             /* Reserved for hardware use        @VR200KB */
   int nuciosid[0];            /* XA or XC mode SID causing I/O int@V6PXNTE */
   short __fill8;              /* Reserved for hardware use        @VR200KB */
   short nucioadr;             /* (EC-mode) I/O device causing int @VR200KB */
   int nucintp;                /* XA or XC mode Interrupt Parameter@VR200KB */
   short lowsave[0];           /* Save area for 1st 160 bytes stg. @V6PXGAM */
   unsigned char __fill9[24];  /* Reserved for hardware use        @VR200KB */
   unsigned char nuctimr[8];   /* CPU timer save area              @VR200KB */
   unsigned char nucclok[8];   /* Clock comparator save area       @VR200KB */
   unsigned char nucmcic[0];   /* Machine check interrupt code     @V6PXGAM */
   unsigned char nucmcic0;     /* MCIC byte 0                      @VR200KB */
   unsigned char nucmcic1;     /* MCIC byte 1                      @VR200KB */
   unsigned char nucmcic2;     /* MCIC byte 2                      @VR200KB */
   unsigned char nucmcic3;     /* MCIC byte 3                      @VR200KB */
   unsigned char nucmcic4;     /* MCIC byte 4                      @VR200KB */
   unsigned char nucmcic5;     /* MCIC byte 5                      @VR200KB */
   unsigned char nucmcic6;     /* MCIC byte 6                      @VR200KB */
   unsigned char nucmcic7;     /* MCIC byte 7                      @VR200KB */
   unsigned char __fill10[8];  /* Reserved for hardware use        @VR200KB */
   void * nucfsa;              /* Failing storage address          @VR200KB */
   int __fill11;               /* Reserved for hardware use        @VR200KB */
   int nucasit[2];             /* Contains the ASIT of the data    @VR200KB */
/*                             space on machine checks related  @VR1BR4Z */
/*                             to storage errors. Will be 0's   @VR1BR4Z */
/*                             if error is in base address space@VR1BR4Z */
   unsigned char __fill12[24]; /* Reserved for hardware use        @VR200KB */
   int xcarlog[16];            /* Access register logout area      @VR200KB */
   double fprlog[4];           /* Floating point register logout area */
   int gprlog[16];             /* General purpose register logout area */
   int ecrlog[16];             /* Extended control register logout area */
/*        End of Fixed Storage Locations                       *@V6S00VB */
/*        CMS System Fields                                    *@V6S00VB */
   unsigned char systemid[32]; /* '        System name and date             @VR200KB */
   unsigned char instalid[64]; /* '        Installation identification      @VR200KB */
   unsigned char sysname[8];   /* '         Name of IPLed saved system       @VR200KB */
   short ipladdr;              /* N*3 - Address of IPLed device    @VR200KB */
   short sysaddr;              /* N*4 - Address of system disk     @VR200KB */
   int device;                 /* Device causing last I/O interrupt@VR200KB */
   short hlpaddr;              /* N*5 - Address of HELP disk       @VR200KB */
   short nucyaddr;             /* N*6 - Address of Y-disk          @VR200KB */
   unsigned char feibm[12];    /* ' Component ID-IPCS referenced @V67CBE4 */
   unsigned char currdate[8];  /* '         Current date - mm/dd/yy          @VR200KB */
   unsigned char currtime[8];  /* '         Current time - hh:mm:ss          @VR200KB */
   int currvirt;               /* Current elapsed virtual time used@VR200KB */
   int currcput;               /* Current elapsed CPU time used    @VR200KB */
   int lastvirt;               /* Previous elapsed virtual time use@VR200KB */
   int lastcput;               /* Previous elapsed CPU time used   @VR200KB */
   unsigned char lastcmnd[8];  /* '         Last command issued */
   unsigned char prevcmnd[8];  /* '         Next to last command */
   unsigned char lastexec[8];  /* '         Last exec procedure */
   unsigned char prevexec[8];  /* '         Next to last exec */
   unsigned char lastlmod[8];  /* '         Last module LOADMODed into main storage */
   unsigned char lasttmod[8];  /* '         Last module LOADMODed into       @V6KRBMB */
/*                             the transient area.              @V6KRBMB */
   double datipcms;            /* Date (mm/dd/yy) at last IPL CMS */
   double clkvalmd;            /* Timer(STCK form) at midnight (0000 hours) */
   int nucenawa[2];            /* Work area for nucleus            @V6PXGAM */
/*                             ENABLE invocations               @V6PXGAM */
   void * nucldset;            /* Ptr to LOADSET of PRGBKs         @VR200KB */
   unsigned char nuccsltm;     /* Temp save area for translation   @VR200KB */
/*                             mode for CSL call in XC-mode mach@VR1BR4Z */
   unsigned char nucfstm;      /* Temp save area for translation   @VR200KB */
/*                             mode for FS calls in XC-mode mach@VR1BR4Z */
   unsigned char nucprtm;      /* Temp save area for translation   @VR200KB */
/*                             mode for PARSECMD call in XC-mode@VR1BR4Z */
   unsigned char nuc2ef;       /* Reserved for future IBM use      @VR200KB */
   void * nucafrsc;            /* Branch Addr for SUBPOOL CREATE   @VR5HN6P */
   void * nucafrsd;            /* Branch Addr for SUBPOOL DELETE   @VR5HN6P */
   void * nucafrsr;            /* Branch Addr for SUBPOOL RELEASE  @VR5HN6P */
   int nuc2fc;                 /* Reserved for future IBM use      @V6S00VB */
   void * nucidal;             /* IDAL pointer                     @V6PXUZ6 */
   int nucidall;               /* IDAL length                      @VR200KB */
   int nucfsr14;               /* R14 savearea in support of BALR  @VR1BR4Z */
/*                             entry processing for FS macros   @VR1BR4Z */
/*                             on XC-mode virtual machine.      @VR1BR4Z */
   int nucprr14;               /* R14 savearea in support of BALR  @VR1BR4Z */
/*                             entry processing for PARSECMD    @VR1BR4Z */
/*                             macro.                           @VA55734 */
   void * nucitexc;            /* EXTXCTL entry point in DMSITE    @VR1BRPQ */
   short nuc314;               /* Reserved for future IBM use      @VM45133 */
/* The following fields are used by the GLOBAL module to create @VM45133 */
/* a list for TXTLIB concatenation.                             @VM45133 */
/*                                                              @VM45133 */
   short nuctlanu;             /* TXTLIB alt. number GLOBALed      @VM45133 */
   int txlibsva;               /* Alt. libe save area TXTLIBS      @VM45133 */
   void * nuctlana;            /* TXTLIB alt. name list address    @VM45133 */
   void * nuctladi;            /* TXTLIB alt. directory list addr  @VM45133 */
   int nuctlasi;               /* TXTLIB alt. free storage size    @VM45133 */
   void * nucafroc;            /* Branch for Cond   CMSSTOR OBTAIN @VR5HN6P */
   void * nucafrou;            /* Branch for Uncond CMSSTOR OBTAIN @VR5HN6P */
   void * nucafrrc;            /* Branch for Cond  CMSSTOR RELEASE @VR5HN6P */
   void * nucafrru;            /* Branch for Uncond CMSSTOR RELEASE@VR5HN6P */
   int vmsizeg[2];             /* Reserved for CEC                 @SL432SG */
   void * nucamqvm;            /* MQSERIES POINTER FOR CEEPIPI     @VR74K0W */
   void * nucmcksa;            /* Anchor for DMSITM save area      @V6PXGAM */
   int txlibsv;                /* Libe save area TXTLIBs           @VM04102 */
   int maclbsv;                /* Libe save area MACLIBs           @VM04102 */
   int totlibs;                /* Total global chains (bytes)      @VM04102 */
   void * txtdirc;             /* Alternate name for NUCTLDIR      @V6MT01T */
   void * nuclicmd;            /* Anchor to LOAD/INCLUDE c-block   @V6PXKGK */
   void * nuctrbuf;            /* Pointer to trace buffer          @V6SR4VB */
   int nucitssa[16];           /* DMSITS general reg save area     @V6PXST4 */
/*        DEBUG dump parameters                                          */
   double dumplist[0];         /* DEBUG dump parameter list */
   void * grs015;              /* Address of GPR save area */
   void * loc0176;             /* Address of low core save area */
   void * firstdmp;            /* Address of first location to dump */
   void * lastdmp;             /* Address of last location to dump */
   void * frs06;               /* Address of FPR save area */
   void * dmptit;              /* Address of dump title line */
   void * nucsgiop;            /* Pointer to SGIOP build area      @V6S00VB */
   unsigned char dmptitle[132]; /* '       Dump title line */
   int glbltabl;               /* Reserved */
   unsigned char nuctrflg;     /* Trace buffering flag             @V6SR4VB */
   unsigned char nucflaga;     /* Miscellaneous flags              @V6S00FK */
/*                              extension of diags x'14',x'd8', @VR61NXY */
/*                              x'bc',x'264' & new diag x'270'  @VR61NXY */
   unsigned char svc$202[2];   /* Common SVC for reentrant code */
   void * err$202;             /* User error address */
   unsigned char br14$202[2];  /* Return to caller                 @V6GMAL1 */
   short currcent;             /* Century part of CURRDATE         @VR61NFK */
/*        BATCH monitor information                                      */
   unsigned char batflags;     /* BATCH flags */
   unsigned char batflag2;     /* More BATCH flags */
   unsigned char batflag3;     /* More BATCH flags                 @VA12384 */
   unsigned char batflag4;     /* BATCH virtual printer type       @VA15361 */
/* BATCH processor entry points                                          */
   void * abatproc;            /* Main entry */
   void * abatabnd;            /* User job ABEND entry */
   void * abatlimt;            /* User job limits table */
   void * auserrst;            /* Restart entry point              @V60C5BE */
   int nuserfwd;               /* Fullword for users               @VMI0066 */
   int nucrsv7;                /* Reserved for future use */
/*        DOS library pointers                                           */
   int doslbsv;                /* Libe save area DOSLIBS           @VM04102 */
   int nucrosad;               /* DMSROS workarea address          @V6RFGMY */
   short nucrosdw;             /* DMSROS workarea size in Dwords   @V6RFGMY */
   short nuc476;               /* Reserved for future IBM use      @V6S00VB */
   void * nucavw;              /* Addr of Alternate-VSAM workarea  @VA33162 */
   int nucmtav;                /* MT address vector                @VR2LML7 */
   int nucapld;                /* PLD anchor                       @VR2LML7 */
   unsigned char nucmtflg[0];  /* MT flags                         @VR2LML7 */
   unsigned char nucmtfl0;     /* 1st MT flag byte                 @VR2LML7 */
   unsigned char nucmtfl1;     /* second MT flag byte              @VR2LML7 */
   unsigned char nucbcpu[2];   /* base CPU address                 @VR2LML7 */
   int nucakga;                /* KGA anchor                       @VR2LML7 */
   int nucosmp;                /* MT OS Sim                        @VR2LML7 */
   void * nucospl;             /* OS simulation plist address      @VA30419 */
   void * nucospll;            /* OS simulation plist length       @VA30419 */
   void * nuccelgt;            /* Addr of Get CEL Anchor routine   @V6S00VB */
   void * nuccelst;            /* Addr of Set CEL Anchor routine   @V6S00VB */
   void * nucmacls;            /* Anchor for SET/QUERY MACLSUBS    @V6S00VB */
   void * nuccelsv;            /* Addr of SVC CEL Anchor routine   @VA52070 */
   int nucppid;                /* Current posix pid                @VR5FSL7 */
   int nuc4ac;                 /* Reserved for OPENVM support      @VR5FSL7 */
   int nuctcbo;                /* TCB OLD pointer                  @VR5FSL7 */
   int nuctcbn;                /* TCB NEW pointer                  @VR5FSL7 */
   int nuc4b8;                 /* Reserved for OPENVM support      @VR5FSL7 */
   int nuc4bc;                 /* Reserved for future IBM use      @V6S00VB */
   int nucrsk;                 /* Reusable Server Kernel           @VR74PVM */
   int nuc4c4;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc4c8;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc4cc;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc4d0;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc4d4;                 /* Reserved for future IBM use      @V6S00VB */
   unsigned char dosflags;     /* DOS simulation flags */
   unsigned char dosrc;        /* DOS return code to user */
   unsigned char nuc4da;       /* Reserved for future IBM use      @V6S00VB */
   unsigned char nuc4db;       /* Reserved for future IBM use      @V6S00VB */
   void * altasave;            /* Address of LTA save area */
   void * abgcom;              /* Address of partition comm. region */
   void * asyscom;             /* Address of system comm. region */
   void * adosdcss;            /* Address of DOS DCSS */
   int svc12sav;               /* Work area for SVC12 */
   void * dosfirst;            /* Address of first DOSCB in chain */
   short dosnum;               /* Number of DOSCBs in chain */
   short doskpart;             /* Number of K-bytes in DOS partition */
   void * appsave;             /* Address of prob. prog. save area */
   void * dostrans;            /* Address of DOS transient area */
   int aaltcvt;                /* Alternate addr field for CVT     @SG6417G */
   int dmntecb;                /* DMSTIO DEMOUNT timer ECB         @VA63002 */
   int nuc508;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc50c;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc510;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc514;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc518;                 /* Reserved for future IBM use      @V6S00VB */
   int nuc51c;                 /* Reserved for future IBM use      @V6S00VB */
   void * anucend;             /* End of DMSNUC                    @V6PXHSK */
   void * ausrarea;            /* Start of CMS user area           @V6PXNTE */
   struct ssave * currsave;            /* Address of current save area */
   short code203;              /* Code number of last SVC 203 */
   short nuc52e;               /* Reserved for future IBM use      @V6S00VB */
   void * nucfrwrk;            /* A(Storage Management Work Area)  @V6PXHSK */
/* V-constants for calling 'ADTLKP/ADTNXT/ADTLKW' via BALR calls:        */
   void * vcadtlkp;            /* BALR equivalent of 'ADTLKP' */
   void * vcadtnxt;            /* BALR equivalent of 'ADTNXT' */
   void * vcadtlkw;            /* BALR equivalent of 'ADTLKW' */
/*        Console I/O pointers                                           */
   void * currioop;            /* Address of current I/O buffer */
   void * pendread;            /* Address of pending read operation */
   void * pendwrit;            /* Address of pending write operation */
   void * fstfinrd;            /* Address of finished read buffer */
   void * lstfinrd;            /* Address of last finished read buffer */
   void * aintrtbl;            /* Address of user input translate table */
   void * aoutrtbl;            /* Address of user output translate table */
   short numfinrd;             /* Number of finished read buffers */
   short numpndwr;             /* Number of pending write operations */
/*        Loader information                                             */
   int vmsize;                 /* Virtual memory size              @VR200KB */
   int aldrtbls;               /* Address of the loader tables */
   int strtaddr;               /* Module starting address */
   int frstloc;                /* Module beginning address */
   int lastloc;                /* Module ending address */
   int loccnt;                 /* Loader location counter */
   int ldraddr;                /* Loader return address */
   int ldrrtcd;                /* Loader return code */
   double psw;                 /* User's starting PSW */
   int ldrflags;               /* Loader flags */
   int prhold;                 /* Pseudo register counter */
   short tbent;                /* Initialize table entries to zero */
   unsigned char unres;
   unsigned char modflgs;      /* MOD flags */
/*                               0=ON <Initial setting>         @VR3W4PQ */
/*                               1=OFF                          @VR3W4PQ */
   int get1;                   /* DMSLSY R1 save location */
   int dsym[2];                /* DMSLSY work space */
   int jsym;                   /* DMSLSY unique symbol base */
   unsigned char nxtsym;       /* 1st char of unique symbol */
   unsigned char __fill15[7];  /* Rest of unique symbol */
   int aliasent;               /* Alias entry point (dynamic load) */
   int dynaend;                /* Max. load loc. (dynamic load) */
/*        OS simulation pointers                                         */
   void * nuclcnta;            /* Location count alternative       @VR200KB */
   void * labfirst;            /* Address of first LABSECT */
   short labnum;               /* Number of LABSECTs */
   unsigned char nucsimfg;     /* OS simulation flags              @VA26912 */
   unsigned char nuc5bf;       /* Reserved for future IBM use      @V6S00VB */
   double fcbtab[0];           /* FCB chain anchor */
   void * fcbfirst;            /* Address of first FCB */
   short fcbnum;               /* Number of FCBs in chain */
   unsigned char __fill16;     /* Reserved for WPL */
   unsigned char ossflags;     /* OS simulation flags */
   void * atlbmodl;            /* Address of tape label processor */
   void * linklast;            /* Address of last OS linkage block */
   void * linkstrt;            /* Address of entry point of last module */
   void * taxeaddr;            /* Terminal attention exit element address */
   void * atsocppl;            /* Address of tmp plist for TSO programs */
   int dcbsav;                 /* DCB restoration address */
/*        Switches                                                       */
   unsigned char optflags;     /* Option flags */
   unsigned char misflags;     /* Miscellaneous flags */
   unsigned char msgflags;     /* Message flags */
   unsigned char dbgflags;     /* DEBUG flags */
   unsigned char misflag2;     /* More miscellaneous flags         @VA16886 */
/*                                            0=Non-OS type load@VA19633 */
/*                             This is used by DMSSLN to        @VA19633 */
/*                             indicate to DMSLDR that the      @VA19633 */
/*                             text load is from an OS          @VA19633 */
/*                             macro type load.                 @VA19633 */
   unsigned char nucflag3;     /* Even more miscellaneous flags    @VA24694 */
/*                             1= current LINKBLK on start      @V6PXKP2 */
/*                             of chain (use LINKSTART)         @V6PXKP2 */
/*                             0= current LINKBLK on end        @V6PXKP2 */
/*                               of LINKBLK chain (LINKEND)     @V6PXKP2 */
/*                             This is used by DMSSTA to        @V6PXKP2 */
/*                             indicate which chain pointer     @V6PXKP2 */
/*                             for the LINKBLK chain points to  @V6PXKP2 */
/*                             the most recently added LINKBLK  @V6PXKP2 */
   unsigned char execflag;     /* Exec flags */
   unsigned char protflag;     /* Storage protection flags */
   unsigned char tsoflags;     /* TSO flag byte */
   unsigned char subflag;      /* CMS subset flag-byte */
   unsigned char nucmflag;     /* Nucleus machine flag             @V6PXNTE */
   unsigned char nuctamde;     /* AMODE of last transient          @VR200KB */
   void * asysnams;            /* Addr of SYSNAMES entries */
   void * nuclanga;            /* LANGBLK anchor                   @V6MV5U9 */
   void * admslio;             /* Loader output routine */
   void * vcfstlkp;            /* BALR equivalent of 'FSTLKP' */
   void * vcfstlkw;            /* BALR equivalent of 'FSTLKW' */
   double sysref[0];           /* System routines and data areas */
   void * afvs;                /* File management work area */
   void * aopsect;             /* I/O operations plist area */
/*------> GPI <-----------------------------------------------* @V6S00VB */
/*                        ADEVTAB                             * @V6S00VB */
/*        This address is used to find CON1ECB for the        * @V6S00VB */
/*        WAITECB macro.  It points to device information     * @V6S00VB */
/*        for CMS.  CON1ECB is located at offset X'C' into    * @V6S00VB */
/*        this device information.  CON1ECB is the only field * @V6S00VB */
/*        of the device information that is supported as a    * @V6S00VB */
/*        programming interface.                              * @V6S00VB */
/*                                                            * @V6S00VB */
   void * adevtab;             /* CMS device table */
/*------> End GPI <-------------------------------------------* @V6S00VB */
   void * afstlkp;             /* Find an FST for a file */
   void * agetclk;             /* Get time from CP timer */
   void * afstlkw;             /* Find a Read/Write FST */
   void * apie;                /* Ptr to active SPIE/ESPIE exit    @V6PXJRU */
   void * aiadt;               /* Ptr to ADT chain */
   void * auser;               /* User defined storage area */
   void * ardtk;               /* Read a disk record */
   void * ascann;              /* Convert command line to plists   @VR5HN6P */
   void * asstat;              /* Ptr to the S-stat */
   void * atabend;
   void * asubsect;            /* Work area during SUBSET mode */
   void * admssvt;             /* Address of OS SVC simulation     @V6GP2MB */
   void * awrtk;               /* Write a disk record */
   void * astrinit;            /* Ptr to OS storage reset */
   void * iadt;                /* Ptr to ADT chain */
   void * nuc2sp;              /* Ptr to syncpoint manager block   @V6SJSVB */
   void * nuctapcb;            /* Ptr to tape control block        @V6S00VB */
   void * admspioc;            /* Put CCWs and data in user buffer */
   void * apgmsect;            /* Program interrupt work area */
   void * aiosect;             /* I/O interrupt work area */
   void * admpexec;            /* Dump from executing program      @VR5HN6P */
   void * adiosect;            /* DMSDIO work area */
   void * aabnsvc;             /* ABEND macro entry point          @V6S00VB */
   void * admserl;             /* Message work area */
   void * admscrd;             /* Make available read input line   @VR5HN6P */
   void * admsfreb;            /* DMSFREE/DMSFRET macro entry point */
   void * asvcsect;            /* Maps fields for SVC interrupts */
   void * aadtlkp;             /* Find an Active Disk Table */
   void * aupufd;              /* Close all files / update disk */
   void * astatext;
   void * aosret;              /* OS SVC routine return address    @V6MW4QE */
   void * acmsret;             /* CMS routine return address       @V6MW4QE */
   void * ascano;              /* Convert command line to plists   @VR5HN6P */
/*------> GPI <-----------------------------------------------* @V6S00VB */
/*                         AEXEC                              * @V6S00VB */
/*        This is the address of DMSEXI, the CMS module       * @V6S00VB */
/*        that is the interface to the REXX, EXEC2 and        * @V6S00VB */
/*        EXEC interpreters.  This address can be used by     * @V6S00VB */
/*        programs that need a minimum-overhead subcommand    * @V6S00VB */
/*        call mechanism.                                     * @V6S00VB */
/*                                                            * @V6S00VB */
   void * aexec;               /* Interface to EXEC handler        @V6SR6SV */
/*------> End GPI <-------------------------------------------* @V6S00VB */
   void * astart;              /* Execute a group of programs      @V6PXVQC */
   void * aadtlkw;             /* Find a Read/Write ADT */
   void * ausabrv;             /* User-defined abbreviations */
   void * aextsect;            /* External interrupt work area */
   void * ascbptr;             /* Ptr to 1st STAE control block */
   void * admsros;             /* Address of DMSROS                @V6KRBMB */
   void * nucastqy;            /* BALR entry for storage query     @VR5HN6P */
   void * aactlkp;             /* Creates, chains and manages AFTs */
   void * aactnxt;             /* Find next AFT */
   void * aactfree;            /* Get a new AFT */
   void * aactfret;            /* Return an AFT */
   void * aadtnxt;             /* Find next ADT */
   void * atrklkp;             /* Allocate an 800-byte disk blk    @VR5HN6P */
   void * atrklkpx;            /* Deallocate an 800-byte disk blk  @VR5HN6P */
   int nuc6cc;                 /* Reserved for future IBM use      @V6S00KB */
   int nuc6d0;                 /* Reserved for future IBM use      @V6S00KB */
   void * aerase;              /* Delete a file or group of files */
   void * atypsrch;            /* Check for common filetype */
   void * aupdisk;             /* Update file directory on disk */
   void * akillex;             /* Halt execution (in DMSABE) */
   void * atfinis;             /* Temporarily close output files   @VR5HN6P */
   void * ardbuf;              /* Read one or more records         @VR5HN6P */
   void * awrbuf;              /* Write one or more records        @VR5HN6P */
   void * afinis;              /* Close one or more files          @VR5HN6P */
   void * astate;              /* Look for a file on any disk */
   void * astatew;             /* Look for a file on R/W disks */
   void * apoint;              /* Set file read or write ptrs      @VR5HN6P */
   double __fill17[0];
   void * nucnaddr;            /* Nucleus Address Table            @V6RFGVB */
   int nucsvq13;               /* DMSSVQ R13 save area             @V6RFGVB */
/* CMS file system routines will not allow a read operation     @V6RFGVB */
/* into any address lower than NUCLOWAD (end of NUCON).         @V6RFGVB */
   void * nuclowad;            /* Address of end of NUCON          @V6RFGVB */
   void * atemplin;            /* Command line translation area    @VA16551 */
   void * nucamd80;            /* Hex constant of 80000000         @V6PXJRU */
   void * nucamd7f;            /* Hex constant of 7777777F         @V6PXJRU */
   void * nucsttmc;            /* 31-bit entry point for STATE     @V6PXJN5 */
   void * nucsimwk;            /* Ptr to OS/MVS simulation ctl blk @V6PXJRU */
   void * nucldend;            /* Maximum load address             @V6RXPMO */
   void * nucldbk;             /* Anchor for LOAD process LDPBK    @VA34581 */
   double nucsvqpw;            /* DMSSVQRX PSW save                @VR200KB */
   unsigned char nucldpf;      /* Contains text load process flags.@VA34581 */
/*                             Mapped by NLFLAG1 field in LDRST.@VA34581 */
   unsigned char nucmodf;      /* Contains flags associated with   @VA36272 */
/*                             loading/generating module files  @VA36272 */
/*                             been replaced by the load of a   @VA36272 */
/*                             module MAP                       @VA36272 */
   unsigned char nucldpg;      /* Contains flags associated with the text @VR100AD */
/*                      load process which is mapped by NLFLAG2 @VR100AD */
/*                      field in LDRST                          @VR100AD */
   unsigned char nuc733;       /* Reserved for future loader use   @V6S00VB */
   unsigned char nuchstr[2];   /* Loader history records           @S59529V */
   unsigned char nucrldr[2];   /* CONTAINS COUNT OF RLD RECORDS    @VA46411 */
   void * nucanc;              /* Anchor routine address           @VA39434 */
   void * nucanchr;            /* Address of anchor block          @VA39434 */
   double __fill18[0];
   unsigned char cmndline[255]; /* @V6MV7E1 */
   unsigned char __fill19;     /* @V6MV7E1 */
   double __fill20[0];
   unsigned char cmndexec[8];  /* @V6GMAL1 */
   unsigned char cmndlist[536];
   double __fill21[0];
   unsigned char constack[320];
/*        Save areas                                                     */
   int freesave[16];           /* @VR200KB */
   int balrsave[16];           /* @VR200KB */
   int waitsave[16];           /* @VR200KB */
/* VSAM and AMSERV control words:                                        */
   double __fill22[0];
/* Percent of available user storage to reserve                          */
/* for GETVIS/FREEVIS use when running VSAM:                             */
   short pctvsam;              /* 50 percent for CMS/VSAM use */
   unsigned char nucvsam2;     /* VSAM information flag            @V6RUOP2 */
   unsigned char nucgexit;     /* REXX Global Exit execution flags @VR1BV6P */
   void * nucvip;              /* Address of VSAM interface        @V6SJXGC */
/* Beginning and end of "IKQLAB" (when in storage):                      */
   void * adikqlab;            /* Set to A(IKQLAB) when in storage */
   void * ndikqlab;            /* Set to end of IKQLAB when in storage */
   void * aloktb;              /* LOCK/UNLOCK resource table       @V6BE0H5 */
   void * admsvib;             /* Addr of VSAM interface bootstrap */
   void * avipblk;             /* Address of DMSVIP 4K block       @V6SJXGC */
   unsigned char vsamflg1;     /* VSAM information flag */
   unsigned char nucc7d;       /* Reserved for future IBM use      @V6S00VB */
   unsigned char nucc7e;       /* Reserved for future IBM use      @V6S00VB */
   unsigned char nucc7f;       /* Reserved for future IBM use      @V6S00VB */
   void * avsamsys;            /* Addr of VSAM saved system */
   void * aamssys;             /* Addr of CMSAMS saved system */
   void * avsreoj;             /* DMSVSR entry point from VSAM $$BACLOS */
   void * avsrwork;            /* Addr of DMSVSR workarea */
   void * acblist;             /* ACB list bulit by OPEN/CLOSE */
   void * nucasyid;            /* A(DIAG X'00' response)           @V6PXHSK */
   void * aabwsect;            /* Pointer for IPCS                 @V67CBE4 */
   void * admszit;             /* Pointer for IPCS                 @V67CBE4 */
   double __fill23[0];
/*        Secondary address table                               @V62B0E5 */
   void * admstrka;            /* EDF disk block allocate          @VR5HN6P */
   void * admstrkm;            /* EDF disk block mark function     @VR5HN6P */
   void * admstrkd;            /* EDF disk block deallocate        @VR5HN6P */
   void * admsalu;             /* Addr of RELEASE subroutine       @VR5HN6P */
   void * asortfst;            /* Addr of SORT FST subroutine      @VR5HN6P */
   void * adevsup;             /* CP to OS dev type conv table     @V6M00MJ */
   void * adevind;             /* Dev const table index            @V6M00MJ */
   void * atblind;             /* Dev constants table              @V6M00MJ */
   void * ablkind;             /* Dev blksize index                @V6M00MJ */
   void * alabelrd;            /* Addr of label read routine       @V62B1E5 */
   void * alabelwr;            /* Addr of label write routine      @V62B1E5 */
   void * admsladn;            /* LOCATE/ADD requested ADT         @V62B3H2 */
   void * admsblkr;            /* EDF block read routine           @VR5HN6P */
   void * admsblkw;            /* EDF block write routine          @VR5HN6P */
   void * aabbrev;             /* Abbrev resolver in DMSINA        @V62A7E5 */
   void * adevsup2;            /* Device support table for FBA     @V6M00MJ */
   void * aestate;             /* Extended plist state             @V62B0G9 */
   void * aestatew;            /* Extended plist state for R/W     @V62B0G9 */
   void * aepoint;             /* Extended plist point             @VR5HN6P */
   void * atrunc;              /* File truncate function           @VR5HN6P */
   int abamsys;                /* Pointer to CMSBAM DCSS           @V62A1B4 */
   void * nucscblk;            /* SCBLOCK chain anchor             @V6BD7G9 */
   unsigned char bamflags;     /* CMSBAM shared segment flags      @V62A1B4 */
   unsigned char nucosflg;     /* OS loader support flag           @V6BE17A */
   unsigned char nuccfa;       /* Reserved for future IBM use      @V6S00VB */
   unsigned char nuccfb;       /* Reserved for future IBM use      @V6S00VB */
   void * ahashmnt;            /* Addr of hash table maint routine @V6RFGVB */
   void * nuclriwa;            /* DMSLRI Work Area                 @V6RUOUD */
   void * asstatx;             /* Addr of shared copy of SSTAT     @V62B0E5 */
   void * asstatz;             /* Addr of dummy 2nd SSTAT hblk     @V62B0E5 */
   void * aystatx;             /* Addr of shared copy of YSTAT     @V62B0E5 */
   void * aystatz;             /* Addr of dummy 2nd YSTAT hblk     @V62B0E5 */
   void * admsiow;             /* CPU in wait state until finish   @V62B0E5 */
   void * adbgsect;            /* DEBUG workarea                   @V62B0E5 */
   void * admsabw;             /* ABEND work area                  @V62B0E5 */
   void * admserr;             /* Old name for NUCERO              @VR200KB */
   void * admscwt;             /* Calling program wait for I/O     @V62B0E5 */
   void * admscwr;             /* Write output to console          @VR5HN6P */
   void * admsiowr;            /* Wait until I/O complete          @V62B0E5 */
   void * admsiti;             /* Handle all I/O interruptions     @V62B0E5 */
   void * admsabn;             /* Old name for NUCABEND            @VR200KB */
   void * aabngo;              /* Special ABEND entry              @V6S00VB */
   void * aladad;              /* Auxiliary directory processing   @V62B0E5 */
   void * acitdb;              /* Clear read and write stacks      @V62B0E5 */
   void * admsitsr;            /* SVC handler ABEND recovery       @V62B0E5 */
   void * admsfres;            /* NOP entry point                  @V62B0E5 */
   void * astgsb;              /* Call STRINIT from nucleus        @V62B0E5 */
   void * aintab;              /* ABEND entry point for DMSINT     @V62B0E5 */
   void * admscat;             /* Stack a line of input            @V62B0E5 */
   void * admscpf;             /* Pass virtual console function    @SM658PR */
   void * aexcab;              /* Address of exec ABEND rtn        @V62B0E5 */
   void * nucfstln;            /* First line in program stack      @V6BD7G9 */
   void * nuclstln;            /* Last line in program stack       @V6BD7G9 */
   void * nucnlstk;            /* Number of lines in prog. stack   @V6BD7G9 */
   void * nucnbstk;            /* Number of program stack          @V6BD7G9 */
   unsigned char nuctiein[8];  /* Listing tiein field              @V6BE17A */
   void * nucafchs;            /* Addr of OS fetch work area       @V6BE17A */
   int nuccblks;               /* Ptr to mods loaded by DMSLOS     @V6BE17A */
   void * nucsfscb;            /* Ptr to SFS control block         @V6RFGVB */
   void * nucsdsgb;            /* Ptr to SDS global ctl block      @V6RFIVB */
   int nucd88;                 /* Reserved for future IBM use      @VR2LMLP */
   void * nucaexr;             /* Pointer to DMSEXR for EXT/REP    @V6RJHHA */
   void * nucopnmc;            /* Ptr to FSOPEN routine            @VR5HN6P */
   void * nucaparl;            /* Ptr to parser storage release    @VR5HN6P */
   void * nuccdcba;            /* Ptr to Communication Directory   @V6RJKN7 */
/*                             Control Block                    @V6RJKN7 */
   void * nuccwr13;            /* DMSCWR R13 save                  @V6RYNUD */
   void * nucfnsmc;            /* Ptr to FSCLOSE routine           @VR5HN6P */
   int nucaxloc;               /* Address of Xedit Locked chain    @VA48638 */
   void * nuccslvt;            /* Ptr to error routine initially   @VR2MJP2 */
/*                             Ptr to CSL 1st level vect table  @VR2MJP2 */
/*                             after CSL initialization         @VR2MJP2 */
/*                             This field may be modified       @VR2MJP2 */
/*                             as new 1st level tables are      @VR2MJP2 */
/*                             needed (i.e., for TRACE, etc.)   @VR2MJP2 */
   void * nuccslv2;            /* Ptr to CSL direct call routing   @VR5HNP2 */
/*                             routine. routine routes direct   @VR200P2 */
/*                             CSL routine calls to proper      @VR200P2 */
/*                             storage location.                @VR200P2 */
   int nuccslfe;               /* 2 fullword bitmap for track-     @VR5FSP2 */
   int __fill26;               /* ing front-ended CSL routines     @VR5FSP2 */
   int nucdb8;                 /* Reserved for future IBM use      @V6S00VB */
   int nucdbc;                 /* Reserved for future IBM use      @V6S00VB */
   void * nucarelm;            /* Pointer to CMSREL message        @V6S00SK */
   void * nucldmod;            /* Branch entry to LOADMOD          @VR5HN6P */
   int nuclodsv;               /* Save area for LOADLIB totals     @V6BE17A */
   void * nucwrkbk;            /* Address of WRKBK chain           @V6MZ8L1 */
   void * nuccslbk;            /* Address of CSL Block             @V6RJIHA */
   void * nucexrep;            /* Address for Extract/Replace      @V6RJHHA */
   void * nucdcscb;            /* Pointer to the first DCSCB       @V6PXOKG */
/*                             in the chain                     @V6PXOKG */
   void * nucsvqof;            /* Address of PL/AS overflow rtn    @VR5HN6P */
   void * nuccwa;              /* System Stack Storage Control Blk @V6S70KL */
   void * nucphi;              /* Start of high part of nucleus    @VR1006P */
   void * nucchi;              /* End of high part of nucleus      @VR1006P */
   void * nucapio;             /* Printer I/O routine              @V6BD7H2 */
   void * atcbptr;             /* DOS TCB address                  @VA15262 */
   void * agamseg;             /* GAM/SP anchor blk address        @VA15262 */
   void * nucalpha;            /* Start of CMS shared nucleus      @V6DEFH2 */
   void * nucsigma;            /* Start of S- and Y-stat storage   @V6DEFH2 */
   void * nucomega;            /* End of CMS shared nucleus        @V6DEFH2 */
   void * nucnltrt;            /* Address of national lang TRTBL   @V6MV5U9 */
   double nucplist[0];         /* Untokenized plist                @V6DEFH2 */
   void * nucplcmd;            /* Address of command token         @V6DEFH2 */
   void * nucplbeg;            /* Addr of start of arg string      @V6DEFH2 */
   void * nucplend;            /* Addr of end of arg string        @V6DEFH2 */
   void * nucplfid;            /* Addr of fn ft fm identifier      @V6DEFH2 */
   void * nuchshtb;            /* Hash table management            @V6MW4P4 */
   int nucpathf;               /* Anchor for CONSOLE path table    @V6KX2Z6 */
   int nucdevf;                /* .... and CONSOLE device table    @V6KX2Z6 */
   int nucsmblk;               /* Windowing master control block   @V6MV7TB */
   void * nucszabv;            /* Size of area above nuc. freted   @V6DEFH2 */
   void * nucadfnc;            /* Addr of nucleus function table   @V6DEFH2 */
   int nucldr0s;               /* Save R0 in DMSLDR (new plist)    @V6DEFH2 */
   void * nucupper;            /* Uppercase translate table        @VR5HNRY */
   void * nucert;              /* DMSERT work area address         @V6GP2T4 */
   void * nucxcblk;            /* Anchor for nuc extension chain   @V6DF9DA */
/*------> GPI <-----------------------------------------------* @V6S00VB */
/*                        NUCXFRES                            * @V6S00VB */
/*        This is the cumulative amount of TYPE=NUCLEUS free  * @V6S00VB */
/*        storage which will be retained by nucleus extensions* @V6S00VB */
/*        through an ABEND.  This does not include storage    * @V6S00VB */
/*        accounted for in SCBLOCKS in the NUCXCBLK chain.    * @V6S00VB */
/*        This field is used by DMSABE when performing abend  * @V6S00VB */
/*        recovery.                                           * @V6S00VB */
/*                                                            * @V6S00VB */
   int nucxfres;               /* @V6DF9DA */
/*------> End GPI <-------------------------------------------* @V6S00VB */
   void * nucxcbee;            /* SCBLOCK free list anchor         @V6DF9DA */
   int nucuser1;               /* FW for exclusive use of users    @V6DF9DA */
   int nucuser2;               /* FW for exclusive use of users    @V6DF9DA */
   int nucuser3;               /* FW for exclusive use of users    @V6DF9DA */
   int nucuser4;               /* FW for exclusive use of users    @V6DF9DA */
/*------> GPI <-----------------------------------------------* @V6S00VB */
/*                        USERLVL                             * @V6S00VB */
/*        USERLVL is reserved for use by the user.  It's      * @V6S00VB */
/*        contents are returned in R0 after QUERY CMSLEVEL    * @V6S00VB */
/*        is issued.                                          * @V6S00VB */
/*                                                            * @V6S00VB */
   int userlvl;                /* @VR200KB */
/*------> End GPI <-------------------------------------------* @V6S00VB */
/*        The following 2 full words are initialized in DMSINQ. @VR100KB */
/*                                                              @V6DF9T4 */
/*        The following 4 bytes are reserved for IBM use only.  @V6DF9T4 */
/*        They contain information relating to the level        @V6DF9T4 */
/*        of CMS being used.  They are returned in R1 after     @V6DF9T4 */
/*        QUERY CMSLEVEL is issued.                             @V6DF9T4 */
/*                                                              @V6DF9T4 */
   unsigned char cmslvl;       /* Reserved for future use          @VR200KB */
   unsigned char cmsprog;      /* Unique program product id        @VR200KB */
/*                             defined in CMSLEVEL macro        @V6DF9T4 */
   short cmsserv;              /* CMS service level in binary      @VR200KB */
/*                                                              @V6DF9T4 */
/*        ACMSLVLM is reserved for IBM use only.  It contains   @V6DF9T4 */
/*        a pointer to the message QUERY CMSLEVEL issues.       @V6DF9T4 */
/*                                                              @V6DF9T4 */
   void * acmslvlm;            /* @V6DF9T4 */
   void * aiucvtab;            /* Addr. of IUCV table              @V6GM0T6 */
   int nucxend;                /* Counter of End-of-command        @V6GM4T6 */
/*                             nucleus extentions               @V6GM4T6 */
   int abnxtptr;               /* ABEND exit anchor                @V6GM28E */
   void * admsabxr;            /* ABNEXIT reset entry              @VR5HN6P */
   void * aimmtabl;            /* Addr of immediate command        @V6GM3H9 */
/*                             command work area                @V6GM3H9 */
   unsigned char imescape;             /* Immediate command escape char    @V6GM3H9 */
   unsigned char imchar;               /* Immediate command escape char    @V6GM3H9 */
/*                             information                      @V6GM3H9 */
/*                             active                           @V6GM3H9 */
   unsigned char nucexsmd;     /* Exec segment access mode         @V6MZ4U9 */
   unsigned char nucqeflc;     /* CMSLEVEL returned by DMSQEFL     @SF805SG */
   void * svcwkadr;            /* Addr of DMSDOS SVC workarea      @V6GM8NB */
   void * admscsf;             /* Addr of command search function  @SM048PR */
   int nucexis;                /* Pointer to EXISBLK of most       @S5646EL */
/*                             recently referenced EXEC In      @S5646EL */
/*                             Storage-- 0 if this exec has     @S5646EL */
/*                             been dropped from storage.       @S5646EL */
/*   Fields for preserving the relocation information           @V6KRAMB */
/*   from the LOAD/GENMOD process                               @V6KRAMB */
/*                                                              @V6KRAMB */
   void * rlddata;             /* Address of the buffer that       @V6KRAMB */
/*                             is used to save RLD              @V6KRAMB */
/*                             information from the             @V6KRAMB */
/*                             LOAD/GENMOD process.             @V6KRAMB */
/*                                                              @V6KRAMB */
/*                             in doublewords.                  @V6KRAMB */
/*                                                              @V6KRAMB */
   void * rldpoint;            /* Pointer to current item in       @V6KRAMB */
/*                             the RLDDATA buffer               @V6KRAMB */
   void * admsexq;             /* BALR entry point for DMSEXQ      @VR5HN6P */
   int miscecb;                /* MISC. use ECB                    @V6KRAMB */
   double nuctodca[2];         /* TOD clock accounting area        @VR200KB */
   unsigned char nuclangc[5];  /* '         Current language                 @V6MV5U9 */
   unsigned char nucnllid;     /* National language level id       @V6MV5U9 */
   unsigned char nucdbcs;      /* SET DBCS flag                    @VR2A62I */
   unsigned char nuceaf;       /* Reserved for future IBM use      @V6S00VB */
   void * nuclangd;            /* Default language LANGBLK ptr     @V6MV5U9 */
   void * nucexsad;            /* Address of exec segment          @V6MZ4U9 */
/*------------------------------------------------------------* @V6MT01T */
/* Fields used by the GLOBAL command to maintain library      * @V6MT01T */
/* lists for MACLIBs, LOADLIBs, DOSLIBs, and TXTLIBs.         * @V6MT01T */
/*------------------------------------------------------------* @V6MT01T */
/* The following fields point to the name lists used by GLOBAL. @V6MT01T */
   void * nucmlnam;            /* MACLIB  name list address        @V6MT01T */
   void * nucllnam;            /* LOADLIB name list address        @V6MT01T */
   void * nucdlnam;            /* DOSLIB  name list address        @V6MT01T */
   void * nuctlnam;            /* TXTLIB  name list address        @V6MT01T */
/* The following fields point to the lists of directory         @V6MT01T */
/*  pointers used by GLOBAL.                                    @V6MT01T */
   void * nucmldir;            /* MACLIB  directory list address   @V6MT01T */
   void * nuclldir;            /* LOADLIB directory list address   @V6MT01T */
   void * nucdldir;            /* DOSLIB  directory list address   @V6MT01T */
   int nuced4;                 /* Reserved for future IBM use      @V6S00VB */
/* The following fields contain the size (in doublewords) of the@V6MT01T */
/*  free areas obtained by GLOBAL to keep the name lists and the@V6MT01T */
/*  directory pointer lists.                                    @V6MT01T */
   int nucmlsiz;               /* MACLIB  free storage size        @V6MT01T */
   int nucllsiz;               /* LOADLIB free storage size        @V6MT01T */
   int nucdlsiz;               /* DOSLIB  free storage size        @V6MT01T */
   int nuctlsiz;               /* TXTLIB  free storage size        @V6MT01T */
/* The following fields contain the number of GLOBALed libraries@V6MT01T */
   short nucmlnum;             /* Number of GLOBALed MACLIBS       @V6MT01T */
   short nucllnum;             /* Number of GLOBALed LOADLIBS      @V6MT01T */
   short nucdlnum;             /* Number of GLOBALed DOSLIBS       @V6MT01T */
   short nuctlnum;             /* Number of GLOBALed TXTLIBS       @V6MT01T */
/*                                                              @V6MSCXC */
/*   Fields for preserving the history information              @V6MSCXC */
/*   from the LOAD/INCLUDE/GENMOD process                       @V6MSCXC */
/*                                                              @V6MSCXC */
   void * nuchstda;            /* Address of the buffer that       @V6MSCXC */
/*                             is used to save history          @V6MSCXC */
/*                             information from the             @V6MSCXC */
/*                             LOAD/INCLUDE/GENMOD process.     @V6MSCXC */
/*                                                              @V6MSCXC */
/*                             (NUCHSTDA) in doublewords.       @V6MSCXC */
/*                                                              @V6MSCXC */
   void * nuchstpo;            /* Pointer to the next available    @V6MSCXC */
/*                             space in the history buffer      @V6MSCXC */
/*                             (NUCHSTDA).                      @V6MSCXC */
/*                                                              @V6MSCXC */
   void * nuclanss;            /* Current language DCSS address    @V6MV5U9 */
/*                                                              @V6MV7TB */
/* The following field is used for internal queue management.   @V6MV7TB */
/*                                                              @V6MV7TB */
   void * nucscrqa;            /* Anchor for Queue Manager         @V6MV7E1 */
/*                                                              @V6MV7TB */
/* The following fields are used for internal storage pools.    @V6MV7TB */
/*                                                              @V6MV7TB */
   void * nucsmsta;            /* Queue Mgr message blocks         @V6MV7E1 */
   void * nucsmstb;            /* Queue Mgr control blocks         @V6MV7E1 */
   void * nucsmstc;            /* Window/Vscreen control blocks    @V6MV7E1 */
/*                                                              @V6MV7TB */
/* V-cons for fullscreen CMS attn-hit & write-pending routines. @V6MV7TB */
/*                                                              @V6MV7TB */
   void * nucwexwr;            /* DMSWEXWR - fullscreen refresh    @V6MV7TB */
   void * nucwexrd;            /* DMSWEXRD - fullscreen attn       @V6MV7TB */
   void * nucapar;             /* Address of command parser        @VR5HN6P */
   void * nucciobf;            /* Addr of I/O buffer for DMSCIO    @V6MW4QE */
   void * nucasttv;            /* Addr of VALIDATE routine         @V6MW4QE */
   void * nucaxadt;            /* Addr of ADT index                @V6MW4QE */
   void * nucaladr;            /* Addr of ADT release routine      @V6MW4QE */
   int nucgethi;               /* Highest value of MAINHIGH        @V6MW4QE */
   int nucf2c;                 /* Reserved for future IBM use      @V6S00VB */
   void * nuccsffn;            /* High-order byte indicator        @VA23100 */
/*                             and FILENAME address             @VA23100 */
   void * nucadie;             /* CMS termination address          @V6RRHFV */
   unsigned char nucinsts[8];  /* '  Installation segment name        @V6MZ4U9 */
/*                                                              @V6MV7E1 */
/* Amount of system storage, in doublewords, allocated for the  @V6MV7E1 */
/* Window Manager storage pool and pending messages enqueued.   @V6MV7E1 */
/* These values are used to reconcile system storage during     @V6MV7E1 */
/* abend recovery.                                              @V6MV7E1 */
/*                                                              @V6MV7E1 */
   int nucsmpst;               /* Storage pool storage allocated   @V6MV7E1 */
   int nucsmqst;               /* Pending messages enqueued        @V6MV7E1 */
   void * nucwvtix;            /* Addr. of Vscreen WAIT routine    @VA33157 */
   void * nucwvxpi;            /* WRITE Vscreen pgm. interface     @VA33157 */
   void * nucwmx;              /* XEDIT interface for windowing    @VA33157 */
   void * nucdsxr;             /* Data Space Exception Exit Addr   @V6S80VB */
   void * nucmcxr;             /* Machine Check Exit Addr          @V6S80VB */
   void * nucspcbk;            /* Anchor for data space structures @VR1BR4Z */
   void * nucmgm;              /* Address of CMS message module    @VR5HN6P */
   unsigned char nucfmpfn[8];  /* '         Fullmap file name                @VR200KB */
   void * nucdiab;             /* REXX I/O support anchor          @VR3A4LP */
   int nucrxsok;               /* RXSOCKET debug ptr               @SI020KC */
   int nucf74;                 /* Reserved for future IBM use      @V6S00VB */
   int nucf78;                 /* Reserved for future IBM use      @V6S00VB */
   int nucf7c;                 /* Reserved for future IBM use      @V6S00VB */
   void * nucmcach;            /* Pointer for message cache        @VR1006P */
   int timrsave;               /* Timer Save Area                  @VR200KB */
   void * nucvmgui;            /* VM GUI Global Work Area Address  @VR55V5H */
   void * nucrxwk;             /* REXX Global Work Area Address    @VR3A47Z */
   int nuccsls0;               /* Reg save area for CSL Direct call@VR200P2 */
   int nuccsls1;               /* Reg save area for CSL Direct call@VR200P2 */
   int nuccsls2;               /* Reg save area for CSL Direct call@VR200P2 */
   int nuccsls3;               /* Reg save area for CSL Direct call@VR200P2 */
   int nuccsls4;               /* Reg save area for CSL Direct call@VR200P2 */
   int nuccsltb;               /* Traceback address for Direct call@VR200P2 */
   unsigned char nucftype[8];  /* '         Save area for FILETYPE           @Vr200AD */
   unsigned char nucmtseg[8];  /* '  Name of VMMTLIB segment          @VR2LMS1 */
   int nucfb8;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfbc;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfc0;                 /* Reserved for future IBM use      @V6S00VB */
   void * ostxtbuf;            /* The size of the buffer in storage@VR2MRKB */
/*                              to use before OSLOADing TEXT    @VR2MRKB */
/*                              Initialized to X'50000'         @VR2MRKB */
   void * nucwdba;             /* CMS defaul debugger              @VR5FSHI */
   int nucfcc;                 /* BFS FSSM Anchor                  @SF193P4 */
   int nucfd0;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfd4;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfd8;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfdc;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfe0;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfe4;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfe8;                 /* Reserved for future IBM use      @V6S00VB */
   int nucfec;                 /* Reserved for future IBM use      @V6S00VB */
   int nucff0;                 /* Reserved for future IBM use      @V6S00VB */
   int nucff4;                 /* Reserved for future IBM use      @V6S00VB */
   int nucff8;                 /* Reserved for future IBM use      @V6S00VB */
   int nucffc;                 /* Reserved for future IBM use      @V6S00VB */
   double __fill27[0];         /* Align end of NUCON               @V6MV7E1 */
};

enum nucon_enum
{
   nucdmstr = 0x80,            /* @V6SR4VB */
   nuctrf40 = 0x40,            /* Reserved for trace support       @V6SR4VB */
   nuctrf20 = 0x20,            /* Reserved for trace support       @V6SR4VB */
   nuctrf10 = 0x10,            /* Reserved for trace support       @V6SR4VB */
   nuctrf08 = 0x08,            /* Reserved for trace support       @V6SR4VB */
   nuctrf04 = 0x04,            /* Reserved for trace support       @V6SR4VB */
   nuctrf02 = 0x02,            /* Reserved for trace support       @V6SR4VB */
   nuctrf01 = 0x01,            /* Reserved for trace support       @V6SR4VB */
   nucoldcm = 0x80,            /* Two word command processing flag @V6RDYVB */
   nucready = 0x40,            /* Long/Short RC on READY Message   @SA787XW */
   nucy2000 = 0x20,            /* CP has Year 2000 support, thatis @VR61NXY */
   usrversn = 0x10,            /* The VERSION at X'200'not deflt   @SK869SG */
   nuc44508 = 0x08,            /* Reserved for future IBM use      @V6RDYVB */
   nuc44504 = 0x04,            /* Reserved for future IBM use      @V6RDYVB */
   nuc44502 = 0x02,            /* Reserved for future IBM use      @V6RDYVB */
   nuczarch = 0x01,            /* Reserved for CEC                 @SL432SG */
   batrun = 0x80,              /* BATCH monitor running */
   batload = 0x40,             /* Loading BATCH processor */
   batnoex = 0x20,             /* Suppress user job execution */
   batrerr = 0x10,             /* BATCH reader error */
   batcpex = 0x08,             /* CP command executing */
   batusex = 0x04,             /* User job executing */
   batmove = 0x02,             /* MOVEFILE executing from terminal */
   batterm = 0x01,             /* User job being flushed */
   batxlim = 0x80,             /* User job limit exceeded */
   batxcpu = 0x40,             /* CPU time exceeded */
   batxprt = 0x20,             /* No. printed lines exceeded */
   batxpun = 0x10,             /* No. punched cards exceeded */
   batdcms = 0x08,             /* Disabled CMS command called */
   batiplss = 0x04,            /* BATCH IPLing saved system */
   batstop = 0x02,             /* BATCH stopping after current job */
   batsysab = 0x01,            /* System ABEND in progress         @VA05162 */
   batcpfng = 0x80,            /* CPF link failure                 @VA12384 */
   batprt = 0x40,              /* LOADVFCB was issued              @VA15361 */
   batcpch = 0x20,             /* BATCH CP check flag              @VA20066 */
   batabnab = 0x10,            /* System ABEND is ABENDing         @VA51673 */
   nuc45208 = 0x08,            /* Reserved for future IBM use      @V6S00VB */
   nuc45204 = 0x04,            /* Reserved for future IBM use      @V6S00VB */
   nuc45202 = 0x02,            /* Reserved for future IBM use      @V6S00VB */
   nuc45201 = 0x01,            /* Reserved for future IBM use      @V6S00VB */
   nuc45380 = 0x80,            /* Reserved for future IBM use      @V6S00VB */
   nuc45340 = 0x40,            /* Reserved for future IBM use      @V6S00VB */
   nuc45320 = 0x20,            /* Reserved for future IBM use      @V6S00VB */
   nuc45310 = 0x10,            /* Reserved for future IBM use      @V6S00VB */
   nuc45308 = 0x08,            /* Reserved for future IBM use      @V6S00VB */
   nuc45304 = 0x04,            /* Reserved for future IBM use      @V6S00VB */
   nuc45302 = 0x02,            /* Reserved for future IBM use      @V6S00VB */
   nuc45301 = 0x01,            /* Reserved for future IBM use      @V6S00VB */
   nucmtmp = 0x80,             /* MP enabled                       @VR2LML7 */
   nucmtnb = 0x40,             /* nonbase processor                @VR2LML7 */
   nucmta24 = 0x20,            /* caller amode 24                  @VR2LML7 */
   nucmtrte = 0x10,            /* run thread exists                @VR2LML7 */
   nucmtisg = 0x08,            /* console input signal wanted      @VR2LML7 */
   nucmtds = 0x04,             /* drop special segment             @VR2LML7 */
   nucmtdsp = 0x02,            /* have started dispatching         @VR2LMFJ */
   nucmten = 0x01,             /* mt call issued                   @VR2LML7 */
   nucmtcwt = 0x80,            /* in command wait                  @VR2LML7 */
   nucmtsfs = 0x40,            /* monitor sfs async io             @VR3W9L7 */
   nucmtexc = 0x20,            /* exec() is in progress somewhere  @VR5FSP2 */
   nucmt1sg = 0x10,            /* con1ecb signal wanted            @VR5FSP2 */
   nucmtroo = 0x08,            /* root processes exist             @VR55VZ6 */
   nucmtfrk = 0x04,            /* fork is allowed */
   dosmode = 0x80,             /* DOS environment flag */
   dossvc = 0x40,              /* DOS SVC simulation flag */
   dosvsam = 0x20,             /* DOS VSAM running flag */
   doscomp = 0x10,             /* DOS complier running flag */
   dospio = 0x08,              /* DOS printer indicator */
   vsminstl = 0x04,            /* VSAM install flag to relocate DCSS table */
   nucosdlb = 0x02,            /* OS DLBL was issued               @VA27489 */
   doseoj = 0x01,              /* Indicates DMSDOS EOJ processing  @VA45647 */
   nomapflg = 0x80,            /* NOMAP flag */
   clearop = 0x40,             /* CLEAR option flag */
   modgndos = 0x20,            /* Module generated with DOS option */
   modgnall = 0x10,            /* Module generated with ALL option */
   sysload = 0x08,             /* Allow load >FREELOWE or <TRANS   @VA04666 */
   mdpcall = 0x04,             /* Indicate call from DMSMDP */
   loadincl = 0x02,            /* LOAD, INCLUDE 1=LOAD 0=INCLUDE   @VA19079 */
   gen370fl = 0x01,            /* SET GEN370 Flag                  @VR3W4PQ */
   nuc1osac = 0x80,            /* 1st O/S disk being accessed      @V6RFGMY */
   nuc1acer = 0x40,            /* 1st O/S disk access error        @V6RFGMY */
   nuctviof = 0x20,            /* SET TVICALL OFF                  @S00147G */
   nuctvisl = 0x10,            /* SET TVICALL SL                   @S00147G */
   nuctnevr = 0x08,            /* SET TAPENEVR 1-OFF 0-ON          @VA62366 */
   nuctcslo = 0x04,            /* SET TAPECSL OFF                  @VA63002 */
   nucfplca = 0x02,            /* Pipes intercepting command output@SL1387G */
   nuc5be01 = 0x01,            /* Reserved for future IBM use      @V6S00VB */
   compswt = 0x80,             /* Compiler switch */
   ossmnu = 0x40,              /* DMSSMN unconditional flag */
   osreset = 0x20,
   oswait = 0x10,              /* Used by OS-WAIT and CMS-WAITECB  @V6GM18E */
   dyld = 0x08,                /* Dynamic loading in process */
   dylibo = 0x04,              /* Omit dynamic library scan */
   dylibnow = 0x02,            /* Dynamic library scan */
   dymbrnm = 0x01,             /* Linked via member name */
   noimpex = 0x80,             /* No implied exec commands */
   noimpcp = 0x40,             /* No implied CP commands */
   nostdsyn = 0x20,            /* No standard synonyms */
   noabbrev = 0x10,            /* No command abbreviations */
   nopagrel = 0x08,            /* No automatic page release */
   novmread = 0x04,            /* No automatic VM console read */
   nuc5e002 = 0x02,            /* Reserved for future IBM use      @V6S00VB */
   rdtdrct = 0x01,             /* Console read Type=Direct         @V6GM58E */
   kxswitch = 0x80,            /* Kill execution switch */
   koswitch = 0x40,            /* Kill tracing switch */
   relpages = 0x20,            /* Release pages switch */
   grafdev = 0x10,             /* Graphics console */
   qswitch = 0x08,             /* Quiet SW for CRD */
   noddsk = 0x04,              /* Don't access D disk */
   negits = 0x02,              /* Negative return code from DMSITS */
   attnhit = 0x01,             /* Attention posted                 @VA05051 */
   notypout = 0x80,            /* No typing - set by exec */
   notyping = 0x40,            /* No typing - set by HT */
   nordymsg = 0x20,            /* No ready message to be typed */
   nordytim = 0x10,            /* No time on ready message */
   rederrid = 0x08,            /* Error code to be typed in red */
   noerrmsg = 0x04,            /* No error messages to be typed */
   noerrtxt = 0x02,            /* No text on error messages */
   speclf = 0x01,              /* Linefeed for typewriter CCW */
   dbgexec = 0x80,             /* DEBUG executing */
   dbgpgmck = 0x40,            /* DEBUG entered by a program check */
   dbgexint = 0x20,            /* DEGUB entered by an external interrupt */
   dbgabn = 0x10,              /* DEBUG entered from DMSABE        @V6S00VB */
   dbgnshr = 0x08,             /* No shared-segment present */
   dbgshr = 0x04,              /* Shared-segment present */
   dbgrecur = 0x02,            /* Recursion flag */
   abnxtsw = 0x01,             /* User ABEND exit taken            @V6GM28E */
   exreset = 0x80,             /* OSRESET wanted  0=YES 1=NO       @VA16886 */
   ostypld = 0x40,             /* OS type load  1=OS type load     @VA19633 */
   donthash = 0x20,            /* Do not invoke R/W disk hashing   @V6KUEZ3 */
   nuctnabl = 0x10,            /* TOD clock accounting enabled     @V6KV391 */
   nuccpcmd = 0x08,            /* DMSINT check for CP command      @VA20722 */
   nuclked = 0x04,             /* LKED command issued              @VA21966 */
   nuc4kkey = 0x02,            /* 4K storage key facility exists   @V6MW4ZS */
   nucvectr = 0x01,            /* 1=Vector facility is in use      @V6KSA1T */
   nucpendw = 0x80,            /* Pending write, update CMS window @V6MV7TB */
   nucexec = 0x40,             /* DMSINT check for IMPLIED EXEC    @VA24694 */
   nucserve = 0x20,            /* Set server  0=Off 1=On           @V6RCHVB */
   nucsrvab = 0x10,            /* Private server ABEND recursion   @V6RCHVB */
   nuccomdr = 0x08,            /* COMDIR status flag               @V6RJKN7 */
   nucurlbk = 0x04,            /* Current LINKBLK position         @V6PXKP2 */
   nuc5e502 = 0x02,            /* Reserved for future IBM use      @V6SF4VB */
   nucipldn = 0x01,            /* IPL done (for private server)    @V6SF4VB */
   /* Execflags byte, 5e6                                            */
   execrun = 0x80,             /* Exec command running */
   execstop = 0x40,            /* Halt interpreter recognized      @V6GMAL1 */
   execmask = 0x20,            /* Halt interpreter enabled         @V6GMAL1 */
   exechalt = 0x10,            /* Halt interpreter has been issued @V6GMAL1 */
   exectrst = 0x08,            /* Trace can be reset by XEDIT */
   nucexsst = 0x04,            /* Exec segment status  0=off 1=on  @V6MZ4U9 */
   exectmsk = 0x02,            /* Trace start enabled */
   exectrac = 0x01,            /* Exec trace requested */

   prfpoff = 0x80,             /* Storage protection is shut off */
   prftsys = 0x40,             /* System routine in transient area */
   prfusys = 0x20,             /* System routine in user area */
   tsoatcnl = 0x80,            /* Read cancelled by attention */
   subrej = 0x08,              /* Subset command reject */
   subrtn = 0x04,              /* Subset-return */
   subinit = 0x02,             /* Subset initialization */
   subact = 0x01,              /* Subset active */
   nucmxa = 0x80,              /* Virtual machine in XA mode       @V6PXNTE */
   nucma4a8 = 0x40,            /* CP supports Diag x'A4'/'A8'      @V6PXNTE */
   nucmec = 0x20,              /* 370 machine with ECMODE on       @V6PXKLR */
   nucla20 = 0x10,             /* Default LOAD address is 20000    @V6PXV1R */
   nucm210 = 0x08,             /* CP supports Diag x'210'          @V6S93VB */
   nucmxc = 0x04,              /* Virtual machine in XC mode       @V6S80VB */
   nucm370 = 0x02,             /* Virtual machine in 370 mode      @V6SR6S1 */
   nucmcds = 0x01,             /* MCDS feature present in hardware @VR1BR4Z */
   nucta31 = 0x80,             /* AMODE of 31                      @V6PXV1R */
   nucta24 = 0x40,             /* AMODE of 24                      @V6PXV1R */
   nuctaany = nucta31+nucta24, /* AMODE of ANY                     @V6PXV1R */
   nucta64 = 0x01,             /* Reserved for CEC                 @SL432SG */
   nucmdmap = 0x80,            /* Indicates the loader table has   @VA36272 */
   nucnrst = 0x80,             /* AMSERV 'NORESET' option specified@V6RUOP2 */
   nucgeexc = 0x80,            /* An exit is executing             @VR1BV6P */
   nucgelst = 0x40,            /* Executing exit is last           @VR1BV6P */
   nucgenxt = 0x20,            /* Current points to next to invoke @VR1BV6P */
   nucteent = 0x10,            /* Trace End immediate requested    @SI540VP */
   nucc6308 = 0x08,            /* Reserved for future IBM use      @VR100VB */
   nucc6304 = 0x04,            /* Reserved for future IBM use      @VR100VB */
   nucc6302 = 0x02,            /* Reserved for future IBM use      @VR100VB */
   nucc6301 = 0x01,            /* Reserved for future IBM use      @VR100VB */
   vsamrun = 0x80,             /* VSAM system loaded */
   vsjobcat = 0x40,            /* VSAM job catalog active */
   vipinit = 0x20,             /* DMSVIP has been initialized */
   vsamserv = 0x10,            /* CMS/AMS system loaded (AMSERV running) */
   vipsop = 0x08,              /* OS interface SVC 2 call */
   viptclos = 0x04,            /* OS TCLOSE call */
   vsamsos = 0x02,             /* OS AMSERV/CATCHECK running       @V6GM7T5 */
   vsractiv = 0x01,            /* DMSVSR (VSAM reset) active       @VA45647 */
   dosbam = 0x80,              /* FB-512 support available         @V62A1B4 */
   nucosrun = 0x80,            /* OSRUN command issued             @V6BE17A */
   nucsysdf = 0x40,            /* $SYSLIB defined by LDR suprt     @V6BE17A */
   nucglobl = 0x20,            /* GLOBAL done by OSRUN             @V6BE1E1 */
   nucosrld = 0x10,            /* Member loaded for OSRUN          @V6BE1E1 */
   imactive = 0x80,            /* Immediate command escape char    @V6GM3H9 */
   rlddwsz = 8192,             /* Size of the RLDDATA buffer       @V6KRAMB */
   nucdbsys = 0x80,            /* SET DBCS SYSTEM                  @VR2A62I */
   nucdbon = 0x40,             /* SET DBCS ON|OFF                  @VR2A62I */
   nuchstsz = 8190,            /* Size of the history buffer       @V6MSCXC */
};
#endif
