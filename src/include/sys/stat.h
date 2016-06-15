/* File information.                                                 */
/*                                 John Hartmann 8 Jun 2011 09:50:36 */

/*********************************************************************/
/* This file is put in the public domain.                            */
/*                                                                   */
/* Change activity:                                                  */
/* 8 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_STAT_H)
   #define _JPH_STAT_H

/* For the time_t type                                               */
#include <time.h>
#include <sys/types.h>

struct stat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for file system I/O */
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    time_t    st_atime;   /* time of last access */
    time_t    st_mtime;   /* time of last modification */
    time_t    st_ctime;   /* time of last status change */
};

#define  S_ISREG(m)  (S_IFREG == (S_IFMT & m)) /* is it a regular file? */
#define  S_ISDIR(m)  (S_IFDIR == (S_IFMT & m))         /* directory? */
#define  S_ISCHR(m)  (S_IFCHR == (S_IFMT & m))  /* character device? */
#define  S_ISBLK(m)  (S_IFBLK == (S_IFMT & m))      /* block device? */
#define  S_ISFIFO(m) (S_IFIFO == (S_IFMT & m)) /* FIFO (named pipe)? */
#define  S_ISLNK(m)  (S_IFLNK == (S_IFMT & m)) /* symbolic link? (Not in POSIX.1-1996.) */
#define  S_ISSOCK(m) (S_IFSOCK == (S_IFMT & m)) /* socket? (Not in POSIX.1-1996.) */


int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);

#endif
