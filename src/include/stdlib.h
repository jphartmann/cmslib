/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stdlib.h - stdlib header file                                    */
/*                                                                   */
/*********************************************************************/

#ifndef __STDLIB_INCLUDED
#define __STDLIB_INCLUDED

#include <stddef.h>

typedef struct { int quot; int rem; } div_t;
typedef struct { long int quot; long int rem; } ldiv_t;

#define EXIT_SUCCESS 0
#if defined(__MVS__) || defined(__CMS__) || defined(__VSE__)
#define EXIT_FAILURE 12
#else
#define EXIT_FAILURE 1
#endif
#define RAND_MAX 32767
#define MB_CUR_MAX 1

#if defined(__ZVM__)
   #include <cmsbase.h>
   #include <cmsthreadglobal.h>
   #define __NATEXIT (__getgbl()->atexitcount)
   #define __userExit (__getgbl()->userExit)
#else
   extern void (*__userExit[__NATEXIT])(void);
   #define __NATEXIT 32
#endif


void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
#if defined(__MVS__) || defined(__CMS__) || defined(__VSE__)
void abort(void) __attribute__((noreturn));
#else
void abort(void);
#endif
void exit(int status);
void qsort(void *, size_t, size_t,
                           int (*)(const void *, const void *));
void srand(unsigned int seed);
int rand(void);
#define atof(nptr) strtod(nptr, (char **) 0)
double strtod(const char *nptr, char **endptr);
int atoi(const char *nptr);
#define atol(nptr) strtol(nptr, (char **) 0, 10)
long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);
int mblen(const char *s, size_t n);
int mbtowc(wchar_t *pwc, const char *s, size_t n);
int wctomb(char *s, wchar_t wchar);
size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n);
size_t wcstombs(char *s, const wchar_t *pwcs, size_t n);
#define abs(x) (0 > x ? -x : x)
#define labs(x) (0 > x ? -x : x)
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
int atexit(void (*func)(void));
char *getenv(const char *name);
#if defined(__ZVM__)
   extern char ** environ;
#endif
int system(const char *string);
void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));

#ifdef __WATCOMC__
#pragma intrinsic (abs,labs,div,ldiv)
#endif

#ifdef __IBMC__
int _Builtin __abs(int j);
#define abs(j) (__abs((j)))
long int _Builtin __labs(long int j);
#define labs(j) (__labs((j)))
#endif

#endif
