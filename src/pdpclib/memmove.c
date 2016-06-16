/*                                                                   */
/*                                John Hartmann 18 Jun 2011 10:58:10 */

/*********************************************************************/
/* Change activity:                                                  */
/*18 Jun 2011  New module.                                           */
/*********************************************************************/

#include <string.h>
#include <stddef.h>

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

#ifdef memmove
#undef memmove
#endif
__PDPCLIB_API__ void *memmove(void *s1, const void *s2, size_t n)
{
    char *p = s1;
    const char *cs2 = s2;
    size_t x;

    if (p <= cs2)
    {
        for (x=0; x < n; x++)
        {
            *p = *cs2;
            p++;
            cs2++;
        }
    }
    else
    {
        if (n != 0)
        {
            for (x=n-1; x > 0; x--)
            {
                *(p+x) = *(cs2+x);
            }
            *(p+x) = *(cs2+x);
        }
    }
    return (s1);
}


#ifdef memcmp
#undef memcmp
#endif
__PDPCLIB_API__ int memcmp(const void *s1, const void *s2, size_t n)
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
        x++;
    }
    return (0);
}

#ifdef memchr
#undef memchr
#endif
__PDPCLIB_API__ void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *p;
    size_t x = 0;

    p = (const unsigned char *)s;
    while (x < n)
    {
        if (*p == (unsigned char)c) return ((void *)p);
        p++;
        x++;
    }
    return (NULL);
}

#ifdef memset
#undef memset
#endif
__PDPCLIB_API__ void *memset(void *s, int c, size_t n)
{
    size_t x = 0;

    for (x = 0; x < n; x++)
    {
        *((char *)s + x) = (unsigned char)c;
    }
    return (s);
}

#ifndef USE_ASSEMBLER
#ifdef memcpy
#undef memcpy
#endif
#ifndef __32BIT__
__PDPCLIB_API__ void *memcpy(void *s1, const void *s2, size_t n)
{
    register const unsigned char *f = s2;
    register const unsigned char *fe;
    register unsigned char *t = s1;

    fe = f + n;
    while (f != fe)
    {
        *t++ = *f++;
    }
    return (s1);
}
#else
__PDPCLIB_API__ void *memcpy(void *s1, const void *s2, size_t n)
{
    register unsigned int *p = (unsigned int *)s1;
    register unsigned int *cs2 = (unsigned int *)s2;
    register unsigned int *endi;

    endi = (unsigned int *)((char *)p + (n & ~0x03));
    while (p != endi)
    {
        *p++ = *cs2++;
    }
    switch (n & 0x03)
    {
        case 0:
            break;
        case 1:
            *(char *)p = *(char *)cs2;
            break;
        case 2:
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            break;
        case 3:
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            break;
    }
    return (s1);
}
#endif /* 32BIT */
#endif /* USE_ASSEMBLER */
