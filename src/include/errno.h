/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  errno.h - errno header file.                                     */
/*                                                                   */
/*********************************************************************/

#ifndef __ERRNO_INCLUDED
#define __ERRNO_INCLUDED

enum
{
   #define __ERRNO(x, y) x,
   #include <errnos.h>
   #undef __ERRNO
   __errno_count
};

#if defined(__ZVM__)
   #include <cmsthreadglobal.h>
   #define errno (__getgbl()->errno)
#else
   extern int errno;
#endif

#if defined(_BSD_SOURCE)
extern const char *sys_errlist[];
extern const int sys_nerr;
#endif

#endif
