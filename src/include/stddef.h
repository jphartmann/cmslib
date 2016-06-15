/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stddef.h - assert header file.                                   */
/*                                                                   */
/*********************************************************************/

#ifndef __STDDEF_INCLUDED
#define __STDDEF_INCLUDED

typedef long ptrdiff_t;
typedef unsigned long time_t;
#ifndef __SIZE_T_DEFINED
#define __SIZE_T_DEFINED
typedef unsigned long size_t;
typedef signed long ssize_t;
#endif
#ifndef __WCHAR_T_DEFINED
#define __WCHAR_T_DEFINED
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#endif
typedef char wchar_t;
#endif

#define NULL ((void *)0)
#define offsetof(x, y) (size_t)&(((x *)0)->y)

#ifdef __PDPCLIB_DLL
#define __PDPCLIB_API__ __declspec(dllexport)
#define __MAIN_FP__
#else
#define __PDPCLIB_API__
#endif

#if defined(__ZVM__)
   #define __MVSCMS__ 0
#elif defined(__MVS__) || defined(__CMS__)
   #define __MVSCMS__ 1
#else
   #define __MVSCMS__ 0
#endif


#endif
