/* LINERD macro and stuff                                            */
/*                                 John Hartmann 3 Oct 2011 17:12:50 */

/*********************************************************************/
/* Change activity:                                                  */
/* 3 Oct 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_LINERD_H)
   #define _JPH_LINERD_H

#include <cmsbase.h>

struct linerd
{
   char verb[8];
   unsigned char * bfr;
   int length;
   char * vscreen;
   int line;
   int column;
   char * prompt;
   int promptlength;
   unsigned char flag1;               /* b'11001110'                 */
   unsigned char flag2;               /* b'01000000'                 */
   unsigned char reserved[2];
   void * numrd1;
   void * numrd2;
   unsigned char fence[8];
};

#define linerd_stack(a, b, c) __consrd(a, b, 0xce, 0xc0, c)
#define linerd_nostack(a, b, c) __consrd(a, b, 0xc6, 0xc0, c)
#define linerd_direct(a, b, c) __consrd(a, b, 0xe6, 0xc0, c)
#define linerd_invisible(a, b, c) __consrd(a, b, 0xd6, 0xc0, c)

#endif
