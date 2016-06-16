/*                                                                   */
/*                                John Hartmann 17 Jun 2011 15:45:52 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stddef.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ int atoi(const char *nptr)
{
    return ((int)strtol(nptr, (char **)NULL, 10));
}

/* this logic is also in vvscanf - if you update this, update
   that one too */

__PDPCLIB_API__ unsigned long int strtoul(
    const char *nptr, char **endptr, int base)
{
    unsigned long x = 0;
    int undecided = 0;

    if (base == 0)
    {
        undecided = 1;
    }
    while (isspace((unsigned char)*nptr))
    {
        nptr++;
    }
    while (1)
    {
        if (isdigit((unsigned char)*nptr))
        {
            if (base == 0)
            {
                if (*nptr == '0')
                {
                    base = 8;
                }
                else
                {
                    base = 10;
                    undecided = 0;
                }
            }
            x = x * base + (*nptr - '0');
            nptr++;
        }
        else if (isalpha((unsigned char)*nptr))
        {
            if ((*nptr == 'X') || (*nptr == 'x'))
            {
                if ((base == 0) || ((base == 8) && undecided))
                {
                    base = 16;
                    undecided = 0;
                    nptr++;
                }
                else if (base == 16)
                {
                    /* hex values are allowed to have an optional 0x */
                    nptr++;
                }
                else
                {
                    break;
                }
            }
            else if (base <= 10)
            {
                break;
            }
            else
            {
                x = x * base + (toupper((unsigned char)*nptr) - 'A') + 10;
                nptr++;
            }
        }
        else
        {
            break;
        }
    }
    if (endptr != NULL)
    {
        *endptr = (char *)nptr;
    }
    return (x);
}

__PDPCLIB_API__ long int strtol(const char *nptr, char **endptr, int base)
{
    unsigned long y;
    long x;
    int neg = 0;

    while (isspace((unsigned char)*nptr))
    {
        nptr++;
    }
    if (*nptr == '-')
    {
        neg = 1;
        nptr++;
    }
    else if (*nptr == '+')
    {
        nptr++;
    }
    y = strtoul(nptr, endptr, base);
    if (neg)
    {
        x = (long)-y;
    }
    else
    {
        x = (long)y;
    }
    return (x);
}
