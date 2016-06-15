/* CMSSTACK function                                                 */
/*                                 John Hartmann 3 Oct 2011 17:52:01 */

/*********************************************************************/
/* Change activity:                                                  */
/* 3 Oct 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_CMSSTACK_H)
   #define _JPH_CMSSTACK_H

struct cmsstack
{
   char verb[8];
   char how[4];                       /* LIFO or FIFO                */
   int length;
   unsigned char * bfr;
   unsigned char fence[8];
};

#endif
