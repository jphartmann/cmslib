/* Interface to CMS/TSO Pipelines                                    */
/*                                 John Hartmann 4 May 2014 11:14:19 */

/*********************************************************************/
/* Change activity:                                                  */
/* 4 May 2014  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_CMSPIPE_H)
#define _JPH_CMSPIPE_H

struct pipeanchor;                    /* Opaque type                 */

struct piperecord                     /* #record macro               */
{
   void * ptr;                        /* Address of buffer (R1)      */
   /* Underlying inteface is 31 bit.                                 */
   int length;                        /* Length in bytes (R0)        */
};

struct pipeparms          /* Regs 0 through 5 in assembler interface */
{
   int integer;
   union
   {
      char * token;
      int endrange;
   };
   struct piperecord string;
   struct piperecord word;
};

typedef int (* fplstage)(struct pipeanchor * panc, struct pipeparms * args);

union fplparm
{
   int number;                        /* If a number                 */
   struct pipeparms * parms;
   struct piperecord * prec;
};
/* Printf                                                            */
extern int fplgccpf(struct pipeanchor * panc, int subs, void * slist);

/* The  second  parameter is the PSTV index for the service routine. */
/* For  calls to fplcvt, the number is used blindly as an index.  If */
/* you  code  additional macros below, you better be sure the called */
/* routine  uses  only  registers  0..5; coz those are the only ones */
/* that will be passed.                                              */

/* The  actual code to call the service routine for fplgccsv must be */
/* added  to  FPLGCC;  you cannot just invent a service by adding it */
/* here.                                                             */

extern int fplgccvt(struct pipeanchor * panc, int service, struct pipeparms * parm);
extern int fplgccsv(struct pipeanchor * panc, int service, union fplparm p1, struct piperecord * rec);

/* DSPPA EQU 0*4 parm                                                */
/* DSPSL EQU 1*4 sel                                                 */
/* DSPLO EQU 2*4 locat                                               */
#define piplocate(anc, rec) fplgccsv(anc, 2, (union fplparm) 0, rec)
/* DSPPI EQU 3*4 input                                               */
#define pipinput(anc, rec)  fplgccsv(anc, 3, (union fplparm) 0, rec)
/* DSPPO EQU 4*4 outp                                                */
#define pipoutput(anc, rec) fplgccsv(anc, 4, (union fplparm) 0, rec)
/* DSPSH EQU 5*4 short                                               */
#define pipshort(anc)       fplgccsv(anc, 4, (union fplparm) 0, NULL)
/* DSPCM EQU 6*4 cmd                                                 */
#define pipcmd(anc, cmd)    fplgccsv(anc, 5, (union fplparm) 0, cmd)
/* REXX EQU 7*4  rexx
/* MSGEP EQU 8*4 msg                                                 */
/* CVTTK EQU 9*4                                                     */
/* CVTNP EQU 10*4                                                    */
/* CVTGW EQU 11*4                                                    */
#define pipword(anc, str) fplgccvt(anc, 11, str)
/* CVTGD EQU 12*4                                                    */
/* CVTST EQU 13*4                                                    */
#define piputkn(anc, str) fplgccvt(anc, 13, str)
/* CVTMT EQU 14*4                                                    */
#define pipmtkn(anc, str) fplgccvt(anc, 14, str)
/* CVTSD EQU 15*4                                                    */
#define pipsdel(anc, str) fplgccvt(anc, 15, str)
/* CVTHW EQU 16*4                                                    */
/* CVTXC EQU 17*4                                                    */
/* CVTXR EQU 18*4                                                    */
/* CVTBX EQU 19*4                                                    */
/* CVTSB EQU 20*4                                                    */
#define pipstrlb(anc, str) fplgccvt(anc, 20, str)
/* CVTDR EQU 21*4                                                    */
#define pipdrang(anc, str) fplgccvt(anc, 21, str)
/* CVTDW EQU 22*4                                                    */
#define pipdecwd(anc, str) fplgccvt(anc, 22, str)
/* CVTCV EQU 23*4                                                    */
/* CVTTS EQU 24*4                                                    */
/* CVTSX EQU 25*4                                                    */
/* BUFXD EQU 26*4                                                    */
/* CVTGM EQU 27*4                                                    */
/* DSPSN EQU 28*4                                                    */
/* DSPX EQU 29*4                                                     */
/* BUFAP EQU 30*4                                                    */
/* BUFFR EQU 31*4                                                    */
/* BUFFT EQU 32*4                                                    */
/* DSPWE EQU 33*4                                                    */
/* XLATU EQU 34*4                                                    */
/* CVTTB EQU 35*4                                                    */
#define pipstrtb(anc, str) fplgccvt(anc, 35, str)
/* ACTTC EQU 37*4                                                    */
/* ACTHV EQU 40*4                                                    */
/* ACTN0 EQU 41*4                                                    */
/* ACTN1 EQU 42*4                                                    */
/* ACTN2 EQU 43*4                                                    */
/* ACTY0 EQU 44*4                                                    */
/* ACTY1 EQU 45*4                                                    */
/* ACTY2 EQU 46*4                                                    */
/* ACTAT EQU 47*4                                                    */
/* ACTCW EQU 48*4                                                    */
/* ACTEA EQU 49*4                                                    */
/* ACTDA EQU 50*4                                                    */
/* ACTQ EQU 51*4                                                     */
/* ACTX EQU 52*4                                                     */
/* BUFXM EQU 53*4                                                    */
/* FNDBS EQU 54*4                                                    */
/* CVTFS EQU 55*4                                                    */
/* CVTSF EQU 56*4                                                    */
/* XLARX EQU 57*4                                                    */
/* $$$PI EQU 58*4                                                    */
/* ACTCS EQU 59*4                                                    */
/* $$$PB EQU 60*4                                                    */
/* $$$PS EQU 61*4                                                    */
/* IUSCE EQU 62*4                                                    */
/* ACTN5 EQU 64*4                                                    */
/* ACTY5 EQU 65*4                                                    */
/* DEFGA EQU 66*4                                                    */
/* DELPC EQU 67*4                                                    */
/* DSPCT EQU 68*4                                                    */
#define pipcommt(anc, n)    fplgccsv(anc, 68, (union fplparm) n, NULL)
/* DSPSA EQU 69*4                                                    */

#endif
