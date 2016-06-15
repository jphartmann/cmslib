/* FILE for CMS.  The stuff in stdio.h is just too much.             */
/*                                John Hartmann 20 Jan 2015 12:29:51 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jan 2015  New header file.                                      */
/*********************************************************************/

#if !defined(_JPH_CMSFILE_H)
#define _JPH_CMSFILE_H

#include <stddef.h>
#include <cmsbase.h>
#include <cmsthreadglobal.h>

struct __file;
struct stat;

/*********************************************************************/
/* File backend routines are selected by this enum.                  */
/*********************************************************************/

enum __ftype
{
   _f_unknown,
   _f_term,
   _f_pipe,
   _f_sfs,
};

struct __access
{
   char type[8];                      /* For indification            */
   int (* open) (struct __file * f, const char * name, int oflags, const char * mode);
   ssize_t (* read) (struct __file * f);          /* Supply a record */
   ssize_t (* write) (struct __file * f);    /* Flush buffer to file */
   /* Grow buffer for write.  Number of bytes we want to add.        */
   int (* extend) (struct __file * f, const size_t add);
   int (* flush) (struct __file * f);          /* Maybe write partial         */
   int (* close) (struct __file * f);          /* Done                        */
   int (* fstat) (struct __file * f, struct stat * s);
};

/*********************************************************************/
/* The ubiquous stream argument of the standard I/O library.         */
/*********************************************************************/

typedef struct __file
{
   char ckwd[4];                      /* = "file"                    */
   #define __FILECKWD "file"
   const struct __access * pac;       /* File type specific stuff    */
   void * accwork;    /* File type specific work area/parameter list */
   union
   {
      unsigned char token[8];         /* SFS open file token         */
      struct                          /* OS/j inode id               */
      {
         int diskix;
         int inode;
      };
   };
   int fd;                            /* File descriptor number      */
   enum __ftype ftype;
   int oflags;                        /* Open flags                  */
   int blksize;                       /* = 4K for CMS                */
   int lrecl;
   size_t numrecs;
   union
   {
      size_t numblks;
      size_t i_size;                  /* File size                   */
   };
   unsigned int i_mode;            /* OS/j ext2 file mode; 0 for CMS */

   unsigned char * buffer;
   /* Number of bytes allocated to buffer on output; number of bytes */
   /* in input record on read                                        */
   size_t buffersize;                 /* Number of bytes allocated   */
   size_t hiwater;    /* Buffer size on output; record size on input */
   size_t byteptr;                  /* Offset to next for read/write */

   int sfsrc;                         /* last return code            */
   int sfsreason;                     /* and reason code             */
   /* There  is  only  one offset for a file, even though there is a */
   /* read and a write pointer for a file descriptor.                */
   size_t offset;                     /* Byte offset                 */
   size_t readpointer;                /* Record number for read      */
   size_t writepointer;               /* Record number for write     */
   int ungetCh;                 /* character pushed back, -1 if none */
   char recform;                      /* 'F' or 'V'                  */
   unsigned int eofInd: 1;
   unsigned int errorInd: 1;
   unsigned int isopen: 1;
   unsigned int stdfile: 1;       /* stdin .. stderr, never released */
} FILE;

struct stat;

extern int _allocbuf(struct __file * f, int size);
extern int _devextend(struct __file * f, int nusize);
extern int _getafd(void);
extern void _initafile(int fd, FILE * f);
extern struct __file * _getafile(int fd);
extern int _openfile (struct __file * f, const char * name, int oflags, const char * ostr);
extern void _fileclean(struct __file * f);
extern int __onOSj(void);

#define fileno(f) ((f)->fd)
#define __userFiles (__getgbl()->userFiles)
#define __NFILE (__getgbl()->numfds)

#define stdin (__getgbl()->prealloc[0])
#define stdout (__getgbl()->prealloc[1])
#define stderr (__getgbl()->prealloc[2])

extern FILE * popen(const char * cmd, const char * type);
extern int pclose(FILE * f);
extern void __opnstd(struct _cmsthreadglobal * gbl);

#endif
