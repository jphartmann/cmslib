/*                                                                   */
/*                                 John Hartmann 8 Jun 2011 09:46:50 */

/*********************************************************************/
/* Change activity:                                                  */
/* 8 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_TYPES_H)
   #define _JPH_TYPES_H

#define      S_IFMT     0170000 /* bit mask for the file type bit fields */
#define      S_IFSOCK   0140000       /* socket                      */
#define      S_IFLNK    0120000       /* symbolic link               */
#define      S_IFREG    0100000       /* regular file                */
#define      S_IFBLK    0060000       /* block device                */
#define      S_IFDIR    0040000       /* directory                   */
#define      S_IFCHR    0020000       /* character device            */
#define      S_IFIFO    0010000       /* FIFO                        */
#define      S_ISUID    0004000       /* set UID bit                 */
#define      S_ISGID    0002000      /* set-group-ID bit (see below) */
#define      S_ISVTX    0001000       /* sticky bit (see below)      */
#define      S_IRWXU    00700     /* mask for file owner permissions */
#define      S_IRUSR    00400         /* owner has read permission   */
#define      S_IWUSR    00200         /* owner has write permission  */
#define      S_IXUSR    00100        /* owner has execute permission */
#define      S_IRWXG    00070         /* mask for group permissions  */
#define      S_IRGRP    00040         /* group has read permission   */
#define      S_IWGRP    00020         /* group has write permission  */
#define      S_IXGRP    00010        /* group has execute permission */
#define      S_IRWXO    00007 /* mask for permissions for others (not in group) */
#define      S_IROTH    00004         /* others have read permission */
#define      S_IWOTH    00002        /* others have write permission */
#define      S_IXOTH    00001      /* others have execute permission */

typedef unsigned long dev_t;
typedef unsigned long ino_t;
typedef unsigned long mode_t;
typedef unsigned long nlink_t;
typedef unsigned long uid_t;
typedef unsigned long gid_t;
typedef unsigned long off_t;
typedef unsigned long blksize_t;
typedef unsigned long blkcnt_t;
#ifndef __SIZE_T_DEFINED
#define __SIZE_T_DEFINED
typedef unsigned long size_t;
typedef long ssize_t;
#endif
#endif
