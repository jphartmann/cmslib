/* Diagnose instructions                                             */
/*                                John Hartmann 30 Jun 2011 10:04:57 */

/*********************************************************************/
/* Change activity:                                                  */
/*30 Jun 2011  New header file.                                      */
/*********************************************************************/

#include <cmsbase.h>

#if !defined(_JPH_DIAGNOSE_H)

/*********************************************************************/
/* 000 - Store extended identification.                              */
/*********************************************************************/

struct diag000
{
   union
   {
      char sysname[8];
      double align;
   };
   unsigned short environment;        /* 8000 in lpar 0400 64-bit    */
   unsigned char version;
   unsigned char version_code;        /* From CPUID                  */
   unsigned char reserved[2];
   unsigned short ap;                 /* Processor address           */
   unsigned char userid[8];           /* User ID                     */
   unsigned char lppmap[8];           /* Licensed program map        */
   int timezoneoffset;
   unsigned char release;
   unsigned char modification;
   unsigned short service;
};

/* Return  actual length stored.  The buffer is an array of diag000s */
/* for each level of cp we are under.                                */

extern int _diag000(struct diag000 * buffer, int length);

/*********************************************************************/
/* Diagnose 00C pseudo timer                                         */
/*                                                                   */
/* If  the  second  argument is nonzero, the micro second values are */
/* converted to time values.                                         */
/*********************************************************************/

struct diag00c
{
   union
   {
      char date[8];
      double align;
   };
   char time[8];
   union
   {
      unsigned long long usec;
      struct timeval tv;
   } virtcpu;
   union
   {
      unsigned long long usec;
      struct timeval tv;
   }
   totcpu;
};

extern void _diag00c(struct diag00c * buffer, int dotv);


   #define _JPH_DIAGNOSE_H
#endif
