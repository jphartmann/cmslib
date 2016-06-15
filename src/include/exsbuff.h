#if !defined(__H_EXSBUFF)
#define __H_EXSBUFF
struct exsbuff
{
   unsigned char exstype;      /* Type of record */
   unsigned char exsfstyp;     /* Filesystemtype                    @VR5FQXY */
   short exslen;               /* Length of actual data passed back @V6S805H */
   union
   {
      struct
      {
         union
         {
            struct
            {
               unsigned char exsffn[8];    /* Filename */
               unsigned char exsfft[8];    /* Filetype */
            };
            unsigned char exsfsubd[16]; /* Subdirectory name(16 characters) @V6RTR6U */
         };
         unsigned char exsffmn;      /* Filemode number */
         unsigned char exsfrecf;     /* Record Format */
         unsigned char exsfrecv;     /* Recoverability                   @V6STF5H */
         unsigned char exsfovwr;     /* Overwrite                        @V6STF5H */
         int exsfrecl;               /* Record length */
         int exsfblks;               /* Number of Blocks */
         int exsfrecs;               /* Number of Records */
         unsigned char exsfdatd[3];  /* Date (decimal yymmdd) */
         unsigned char exsffm;       /* File mode                        @VR2MJ5H */
         unsigned char exsftimd[3];  /* Time (decimal hhmmss) */
         unsigned char exsfrfm;      /* Real File Mode                   @VR2MJ5H */
         unsigned char exsfdatc[8];  /* Date (character yy/mm/dd) */
         unsigned char exsftimc[8];  /* Time (character hh:mm:ss) */
         unsigned char exsfuser[8];  /* Userid */
         unsigned char exsfstat;     /* Status */
         unsigned char exsfrath;     /* Read Authority */
         unsigned char exsfwath;     /* Write Authority */
         unsigned char exsfprot;     /* External protection indicator */
         union
         {
            struct
            {
               unsigned char exsfdlrd[3];  /* DoLR (decimal yymmdd)            @V6RTR6U */
               unsigned char __fill5;      /* Reserved                         @V6RTR6U */
               unsigned char exsfdlrc[8];  /* DoLR (character yy/mm/dd)        @V6RTR6U */
            };
            unsigned char exsfdolr[12]; /* @V6S956U */
         };
         union
         {
            struct
            {
               unsigned char exsfcdtd[3];  /* Creation Date (decimal yymmdd)   @V6S956U */
               unsigned char __fill7;      /* Reserved                         @V6S956U */
               unsigned char exsfctmd[3];  /* Creation Time (decimal hhmmss)   @V6S956U */
               unsigned char __fill8;      /* Reserved                         @V6S956U */
               unsigned char exsfcdtc[8];  /* Creation Date (char yy/mm/dd)    @V6S956U */
               unsigned char exsfctmc[8];  /* Creation Time (char hh:mm:ss)    @V6S956U */
            };
            unsigned char exsfdtoc[24]; /* @V6S956U */
         };
         union
         {
            struct
            {
               int exsfmaxb;               /* Maximum Blocks                   @VR1MG5H */
               int exsfdatb;               /* Data Blocks                      @VR1MG5H */
               int exsfsysb;               /* System Blocks                    @VR1MG5H */
               unsigned char exsfmigr;     /* Migrated file                    @VR1MG5H */
               union
               {
                  struct
                  {
                     unsigned char exsfdra1[8];  /* DRA field 1                      @VR1MG5H */
                     unsigned char exsfdra2[8];  /* DRA field 2                      @VR1MG5H */
                     unsigned char exsfdra3[8];  /* DRA field 3                      @VR1MG5H */
                  };
                  unsigned char exsfdras[24]; /* DRA values                       @VR1MG5H */
               };
               unsigned char exsfunqd[16]; /* Unique id                        @VR1MG5H */
            };
            unsigned char exsftdfm[53]; /* @S63465H */
         };
         union
         {
            struct
            {
               unsigned char exsfdirl;     /* Length of Directory ID           @VR3W75H */
               unsigned char exsfdird[153]; /* Directory ID                     @VR3W75H */
            };
            unsigned char exsfconv[154]; /* Dirname and length values        @VR3W75H */
         };
         union
         {
            struct
            {
               unsigned char exsfdlcd[3];  /* DOLC          (decimal yymmdd)   @VR43IS0 */
               unsigned char __fill13;     /* Reserved                         @VR43IS0 */
               unsigned char exsftlcd[3];  /* TOLC          (decimal hhmmss)   @VR43IS0 */
               unsigned char __fill14;     /* Reserved                         @VR43IS0 */
               unsigned char exsfdlcc[8];  /* DOLC          (char yy/mm/dd)    @VR43IS0 */
               unsigned char exsftlcc[8];  /* TOLC          (char hh:mm:ss)    @VR43IS0 */
            };
            unsigned char exsfdtlc[24]; /* @VR43IS0 */
         };
         union
         {
            struct
            {
               unsigned char exsfdaxd[4];  /* Date (decimal yyyymmdd)          @VR61NXY */
               unsigned char exsfdaxc[10]; /* Date (character yyyy/mm/dd)      @VR61NXY */
               unsigned char exsfdaxi[10]; /* Date (character yyyy-mm-dd)      @VR61NXY */
               unsigned char exsfdrxd[4];  /* DoLR (decimal yyyymmdd)          @VR61NXY */
               unsigned char exsfdrxc[10]; /* DoLR (character yyyy/mm/dd)      @VR61NXY */
               unsigned char exsfdrxi[10]; /* DoLR (character yyyy-mm-dd)      @VR61NXY */
               unsigned char exsfcdxd[4];  /* Creation Date (decimal yyyymmdd) @VR61NXY */
               unsigned char exsfcdxc[10]; /* Creation Date (char yyyy/mm/dd)  @VR61NXY */
               unsigned char exsfcdxi[10]; /* Creation Date (char yyyy-mm-dd)  @VR61NXY */
               unsigned char exsfdcxd[4];  /* DOLC (decimal yyyymmdd)          @VR61NXY */
               unsigned char exsfdcxc[10]; /* DOLC (character yyyy/mm/dd)      @VR61NXY */
               unsigned char exsfdcxi[10]; /* DOLC (character yyyy-mm-dd)      @VR61NXY */
            };
            unsigned char exsf2000[96]; /* these are for year 2000      @VR61NXY */
         };
         unsigned char exsfres;      /* Reserved for future              @VR61NXY */
      };
   };
   struct
   {
      unsigned char exsddirl;     /* Length of Directory ID */
      unsigned char exsddird[153]; /* Directory ID */
      unsigned char exsdrath;     /* Read Authority */
      unsigned char exsdwath;     /* Write Authority */
      unsigned char exsdprot;     /* External protection */
      union
      {
         struct
         {
            unsigned char exsddrat;     /* Directory Read Authority        @V6S805H */
            unsigned char exsddwat;     /* Directory Write Authority       @V6S805H */
            unsigned char exsdattr;     /* Directory Attribute             @V6S805H */
            unsigned char exsdnrat;     /* Directory NEWREAD Authority     @V6S805H */
            unsigned char exsdnwat;     /* Directory NEWWRITE Authority    @V6S805H */
         };
         unsigned char exsdmcds[5];  /* @VR1MG5H */
      };
      union
      {
         struct
         {
            unsigned char exsddra1[8];  /* DRA field 1                     @VR1MG5H */
            unsigned char exsddra2[8];  /* DRA field 2                     @VR1MG5H */
            unsigned char exsddra3[8];  /* DRA field 3                     @VR1MG5H */
         };
         unsigned char exsddras[24]; /* DRA values                      @VR1MG5H */
      };
      unsigned char exsdunqd[16]; /* Unique Id                       @VR3W75H */
      union
      {
         struct
         {
            unsigned char exsddlcd[3];  /* DOLC          (decimal yymmdd)  @VR43IS0 */
            unsigned char __fill20;     /* Reserved                        @VR43IS0 */
            unsigned char exsdtlcd[3];  /* TOLC          (decimal hhmmss)  @VR43IS0 */
            unsigned char __fill21;     /* Reserved                        @VR43IS0 */
            unsigned char exsddlcc[8];  /* DOLC          (char yy/mm/dd)   @VR43IS0 */
            unsigned char exsdtlcc[8];  /* TOLC          (char hh:mm:ss)   @VR43IS0 */
         };
         unsigned char exsddtlc[24]; /* @VR43IS0 */
      };
      union
      {
         struct
         {
            unsigned char exsdcdtd[3];  /* Creation Date (decimal yymmdd)  @VR43IS0 */
            unsigned char __fill23;     /* Reserved                        @VR43IS0 */
            unsigned char exsdctmd[3];  /* Creation Time (decimal hhmmss)  @VR43IS0 */
            unsigned char __fill24;     /* Reserved                        @VR43IS0 */
            unsigned char exsdcdtc[8];  /* Creation Date (char yy/mm/dd)   @VR43IS0 */
            unsigned char exsdctmc[8];  /* Creation Time (char hh:mm:ss)   @VR43IS0 */
         };
         unsigned char exsddtoc[24]; /* @VR43IS0 */
      };
      union
      {
         struct
         {
            unsigned char exsddcxd[4];  /* DOLC (decimal yyyymmdd)         @VR61NXY */
            unsigned char exsddcxc[10]; /* DOLC (character yyyy/mm/dd)     @VR61NXY */
            unsigned char exsddcxi[10]; /* DOLC (character yyyy-mm-dd)     @VR61NXY */
            unsigned char exsdcdxd[4];  /* Creation Date (decimal yyyymmdd)@VR61NXY */
            unsigned char exsdcdxc[10]; /* Creation Date (char yyyy/mm/dd) @VR61NXY */
            unsigned char exsdcdxi[10]; /* Creation Date (char yyyy-mm-dd) @VR61NXY */
         };
         unsigned char exsd2000[48]; /* these are for year 2000     @VR61NXY */
      };
      unsigned char exsdres[6];   /* Reserved for future             @VR61NXY */
   };
};

enum exstype
{
   exstfile = '1',             /* EXSTYPE of FILE */
   exstdir = '2',              /* EXSTYPE of DIR */
};

enum  exsfstyp
{
   exsosfs = '0',              /* Filesystemtype = SFS file space   @VR5FQXY */
   exsobfs = '1',              /* Filesystemtype = BFS file space   @VR5FQXY */
   exsomd = '2',               /* Filesystemtype = minidisk         @VR5FQXY */
};

enum exsfstat
{
   exsfstb = '1',              /* Base */
   exsfsta = '2',              /* Alias */
   exsfste = '3',              /* Erased */
   exsfstr = '4',              /* Revoked */
   exsfsto = '6',              /* External Object                  @VR1MG5H */
   exsfstm = '7',              /* Minidisk                         @SC691PB */
   exsfstd = '8',              /* OS or DOS formatted minidisk     @SC691PB */
};

enum
{
   exsfryes = '1',             /* Read Authority exists */
   exsfrno = '0',              /* No Read Authority */
   exsfwyes = '1',             /* Write Authority exists */
   exsfwno = '0',              /* No Write Authority */
   exsfpyes = '1',             /* External protection exists */
   exsfpno = '0',              /* No External protection */
};
#endif
