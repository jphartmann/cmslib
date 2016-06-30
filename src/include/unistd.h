/* Low level unix interface                                          */
/*                                John Hartmann 11 Jun 2011 15:48:04 */

/*********************************************************************/
/* Change activity:                                                  */
/*11 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_UNISTD_H)
   #define _JPH_UNISTD_H

#include <stddef.h>
#include <sys/types.h>

extern int close (int filedes);

/* Read  a  record into the buffer in the file; or set the buffer in */
/* the file from the underlying interface.                           */

extern off_t lseek(int fd, off_t offset, int whence);
#if !defined(SEEK_SET)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

extern ssize_t read (int filedes, void *buffer, ssize_t size);
extern ssize_t write(int filedes, const void *buffer, ssize_t size);

#endif
