/* Basic CMS building blocks                                         */
/*                                John Hartmann 16 Jun 2011 13:40:22 */

/*********************************************************************/
/* Change activity:                                                  */
/*16 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_CMSBASE_H)
   #define _JPH_CMSBASE_H

#include <eplist.h>
#include <sys/time.h>

#if !defined(_CMSNOMAIN)
extern int cmsmain(struct eplist * epl, char (* pl)[8]);
#endif

/*********************************************************************/
/* Macros defining runtime flags.                                    */
/*********************************************************************/

#define GCC390_STACK_SIZE(x) int __CMSSTK = x
#define GCC390_NO_ENVIRON    int __CMSNOENV = 1

/*********************************************************************/
/* Assembler support stuff:                                          */
/*********************************************************************/

/* return to CMS.                                                    */
extern void __exit(int rv) __attribute__((noreturn));
/* return the address of the current stack frame                     */
extern struct gccstack * __stktop(void);
/* get heap storage in our subpool                                   */
extern struct __heap * __gethp(unsigned bytes);
/* return heap storage in our subpool                                */
extern int __freehp(unsigned bytes, void * addr);
/* Issue svc 204                                                     */
extern int __svc204(struct eplist * epl, char * olplist,
   unsigned flags, int * regfb);
/* Display a string                                                  */
extern int __say(const char * msg, unsigned length);
#define __says __say
extern int __says(const char * msg, unsigned length);
/* Change PSW key; return previous key.                              */
extern int __pswkey(int key);
/* Get tod with uS precision                                         */
extern void __timev(struct timeval * tv);
/* Call  a  callable service.  Count is count of parameters less the */
/* service name.                                                     */
extern int __csl(const void * plist);
extern int __oscall(int (* f)(void), const void * plist);
/* Call adtlkp.  See printblk sampasm on the CMS source disk         */
struct adt;
extern struct adt * __adtlkp(unsigned char * mode);

/* Diagnose codes are in diagnose.h                                  */


/*********************************************************************/
/* Supporting C code                                                 */
/*********************************************************************/

extern void * __getm(unsigned size);
extern void __freem(void * p);
extern void __dump(const void * s, int bytes);
extern int __sayf(const char * format, ...)
   __attribute__ ((format (printf, 1, 2)));

#define FENCE {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
#define FENCESTR "\xff\xff\xff\xff\xff\xff\xff\xff"

#define __WERROR(x, ...) __sayf(__FILE__ "(%d):  " x, __LINE__, ## __VA_ARGS__)

/*********************************************************************/
/* In cms.c:                                                         */
#if 0
  LINERD  DATA=((2),(3)),WAIT=YES,CASE=MIXED,TYPE=STACK
    DC    B'11001110' 01 on is case=upper
    DC    B'11000000' 80 on is wait=yes
  LINERD  DATA=((2),(3)),WAIT=YES,CASE=MIXED,TYPE=NOSTACK
    DC    B'11000110'
    DC    B'11000000'
  LINERD  DATA=((2),(3)),WAIT=YES,CASE=MIXED,TYPE=DIRECT
    DC    B'11100110'
    DC    B'11000000'
  LINERD  DATA=((2),(3)),WAIT=YES,CASE=MIXED,TYPE=INVISIBLE
    DC    B'11010110'
    DC    B'11000000'
#endif
/*********************************************************************/

extern int __consrd(void * bfr, int len,
   unsigned char flag1, unsigned char flag2, int * regfb);

extern void __traceb(void);


#endif
