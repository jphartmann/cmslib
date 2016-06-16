/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  errno.c - implementation of stuff in errno.h                     */
/*                                                                   */
/* Change activity:                                                  */
/*17 Jun 2011  jph Added error strings.                              */
/*********************************************************************/

#define _BSD_SOURCE
#include <errno.h>
#include <string.h>
#include <stddef.h>

#if !defined(__ZVM__)
   int errno;
#endif

const int sys_nerr=__errno_count;
const char *sys_errlist[__errno_count + 1]=
{
   #define __ERRNO(x, y) y,
   #include <errnos.h>
   #undef __ERRNO
};

#ifdef strerror
#undef strerror
#endif
__PDPCLIB_API__ const char *strerror(int errnum)
{
    if (0 <= errnum && sys_nerr >= errnum )
      return sys_errlist[errnum];
    return ("Unknown error nnn");
}
