/*                                                                   */
/*                                John Hartmann 30 Jun 2011 08:36:51 */

/*********************************************************************/
/* Change activity:                                                  */
/*30 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_LIMITS_H)
   #define _JPH_LIMITS_H

/* Minimum and maximum values a `signed short int' can hold.  */
#  define SHRT_MIN      (-32768)
#  define SHRT_MAX      32767

/* Maximum value an `unsigned short int' can hold.  (Minimum is 0.)  */
#  define USHRT_MAX     65535

/* Minimum and maximum values a `signed int' can hold.  */
#  define INT_MIN       (-INT_MAX - 1)
#  define INT_MAX       2147483647

/* Maximum value an `unsigned int' can hold.  (Minimum is 0.)  */
#  define UINT_MAX      4294967295U
#  define ULONG_MAX     UINT_MAX
#  define LONG_MAX      INT_MAX
#  define SSIZE_MAX     INT_MAX

#define PATH_MAX 256

#endif
