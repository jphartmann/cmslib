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
   union
   {
      char * module;
      int integer;
   };
   union
   {
      char * token;
      int endrange;
   };
   struct piperecord string;
   struct piperecord word;
};

struct pipebuffer                     /* pipbfr                      */
{
   int dwds;                       /* Opaque (Doublewords allocated) */
   char * base;                       /* Where it is                 */
   int size;                          /* Current size in bytes       */
   char * next;                       /* Next available position     */
};

typedef int (* fplstage)(struct pipeanchor * panc, struct pipeparms * args);

/* Printf                                                            */
extern int fplgccpf(struct pipeanchor * panc, int subs, void * slist);

extern int fplgccvt(struct pipeanchor * panc, int service);
/* Operations on a record                                            */
extern int fplgccrc(struct pipeanchor * panc, int service, struct piperecord * rec);
enum __record_function
{
   __dsp_locate,
   __dsp_input,
   __dsp_output,
   __dsp_command,
   __dsp_rexx,
};
#define piplocate(anc, rec) fplgccrc(anc, __dsp_locate, rec)
#define pipinput(anc, rec)  fplgccrc(anc, __dsp_input, rec)
#define pipoutput(anc, rec) fplgccrc(anc, __dsp_output, rec)
#define pipcmd(anc, cmd)    fplgccrc(anc, __dsp_output, cmd)
#define piprexx(anc, cmd)    fplgccrc(anc, __dsp_rexx, cmd)

/* Dispatcher functions that take nothing, an integer or, a pair     */
extern int fplgccdi(struct pipeanchor * panc, int service, int i, int j);

enum __integer_function
{
   __dsp_parm,
   __dsp_short,
   __dsp_commit,
   __dsp_select,
};
#define pipparm(anc)                      fplgccdi(anc, __dsp_parm, 0, 0)
#define pipshort(anc)                     fplgccdi(anc, __dsp_short, 0, 0)
#define pipcommit(anc, n)                 fplgccdi(anc, __dsp_commit, n, 0)
#define pipselect(anc, parm, dir, stream) fplgccdi(anc, __dsp_select, dir, stream)
   #define SELECTINPUTSIDE -1
   #define SELECTOUTPUTSIDE -2
   #define SELECTBOTHSIDES -3
   #define SELECTANYINPUT -4

/* Operate on hidden buffer                                          */
extern int fplgccbf(struct pipeanchor * panc, int service, void * data, int length);
enum __buffer_function
{
   __pipbfr_reset,                    /* Reset buffer to be empty    */
   __pipbfr_extend,          /* Ensure at least size bytes available */
   __pipbfr_load,                     /* Load data                   */
   __pipbfr_append,                   /* Append data                 */
   __pipbfr_pad,                      /* Pad bytes                   */
   __pipbfr_setup,            /* Set parm 4 and 5 to buffer contents */
   __pipbfr_write,      /* Write buffer contents to output and reset */
};

#define pipbfrreset(anc)  fplgccbf(anc, __pipbfr_reset, 0, 0)
#define pipbfrextend(anc, size)  fplgccbf(anc, __pipbfr_extend, 0, size)
#define pipbfrload(anc, data, size)  fplgccbf(anc, __pipbfr_load, data, size)
#define pipbfrappend(anc, data, size)  fplgccbf(anc, __pipbfr_append, data, size)
#define pipbfrpad(anc, pad, size)  fplgccbf(anc, __pipbfr_pad, (int *) -pad, size)
#define pipbfrsetup(anc)  fplgccbf(anc, __pipbfr_setup, 0, 0)
#define pipbfrwrite(anc)  fplgccbf(anc, __pipbfr_write, 0, 0)

/* DSPPA EQU 0*4 parm                                                */
/* DSPSL EQU 1*4 sel                                                 */
/* When R0 is negative, R1 is the stream number of stream identifier */
/* of  the stream to select; otherwise R0 is the stream to select on */
/* both sides.                                                       */
/* DSPLO EQU 2*4 locat                                               */
/* DSPPI EQU 3*4 input                                               */
/* DSPPO EQU 4*4 outp                                                */
/* DSPSH EQU 5*4 short                                               */
/* DSPCM EQU 6*4 cmd                                                 */
/* REXX EQU 7*4  rexx                                                */
/* MSGEP EQU 8*4 msg                                                 */
#define piperm(anc)    fplgccvt(anc, 8, (union fplparm) prm, 0)
/* CVTTK EQU 9*4                                                     */
#define piptstkw(anc) fplgccvt(anc, 09)
/* CVTNP EQU 10*4                                                    */
#define pipnupl(anc) fplgccvt(anc, 10)
/* CVTGW EQU 11*4                                                    */
#define pipword(anc) fplgccvt(anc, 11)
/* CVTGD EQU 12*4                                                    */
#define pipdwrd(anc) fplgccvt(anc, 12)
/* CVTST EQU 13*4                                                    */
#define piputkn(anc) fplgccvt(anc, 13)
/* CVTMT EQU 14*4                                                    */
#define pipmtkn(anc) fplgccvt(anc, 14)
/* CVTSD EQU 15*4                                                    */
#define pipsdel(anc) fplgccvt(anc, 15)
/* CVTHW EQU 16*4                                                    */
#define pipxwrd(anc) fplgccvt(anc, 16)
/* CVTXC EQU 17*4                                                    */
#define pipxchr(anc) fplgccvt(anc, 17)
/* CVTXR EQU 18*4                                                    */
#define pipxrng(anc) fplgccvt(anc, 18)
/* CVTBX EQU 19*4                                                    */
#define pipbhex(anc) fplgccvt(anc, 19)
/* CVTSB EQU 20*4                                                    */
#define pipstrlb(anc) fplgccvt(anc, 20)
/* CVTDR EQU 21*4                                                    */
#define pipdrang(anc) fplgccvt(anc, 21)
/* CVTDW EQU 22*4                                                    */
#define pipdecwd(anc) fplgccvt(anc, 22)
/* CVTCV EQU 23*4                                                    */
#define pipckvc(anc) fplgccvt(anc, 23)
/* CVTTS EQU 24*4                                                    */
#define piptstar(anc) fplgccvt(anc, 24)
/* CVTSX EQU 25*4                                                    */
#define pipsxtab(anc) fplgccvt(anc, 25)
/* BUFXD EQU 26*4  extend buffer without message                     */
/* CVTGM EQU 27*4                                                    */
#define pipgendm(anc) fplgccvt(anc, 27)
/* DSPSN EQU 28*4                                                    */
/* DSPX EQU 29*4                                                     */
/* BUFAP EQU 30*4                                                    */
/* BUFFR EQU 31*4                                                    */
/* BUFFT EQU 32*4                                                    */
/* DSPWE EQU 33*4                                                    */
/* XLATU EQU 34*4                                                    */
/* CVTTB EQU 35*4                                                    */
#define pipstrtb(anc) fplgccvt(anc, 35)
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
/* CVTFS EQU 55*4 hex float to string                                */
/* CVTSF EQU 56*4 string to hex float                                */
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
/* DSPSA EQU 69*4                                                    */

#endif
