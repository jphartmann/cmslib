#if !defined(__H_SHVBLOCK)
#define __H_SHVBLOCK
/*        ***  LAYOUT OF SHARED-VARIABLE ACCESS CONTROL BLOCK  ***       */
/*   THE CONTROL BLOCKS FOR ACCESSING SHARED VARIABLES ARE CHAINED       */
/*   AS A LIST TERMINATED BY A NULL POINTER.  THE LIST IS ADDRESSED      */
/*   VIA THE 'PRIVATE INTERFACE' PLIST IN A SUBCOMMAND CALL TO A         */
/*   PUBLIC VARIABLE-SHARING ENVIRONMENT (E.G. AS SET UP BY THE          */
/*   EXEC 2 OR SYSTEM PRODUCT INTERPRETER).                     @V6GMAL1 */
/************************************************************** @SI1469E */
/*                                                              @SI1469E */
/* Name - SHVBLOCK                                              @SI1469E */
/*                                                              @SI1469E */
/* Description - Control BLocks for accessing shared variables  @SI1469E */
/*                                                              @SI1469E */
/* DSECT - SHVBLOCK                                             @SI1469E */
/*                                                              @SI1469E */
/* Function - Defines the CMS EXECCOMM Shared Variable Block    @SI1469E */
/*              Structure and some common declares for use.     @SI1469E */
/*                                                              @SI1469E */
/************************************************************** @SI1469E */
struct shvblock
{
   struct shvblock * shvnext;             /* (+0)  CHAIN POINTER (0 IF LAST) */
   union
   {
      void * shvuser;             /* (+4)  NOT USED, AVAILABLE FOR PRIVATE  @V6GMAL1 */
         /*                       use EXCEPT DURING 'FETCH NEXT'         @V6GMAL1 */
      int shvnextnaml;                /* Name buffer length          */
   };
   unsigned char shvcode;      /* (+8)  INDIVIDUAL FUNCTION CODE */
   unsigned char shvret;       /* (+9)  INDIVIDUAL RETURN CODE FLAG */
   short __fill1;              /* RESERVED, SHOULD BE ZERO */
   int shvbufl;                /* (+12)  LENGTH OF 'FETCH' VALUE BUFFER */
   char * shvnama;             /* (+16)  ADDR OF PUBLIC VARIABLE NAME */
   int shvnaml;                /* (+20)  LENGTH OF PUBLIC VARIABLE NAME */
   char * shvvala;             /* (+24)  ADDR OF VALUE BUFFER (0 IF NONE) */
   int shvvall;                /* (+28)  LENGTH OF VALUE (SET BY 'FETCH') */
/*     FUNCTION CODES (SHVCODE):                                         */
/*  The following function codes only apply to the System       @V6MUBR0 */
/*  Product Interpreter.                                        @V6MUBR0 */
/*                                                              @V6MUBR0 */
/*     (Note that the symbolic name codes are lowercase)        @V6MUBR0 */
/*     RETURN CODE FLAGS (SHVRET):                                       */
/*                             (SP interpreter only)            @V6GMAL1 */
/*                             long (EXEC 2 ONLY).              @V6GMAL1 */
};

enum
{
   shvfetch = 'F',             /* copy value of shared var to buffer */
   shvstore = 'S',             /* store given value in shared variable */
   shvdropv = 'D',             /* drop variable                    @v6gmal1 */
   shvsyfet = 'f' ,            /* =C'f' SYMBOLIC NAME FETCH VARIABLE     @V6MUBR0 */
   shvsyset = 's' ,            /* =C's' SYMBOLIC NAME SET VARIABLE       @V6MUBR0 */
   shvsydro = 'd' ,            /* =C'd' SYMBOLIC NAME DROP VARIABLE      @V6MUBR0 */
   shvnextv = 'N',             /* fetch 'NEXT' VARIABLE            @V6GMAL1 */
   shvpriv = 'P',              /* fetch private information        @v6gmal1 */
   shvclean = 0x00,            /* EXECUTION WAS OK                 @V6GMAL1 */
   shvnewv = 0x01,             /* VARIABLE DID NOT EXIST           @V6GMAL1 */
   shvlvar = 0x02,             /* LAST VARIABLE TRANSFERRED (FOR N)@V6GMAL1 */
   shvtrunc = 0x04,            /* TRUNCATION OCCURRED FOR 'FETCH'  @V6GMAL1 */
   shvbadn = 0x08,             /* INVALID VARIABLE NAME            @V6GMAL1 */
   shvbadv = 0x10,             /* INVALID VARIABLE VALUE, e.g. too @V6GMAL1 */
   shvbadf = 0x80,             /* INVALID FUNCTION CODE (SHVCODE)  @V6GMAL1 */
};
#endif
