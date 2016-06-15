/* Header file used by flex to include stdint.                       */
/*                                John Hartmann 13 Jun 2016 12:10:30 */

/*********************************************************************/
/* Change activity:                                                  */
/*13 Jun 2016  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_INTTYPES_H)
#define _JPH_INTTYPES_H

#include <stdint.h>

typedef   signed char int8_t;
typedef unsigned char uint8_t;
typedef   signed short int16_t;
typedef unsigned short uint16_t;
typedef   signed int   int32_t;
typedef unsigned int  uint32_t;
typedef   signed long long  int64_t;
typedef unsigned long long uint64_t;

#endif
