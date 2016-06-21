/* Interface to FPLPOP subroutines.                                  */
/*                               John Hartmann  31 Jul 2002 19:49:40 */

/*********************************************************************/
/*                   (c) Copyright IBM Corp 2002.                    */
/*                       All rights reserved.                        */
/*                                                                   */
/* Change activity:                                                  */
/*31 Jul 2002  New Header file.                                      */
/*********************************************************************/


#if !defined(_JPH_FPLPOPEN_H)
   #define _JPH_FPLPOPEN_H

typedef double fplpopwa[32];

enum fplpopflag
{
   fplpop_read=0,
   fplpop_write=1
};


#if defined(__C370__)

extern int fplpopen(fplpopwa * wa, enum fplpopflag * flag,
   char * pipe, int * pipelen);
extern int fplpclose(fplpopwa * wa);
extern int fplpread(fplpopwa * wa, char ** bfr, int * length);
extern int fplpwrite(fplpopwa * wa, char  * bfr, int * length);

#pragma map (fplpopen, "FPLPOPEN")
#pragma map (fplpclose, "FPLPCLOS")
#pragma map (fplpread, "FPLPREAD")
#pragma map (fplpwrite, "FPLPWRIT")

#pragma linkage (fplpopen, OS)
#pragma linkage (fplpclose, OS)
#pragma linkage (fplpread, OS)
#pragma linkage (fplpwrite, OS)

#else

extern int fplpopen(void);
extern int fplpclos(void);
extern int fplpread(void);
extern int fplpwrit(void);

#define _popen(wa, flg, bfr, len) oscall(fplpopen, 4, wa, flg, bfr, len)
#define _pclose(wa) oscall(fplpclos, 1, wa)
#define _pread( wa, bfr, length) oscall(fplpread, 3, wa, bfr, length)
#define _pwrite( wa, bfr, length) oscall(fplpwrit, 3, wa, bfr, length)

#endif

#endif
