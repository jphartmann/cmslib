/* Low level unix interface                                          */
/*                                John Hartmann 11 Jun 2011 15:48:04 */

/*********************************************************************/
/* Change activity:                                                  */
/*11 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_UNISTD_H)
   #define _JPH_UNISTD_H

#include <stddef.h>

extern int close (int filedes);

/* Read  a  record into the buffer in the file; or set the buffer in */
/* the file from the underlying interface.                           */

extern ssize_t read (int filedes, void *buffer, ssize_t size);
extern ssize_t write(int filedes, const void *buffer, ssize_t size);

#endif
