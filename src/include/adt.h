#if !defined(__H_ADT)
#define __H_ADT
/* PREFIX_LEN = 8                                               @SJ6289E */
/* ACTIVE DISK TABLE BLOCK                                               */
struct adt
{
/*        NEEDED FOR READ-ONLY DISKS AND READ-WRITE DISKS                */
   void * adtptr;              /* PTR TO NEXT ADT BLOCK IN CHAIN   @V62B0H2 */
   int adtbwptr;               /* ADDRESS OF PREVIOUS ADT(BW CHAIN)@V62B3H2 */
   void * adtdta;              /* DEVICE TABLE ADDRESS IN NUCON    @V62B0H2 */
   void * adtfda;              /* FILE DIRECTORY (PSTAT) ADDRESS   @V62B0H2 */
   void * adtdfp1;             /* DIRECTORY FILE LEVEL 1 POINTER   @V62B0H2 */
   void * adtdfp2;             /* DIRECTORY FILE LEVEL 2 POINTER   @V62B0H2 */
   void * adtdfp3;             /* DIRECTORY FILE LEVEL 3 POINTER   @V62B0H2 */
   int adthbct;                /* FST HYPERBLOCK COUNT             @V62B0H2 */
   int adtfstc;                /* NUMBER OF FILES IN THE DIRECTORY.@V6RFG1T */
/*                             THIS INCLUDES FILES WHICH HAVE AN@V6RFG1T */
/*                             FST IN THE DIRECTORY AND NEW     @V6RFG1T */
/*                             FILES WHICH ARE CURRENTLY ACTIVE,@V6RFG1T */
/*                             EVEN IF THEY HAVE NO RECORDS.    @V6RFG1T */
/*                             FOR EDF MINIDISKS, UPDATES TO    @VA35319 */
/*                             THIS FIELD SHOULD BE MADE USING  @VA35319 */
/*                             THE DMSRBADJ MACRO WHENEVER      @VA35319 */
/*                             ADTARES ALSO NEEDS CHANGING TO   @VA35319 */
/*                             REFLECT THE NEW ADTFSTC VALUE.   @VA35319 */
   int adtchba;                /* ADDRESS OF CURRENT HYPERBLOCK.   @V62B0H2 */
   int adtcfst;                /* DISP. OF CURRENT FST ENTRY       @V62B0H2 */
   int __fill1;                /* Reserved for future IBM use      @S81491T */
/*                               2 bytes device address         @S81491T */
/*                               1 byte device class            @S81491T */
/*                               1 byte device type             @S81491T */
   int __fill2;                /* Overlay of OSADTDSK, available   @S81491T */
/*                               for future use for accesed     @S81491T */
/*                               file modes other than OS or    @S81491T */
/*                               DOS formatted disks.           @S81491T */
   int osadtsv1;               /* O/S SAVE AREA                    @V62B0H2 */
   int adtleft;                /* Number of Blocks left            @VR2YD2O */
/*                             in the minidisk or, in           @VR2YD2O */
/*                             the case of an SFS top           @VR2YD2O */
/*                             directory, the number            @VR2YD2O */
/*                             of blocks remaining in           @VR2YD2O */
/*                             the containing                   @VR2YD2O */
/*                             filespace.  This is              @VR2YD2O */
/*                             maintained for SFS top           @VR2YD2O */
/*                             directories via cache            @VR2YD2O */
/*                             notifications (CNRs) as          @VR2YD2O */
/*                             space consumption is             @VR2YD2O */
/*                             committed by SFS. It is          @VR2YD2O */
/*                             not updated for space            @VR2YD2O */
/*                             consumed through                 @VR2YD2O */
/*                             subdirectories or for            @VR2YD2O */
/*                             administrative changes           @VR2YD2O */
/*                             to the number of blocks          @VR2YD2O */
/*                             assigned.  However, all          @VR2YD2O */
/*                             values are made current          @VR2YD2O */
/*                             when a directory is              @VR2YD2O */
/*                             accessed or reaccessed.          @VR2YD2O */
/*                             This field is not set            @VR2YD2O */
/*                             for SFS subdirectories           @VR2YD2O */
/*                             except as a byproduct            @VR2YD2O */
/*                             of the ADT Lookup                @VR2YD2O */
/*                             function, which queries          @VR2YD2O */
/*                             the space values for             @VR2YD2O */
/*                             subdirectories and also          @VR2YD2O */
/*                             leaves these values              @VR2YD2O */
/*                             in the ADT space fields.         @VR2YD2O */
   int __fill3;                /* Reserved for future IBM use      @S81491T */
   void * adtcuct;             /* CURRENT UCT ENTRY ADDRESS WHEN   @V6RFG91               ADT IS FOR SFS DIRECTORY         @V6RFG91 */
   unsigned char adtm;         /* MODE LETTER (A,B,C,...,X,Y,Z)    @V62B0H2 */
   unsigned char adtmx;        /* EXTENSION-OF-MODE LETTER         @V62B0H2 */
   unsigned char adtflg1;      /* FLAG BYTE 1                      @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQUATES FOR FIRST FLAG BYTE (ADTFLG1)                 @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQU   X'80'          Available for future IBM use     @S81491T */
/*        EQU   X'10'          Available for future IBM use     @S81491T */
/*                             USED TO AVOID MODS TO FSTS.      @V6MW4P4 */
/*                             lowest available block number.   @VR4HZ1T */
/*        EQU   X'01'          Available for future IBM use     @S85661T */
/*                                                              @V62B0H2 */
   unsigned char adtflg2;      /* FLAG BYTE 2                      @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQUATES FOR SECOND FLAG BYTE (ADTFLG2)                @V62B0H2 */
/*                                                              @V62B0H2 */
/*                                                              @V62B0H2 */
   unsigned char adtflg3;      /* FLAG BYTE 3                      @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQUATES FOR THE THIRD FLAG BYTE (ADTFLG3)             @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQU   X'80'          Available for future IBM use     @S81491T */
/*        EQU   X'40'          Available for future IBM use     @S81491T */
/*        EQU   X'01'          Available for future IBM use     @S81491T */
/*                               DMSFNS, DMSAUD & DMSERC)       @V6RFG1Q */
/*                                                              @V62B0H2 */
   unsigned char adtflg4;      /* FLAG BYTE 4                      @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQUATES FOR FOURTH FLAG BYTE (ADTFLG4)                @V62B0H2 */
/*                                                              @V62B0H2 */
/*        EQU   X'20'          Available for future IBM use     @S81491T */
/*                             user machine address space but   @V6S801T               is in a data space               @V6S801T */
/*                             least VM/ESA R 1.2.0             @VR2YDTJ */
/*                             directory.                       @VA38885 */
/*                                                              @V62B0H2 */
   unsigned char adtftyp[0];   /* File type flag bytes             @V6S801T */
   unsigned char adtftyp1; /* File type flag byte 1            @V6S801T */
   unsigned char adtftyp2; /* File type flag byte 2            @V6S801T */
   void * adtdiskc;            /* DISK CONSTANTS TABLE IN DMSDIP   @V6M00MJ */
   void * adtsectr;            /* SECTOR NUMBER TABLE IN DMSDIP    @V6M00MJ */
   int adtnacn;                /* NUMBER OF NEW FILES WHICH ARE    @V6RFG1T */
/*                             CURRENTLY ACTIVE, BUT DO NOT YET @V6RFG1T */
/*                             HAVE AN FST IN THE DIRECTORY.    @V6RFG1T */
   double adt2nd[0];           /* @V62B0H2 */
   int adtmsk;                 /* ALLOCATION MAP DATA HBLK CHAIN   @S81491T */
   int adtamp1;                /* ALLOCATION MAP LEVEL 1 POINTER   @V62B0H2 */
   int adtamp2;                /* ALLOCATION MAP LEVEL 2 POINTER   @V62B0H2 */
   int adtamp3;                /* ALLOCATION MAP LEVEL 3 POINTER   @V62B0H2 */
   int adtdamap;               /* DEALLOCATION MAP HBLK CHAIN      @V62B0H2 */
   void * adtlhba;             /* POINTER TO LAST FST HYPER-BLOCK  @V62B0H2 */
   int adtlfst;                /* DISP. OF LAST FST IN LAST HYPBLK @V62B0H2 */
   int adtanacw;               /* ALT. NUMBER OF ACT. WRITE FILES  @V62B0H2 */
   int adtares;                /* COUNT OF MINIDISK BLOCKS THAT    @VA35319 */
/*                             ARE RESERVED FOR DIRECTORY DATA  @VA35319 */
/*                             AND POINTER BLOCKS AND FOR       @VA35319 */
/*                             ALLOCATION MAP DATA AND POINTER  @VA35319 */
/*                             BLOCKS.  THE FIRST PART OF THE   @VA35319 */
/*                             VALUE DEPENDS ON THE NUMBER OF   @VA35319 */
/*                             FILES ON THE MINIDISK; THE       @VA35319 */
/*                             SECOND PART IS DETERMINED AT     @VA35319 */
/*                             FORMAT TIME AND IS CONSTANT      @VA35319 */
/*                             THEREAFTER.  AFTER UPDISK        @VA35319 */
/*                             (DMSAUD) PROCESSING, THIS COUNT  @VA35319 */
/*                             GIVES THE NUMBER OF MINIDISK     @VA35319 */
/*                             BLOCKS REQUIRED IF ALL DIRECTORY @VA35319 */
/*                             AND ALLOCATION MAP BLOCKS WERE   @VA35319 */
/*                             CHANGED.  BEFORE UPDISK          @VA35319 */
/*                             PROCESSING, EACH DIRECTORY BLOCK @VA35319 */
/*                             REQUIRING ALLOCATION FOR THE     @VA35319 */
/*                             FIRST TIME IS COUNTED TWICE --   @VA35319 */
/*                             ONCE FOR THE BLOCK TO BE         @VA35319 */
/*                             ALLOCATED AND ONCE FOR ITS       @VA35319 */
/*                             SHADOW -- TO PRECLUDE OPENING    @VA35319 */
/*                             MORE FILES THAN CAN BE CLOSED.   @VA35319 */
   int adtntfin;               /* COUNTER FOR NUMBER OF DMSOPEN    @VR2MJ4H */
/*                             MINIDISK OUTPUT FILES THAT       @VR2MJ4H */
/*                             WERE TFINISED WHILE DOING        @VR2MJ4H */
/*                             FINIS * *                        @VR2MJ4H */
   int __fill4;                /* Reserved for future IBM use      @S81491T */
   int adtchmap;               /* CHANGE MAP HBLK CHAIN            @V62B0E5 */
   void * adtahtab;            /* Address of Hyperblock Map        @V6S80KI */
   void * adtahash;            /* Address of Hash Table            @V6S80KI */
/*                                                              @V62B0E5 */
/*        MAPPING OF VOLUME LABEL                               @V62B0E5 */
/*                                                              @V62B0E5 */
   double __fill5[0];          /* @V62B0E5 */
   unsigned char adtident[4];  /* VOL START / LABEL IDENTIFIER     @V62B0H2 */
   unsigned char adtid[6];     /* VOL START / VOL IDENTIFIER       @V62B0H2 */
   unsigned char adtver[2];    /* VERSION LEVEL                    @V62B0H2 */
   int adtdbsiz;               /* DISK BLOCK SIZE                  @V62B0H2 */
   int adtdop;                 /* DISK ORIGIN POINTER              @V62B0H2 */
   int adtcyl;                 /* NUM OF FORMATTED CYL ON DISK     @V62B0H2 */
   int adtmcyl;                /* MAX NUM FORMATTED CYL ON DISK    @V62B0H2 */
   int adtnum;                 /* Number of Blocks                 @V62B0H2 */
/*                             assigned to the minidisk         @VR20020 */
/*                             or, in the case of an            @VR20020 */
/*                             SFS top directory, the           @VR20020 */
/*                             number of blocks                 @VR20020 */
/*                             assigned to the                  @VR20020 */
/*                             containing filespace.            @VR20020 */
/*                             This field is not set            @VR20020 */
/*                             for SFS subdirectories           @VR20020 */
/*                             except as a byproduct of         @VR20020 */
/*                             the ADT Lookup function,         @VR20020 */
/*                             which queries the space          @VR20020 */
/*                             values for subdirs and           @VR20020 */
/*                             also leaves these values         @VR20020 */
/*                             in the ADT space fields.         @VR20020 */
   int adtused;                /* Number of Blocks used            @V62B0H2 */
/*                             in the minidisk or, in           @VR20020 */
/*                             the case of an SFS top           @VR20020 */
/*                             directory, the number of         @VR20020 */
/*                             blocks consumed in the           @VR20020 */
/*                             containing filespace.            @VR20020 */
/*                             This field is not set            @VR20020 */
/*                             for SFS subdirectories           @VR20020 */
/*                             except as a byproduct of         @VR20020 */
/*                             the ADT Lookup function,         @VR20020 */
/*                             which queries the space          @VR20020 */
/*                             values for subdirs and           @VR20020 */
/*                             also leaves these values         @VR20020 */
/*                             in the ADT space fields.         @VR20020 */
   int adtfstsz;               /* SIZE OF FST                      @V62B0H2 */
   int adtnfst;                /* NUMBER OF FST'S PER BLOCK        @V62B0H2 */
   unsigned char adtdcred[6];  /* DISK CREATION DATE (YYMMDDHHMMSS)@V62B0H2 */
   unsigned char adtflgl;      /* LABEL FLAG BYTE (ADTFLGL)        @VR61NXY */
/*                                                              @VR61NXY */
/*        EQUATES FOR ADT LABEL FLAG BYTE (ADTFLGL)             @VR61NXY */
/*                                                              @VR61NXY */
/*                             (0=19, 1=20), corresponds to     @VR61NXY */
/*                             ADTDCRED.                        @VR61NXY */
   unsigned char __fill6;      /* RESERVED                         @VR61NXY */
   int adtoffst;               /* DISK OFFSET WHEN RESERVED        @V6GNF8E */
   int adtamnb;                /* ALLOC MAP BLOCK WITH NEXT HOLE   @V6MW41Q */
   int adtamnd;                /* DISP INTO HBLK DATA OF NEXT HOLE @V6MW41Q */
   int adtamup;                /* DISP INTO USER PART OF ALLOC MAP @V6MW41Q */
   int adtofcnt;               /* Count of SFS open files for this @VA53138 */
/*                             ADT                              @VA53138 */
/*                             NOTE:  ADTOFCNT IS NOT REALLY    @VA53138 */
/*                             PART OF THE VOLUME LABEL - IT    @VA53138 */
/*                             IS NOT USED FOR MINIDISKS.       @VA53138 */
   unsigned char adtsfnam[8];  /* NAME OF SHARED SEGMENT           @V6MW4P4 */
/*                                                              @V62B0E5 */
/*        MAPPING OF OS FIELDS IN VOL LABEL                     @V62B0E5 */
/*                                                              @V62B0E5 */
/*                                                              @V6RFG91 */
/* SFS DIRECTORY FIELDS                                         @V6RFG91 */
/*                                                              @V6RFG91 */
   double __fill7[0];          /* @V6S80KI */
   union
   {
      unsigned char adtfqdn[144]; /* FULLY QUALIFIED DIRECTORY NAME   @V6RFG91 */
      struct
      {
         unsigned char adtfpid[8];   /* FILE POOL ID                     @V6RFG91 */
         unsigned char adtowner[8];  /* DIRECTORY OWNER                  @V6RFG91 */
         union
         {
            unsigned char adtnall[128]; /* ALL THE QUALIFIERS               @V6RFG91 */
            struct
            {
               unsigned char adtn1[16];    /* QUALIFIER NUMBER 1               @V6RFG91 */
               unsigned char adtn2[16];    /* QUALIFIER NUMBER 2               @V6RFG91 */
               unsigned char adtn3[16];    /* QUALIFIER NUMBER 3               @V6RFG91 */
               unsigned char adtn4[16];    /* QUALIFIER NUMBER 4               @V6RFG91 */
               unsigned char adtn5[16];    /* QUALIFIER NUMBER 5               @V6RFG91 */
               unsigned char adtn6[16];    /* QUALIFIER NUMBER 6               @V6RFG91 */
               unsigned char adtn7[16];    /* QUALIFIER NUMBER 7               @V6RFG91 */
               unsigned char adtn8[16];    /* QUALIFIER NUMBER 8               @V6RFG91 */
            };
         };
      };
   };
   int adttid;                 /* SDS TUPPLE IDENTIFIER            @V6RFG91 */
   int adtscid;                /* SDS SEQUENTIAL CHANGE IDENTIFIER @V6RFG91 */
   unsigned char adtdoid[8];   /* OBJECT ID OF DIRECTORY           @V6RFG91 */
   unsigned char adtpdoid[8];  /* OBJECT ID OF PARENT DIRECTORY    @V6RFG91 */
   void * adtcfwd;             /* CACHE FORWARD POINTER            @V6RFG91 */
   void * adtcbwd;             /* CACHE BACKWARD POINTER           @V6RFG91 */
   int adtodt;                 /* NUMBER OF ODTS FOR THIS ADT      @V61MG91 */
   unsigned char adtflg5;      /* FLAG BYTE 5                      @V6RFG91 */
/*                                                              @V6RFG91 */
/*        EQUATES FOR FIFTH FLAG BYTE (ADTFLG5)                 @V6RFG91 */
/*                                                              @V6RFG91 */
/*                                filemode is released          @V6RFGJT */
   unsigned char __fill10[3];  /* @V6RFG91 */
   union
   {
      double adtts;               /* TIME STAMP                       @V6RFG91 */
      struct
      {
         int adttssec;               /* UNITS OF 1.048576 SECONDS        @V6RFG91 */
         int adttsfuz;               /* REST OF SPACE FOR STCK           @V6RFG91 */
      };
   };
   void * adtddeta;            /* DELAYED DELETE ENTRY TABLE ADDR  @V6RFG91 */
   int adtddect;               /* DELAYED DELETE ENTRY COUNT       @V6RFG91 */
   double __fill12[0];         /* Directory Control fields         @V6S80KI */
   unsigned char adtasit[8]; /* Address Space Identification     @V6S80KI               Token                            @V6S80KI */
   unsigned char adtalet[4]; /* Access List Entry Token          @V6S80KI */
   int adtaclev;               /* Access Level                     @V6S80KI */
   int adthtsiz;               /* Size of Hash Table in data       @V6S80KI               space, in bytes */
   unsigned char adtflg6; /* Flag byte 6                      @V6S80KI */
/*                                                              @V6S80KI */
/*        Equates for sixth flag byte (ADTFLG6)                 @V6S80KI */
/*                                                              @V6S80KI */
/*                             specific to this user            @V6S80KI */
/*                                                              @V6S80KI */
   unsigned char __fill13[3];  /* Reserved                         @V6S80KI */
   double __fill14[0];         /* ALIGN ON DOUBLE WORD             @V6RFG91 */
/*        OTHER PARAMETERS                                               */
/*        NUCON DEVICE TABLE OFFSETS                                     */
/*                                                              @S81491T */
/*        The following are obsolete CDF fields.                @S81491T */
/*                                                              @S81491T */
/*        CDF support was dropped in VM/ESA Release 1.0.        @S81491T */
/*        The ADT areas previously occupied by these fields     @S81491T */
/*        which were not already overlayed by non-CDF fields    @S81491T */
/*        are now declared available for future use.  The       @S81491T */
/*        fields are left here but are suppressed.  In case of  @S81491T */
/*        any compatibility problems with other products,       @S81491T */
/*        tools, etc. which may still contain outdated CDF      @S81491T */
/*        references, a simple change to invoke the ADT macro   @S81491T */
/*        via ADT CDF=YES will cause the CDF fields to be       @S81491T */
/*        generated.                                            @S81491T */
/*                                                              @S81491T */
/*                                                              @S81491T */
/*        EQUATES FOR FIRST FLAG BYTE (ADTFLG1)                 @S81491T */
/*                                                              @S81491T */
/*                                                              @S81491T */
/*        EQUATES FOR THE THIRD FLAG BYTE (ADTFLG3)             @S81491T */
/*                                                              @S81491T */
};

enum
{
   adtfro = 0x40,              /* CMS READ-ONLY DISK(ATTACH & RDY) @V62B0H2 */
   adtfrw = 0x20,              /* CMS READ-WRITE DISK(ATTACH & RDY)@V62B0H2 */
   adtffstv = 0x08,            /* FST HYPBLKS ARE OF VARYING LNGTH @V62B0H2 */
   adtlowal = 0x04,            /* DMSTRKAL should allocate the     @VR4HZ1T */
   adtrox = 0x02,              /* THIS DISK HAS READ ONLY EXTENSION(S)@V62B0H2 */
   adtfmfd = 0x80,             /* MFD IS IN CORE                   @V62B0H2 */
   adtfalnm = 0x40,            /* ALL FILENAMES ARE IN CORE        @V62B0H2 */
   adtfalty = 0x20,            /* ALL FILETYPES ARE IN CORE        @V62B0H2 */
   adtfmdro = 0x10,            /* MODES 1-5 ARE IN CORE            @V62B0H2 */
   adtfros = 0x04,             /* This is an OS (or DOS) disk      @V6S80KI */
   adtpstm = 0x02,             /* ADT PSTAT CHAIN MODIFIED         @V62B0H2 */
   adtfdos = 0x01,             /* INDICATES THIS IS A DOS DISK     @V62B0H2 */
   adtfrwos = 0x20,            /* READ-WRITE OS OR DOS DISK        @V62B0H2 */
   adtfsort = 0x10,            /* ALL FST HYPERBLOCKS AND          @V62B0H2                 FST ENTRIES SORTED             @V62B0H2 */
   adtforce = 0x08,            /* CMS/DOS/OS DISK FORCED READ-ONLY @V62B0H2 */
   adtfnoab = 0x04,            /* FOR DMSAUD - DON'T ABEND IF      @V62B0H2                 DISK ERROR                     @V62B0H2 */
   adtfupdr = 0x02,            /* UPDISK CALL REQUIRED AFTER FINIS                          OF AN OUTPUT FILE (USED BY     @V6RFG1Q */
   adtedf = 0x80,              /* ENHANCED-DISK-FORMAT DISK        @V62B0H2 */
   adtedfae = 0x40,            /* EDF ACCESS ERASE DONE            @V62B0H2 */
   adtdir = 0x10,              /* ADT IS FOR DIRECTORY             @V6RFG91 */
   adtdird = 0x08,             /* Directory (Hyperblocks (FSTs)    @V6S801T               and Hash Table) is not in the    @V6S801T */
   adtserv2 = 0x04,            /* SFS Directory where server is at @VR2YDTJ */
   adtfmtrl = 0x02,            /* Tell RELEASE not to sort the     @VA38885 */
   adtsfshr = 0x01,            /* SAVED STORAGE ACCESS             @V6MW4P4 */
   # if 0
   adtfbabf = adtdiskc,        /* FBA BLK TO CMS BLK FACTOR        @V6M00MJ */
   adtfbalb = adtsectr,        /* LAST FBA BLK OF THE MINIDISK     @V6M00MJ */
          #endif
   adtcntry = 0x01,            /* Century for disk creation date   @VR61NXY */
   adtdel = 0x80,              /* CACHE HAS BEEN LOGICALLY DELETED @V6RFG91 */
   adtrem = 0x40,              /* CACHE CAN BE RELEASED AT END OF  @V6RFG91                 COMMAND                        @V6RFG91 */
   adtuacc = 0x20,             /* ADT IS ON UNACCESSED CHAIN       @V6RFG91 */
   adtinuse = 0x10,            /* DIRECTORY IS BEING USED BY CMS   @V6RFG91 */
   adtncach = 0x08,            /* CACHE IS NO LONGER IN EXISTENCE  @V6RFG91 */
   adtimmcr = 0x04,            /* Cache should be released as soon @V6RFGJT */
   adtmydir = 0x02,            /* Directory is owned by this user  @V6RFGJT */
   adtserv6 = 0x01,            /* Directory is from Rel 6 filepool @V6S2091 */
   adtdirc = 0x80,             /* Directory has the Directory      @V6S80KI               Control attribute                @V6S80KI */
   adtdirs = 0x40,             /* Directory Control directory is   @V6S801T               from a shared copy and is not    @V6S80KI */
   adtrl = 800,                /* LOGICAL RECORD LENGTH             @V62B0H2 */
   dtad = 0,                   /* DEVICE NUMBER */
   dtadc = 2,                  /* DEVICE CLASS */
   dtadt = 3,                  /* DEVICE TYPE BYTE */
   dtas = 4,                   /* SYMBOLIC DEVICE NAME */
   adtfqqf = 0x04,             /* 200-BYTE QQMSK IS IN FREE STOR@S81491T */
   adtfmin = 0x01,             /* ADT BLOCK IS MINIMUM SIZE     @S85661T */
   adtfupd1 = 0x80,            /* 1ST HALF OF UPDISK CALLED     @S81491T */
   adtfxchn = 0x40,            /* EXTRA CHAIN LINK(S) NEED      @S81491T                    TO BE RETURNED              @S81491T */
};
#endif
