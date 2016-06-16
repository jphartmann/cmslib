/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  string.c - implementation of routines in string.h                */
/*                                                                   */
/* Change activity:                                                  */
/*17 Jun 2011  +++ Fix strerror.                                     */
/*********************************************************************/

#include "stdio.h"
#include "string.h"
#include "stddef.h"
#define _BSD_SOURCE
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

/* Forward declarations:                                             */
static int strxcasecmp(const char *s1s, const char *s2s, const int anycase,
   const size_t mlen);
/* End of forward declarations.                                      */

#ifdef strcpy
#undef strcpy
#endif
__PDPCLIB_API__ char *strcpy(char *s1, const char *s2)
{
    char *p = s1;

    while ((*p++ = *s2++) != '\0') ;
    return (s1);
}

#ifdef strncpy
#undef strncpy
#endif
__PDPCLIB_API__ char *strncpy(char *s1, const char *s2, size_t n)
{
    char *p = s1;
    size_t x;

    for (x=0; x < n; x++)
    {
        *p = *s2;
        if (*s2 == '\0') break;
        p++;
        s2++;
    }
    for (; x < n; x++)
    {
        *p++ = '\0';
    }
    return (s1);
}

#ifdef strcat
#undef strcat
#endif
__PDPCLIB_API__ char *strcat(char *s1, const char *s2)
{
    char *p = s1;

    while (*p != '\0') p++;
    while ((*p = *s2) != '\0')
    {
        p++;
        s2++;
    }
    return (s1);
}

#ifdef strncat
#undef strncat
#endif
__PDPCLIB_API__ char *strncat(char *s1, const char *s2, size_t n)
{
    char *p = s1;
    size_t x = 0;

    while (*p != '\0') p++;
    while ((*s2 != '\0') && (x < n))
    {
        *p = *s2;
        p++;
        s2++;
        x++;
    }
    *p = '\0';
    return (s1);
}

#ifdef strcmp
#undef strcmp
#endif
__PDPCLIB_API__ int strcmp(const char *s1, const char *s2)
{
    const unsigned char *p1;
    const unsigned char *p2;

    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    while (*p1 != '\0')
    {
        if (*p1 < *p2) return (-1);
        else if (*p1 > *p2) return (1);
        p1++;
        p2++;
    }
    if (*p2 == '\0') return (0);
    else return (-1);
}

__PDPCLIB_API__ int strcasecmp(const char *s1, const char *s2)
{
   return strxcasecmp(s1, s2, 1, SSIZE_MAX);
}

__PDPCLIB_API__ int strncasecmp(const char *s1, const char *s2, size_t n)
{
   return strxcasecmp(s1, s2, 1, n);
}

static int
strxcasecmp(const char *s1s, const char *s2s, const int anycase,
   const size_t mlen)
{
   const void * v1 = s1s;
   const void * v2 = s2s;
   const unsigned char * p1 = v1;
   const unsigned char * p2 = v2;
   size_t ix = 0;

    while (ix < mlen)
    {
        unsigned char c1 = p1[ix];
        unsigned char c2 = p2[ix];

        if (anycase)
        {
           c1 = toupper(c1);
           c2 = toupper(c2);
        }

        if (c1 < c2) return (-1);
        if (c1 > c2) return (1);
        if (!c1) return 0;
        ix++;
    }
    return 0;
}

#ifdef strcoll
#undef strcoll
#endif
__PDPCLIB_API__ int strcoll(const char *s1, const char *s2)
{
    return (strcmp(s1, s2));
}

#ifdef strncmp
#undef strncmp
#endif
__PDPCLIB_API__ int strncmp(const char *s1, const char *s2, size_t n)
{
    const unsigned char *p1;
    const unsigned char *p2;
    size_t x = 0;

    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    while (x < n)
    {
        if (p1[x] < p2[x]) return (-1);
        else if (p1[x] > p2[x]) return (1);
        else if (p1[x] == '\0') return (0);
        x++;
    }
    return (0);
}

#ifdef strxfrm
#undef strxfrm
#endif
__PDPCLIB_API__ size_t strxfrm(char *s1, const char *s2, size_t n)
{
    size_t oldlen;

    oldlen = strlen(s2);
    if (oldlen < n)
    {
        memcpy(s1, s2, oldlen);
        s1[oldlen] = '\0';
    }
    return (oldlen);
}

#ifdef strchr
#undef strchr
#endif
__PDPCLIB_API__ char *strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c) return ((char *)s);
        s++;
    }
    if (c == '\0') return ((char *)s);
    return (NULL);
}

#ifdef strcspn
#undef strcspn
#endif
__PDPCLIB_API__ size_t strcspn(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;

    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) return ((size_t)(p1 - s1));
            p2++;
        }
        p1++;
    }
    return ((size_t)(p1 - s1));
}

#ifdef strpbrk
#undef strpbrk
#endif
__PDPCLIB_API__ char *strpbrk(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;

    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) return ((char *)p1);
            p2++;
        }
        p1++;
    }
    return (NULL);
}

#ifdef strrchr
#undef strrchr
#endif
__PDPCLIB_API__ char *strrchr(const char *s, int c)
{
    const char *p;

    p = s + strlen(s);
    while (p >= s)
    {
        if (*p == (char)c) return ((char *)p);
        p--;
    }
    return (NULL);
}

#ifdef strspn
#undef strspn
#endif
__PDPCLIB_API__ size_t strspn(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;

    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) break;
            p2++;
        }
        if (*p2 == '\0') return ((size_t)(p1 - s1));
        p1++;
    }
    return ((size_t)(p1 - s1));
}


/* strstr by Frank Adam */
/* modified by Paul Edwards */

#ifdef strstr
#undef strstr
#endif
__PDPCLIB_API__ char *strstr(const char *s1, const char *s2)
{
    const char *p = s1, *p1, *p2 = s2;

    while (*p)
    {
        if (*p == *s2)
        {
            p1 = p;
            p2 = s2;
            while ((*p2 != '\0') && (*p1 == *p2))
            {
                p1++;
                p2++;
            }
            if (*p2 == '\0')
            {
                return (char *)p;
            }
        }
        p++;
    }
    return NULL;
}

#ifdef strtok
#undef strtok
#endif
__PDPCLIB_API__ char *strtok(char *s1, const char *s2)
{
    static char *old = NULL;
    char *p;
    size_t len;
    size_t remain;

    if (s1 != NULL) old = s1;
    if (old == NULL) return (NULL);
    p = old;
    len = strspn(p, s2);
    remain = strlen(p);
    if (remain <= len) { old = NULL; return (NULL); }
    p += len;
    len = strcspn(p, s2);
    remain = strlen(p);
    if (remain <= len) { old = NULL; return (p); }
    *(p + len) = '\0';
    old = p + len + 1;
    return (p);
}

#ifdef strlen
#undef strlen
#endif
__PDPCLIB_API__ size_t strlen(const char *s)
{
    const char *p;

    p = s;
    while (*p != '\0') p++;
    return ((size_t)(p - s));
}

char *
strdup(const char * s)
{
   char * t=malloc(strlen(s)+1);
   if (t) strcpy(t, s);
   return t;
}
