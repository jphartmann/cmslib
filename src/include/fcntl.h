/* File control                                                      */
/*                                 John Hartmann 3 Jul 2011 06:04:18 */

/*********************************************************************/
/* Change activity:                                                  */
/* 3 Jul 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_FCNTRL_H)
   #define _JPH_FCNTRL_H

extern int open (const char *filename, int flags, ...);

#define O_RDONLY    0x0001
#define O_WRONLY    0x0002
#define O_RDWR      0x0004
#define O_CREAT     0x0010
#define O_TRUNC     0x0020
#define O_APPEND    0x0040
#define O_EXCL      0x0080
#define O_SHLOCK    0x0100
#define O_EXLOCK    0x0200
/* The mode parameter to open is additional fopen mode string stuff. */
#define O_MODESTR   0x1000
#define O_BINARY    0x2000

#endif
