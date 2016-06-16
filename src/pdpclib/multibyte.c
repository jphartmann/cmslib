/*                                                                   */
/*                                John Hartmann 17 Jun 2011 15:47:18 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include "stdlib.h"
#include "string.h"
#include "stddef.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ int mblen(const char *s, size_t n)
{
    if (s == NULL)
    {
        return (0);
    }
    if (n == 1)
    {
        return (1);
    }
    else
    {
        return (-1);
    }
}

__PDPCLIB_API__ int mbtowc(wchar_t *pwc, const char *s, size_t n)
{
    if (s == NULL)
    {
        return (0);
    }
    if (n == 1)
    {
        if (pwc != NULL)
        {
            *pwc = *s;
        }
        return (1);
    }
    else
    {
        return (-1);
    }
}

__PDPCLIB_API__ int wctomb(char *s, wchar_t wchar)
{
    if (s != NULL)
    {
        *s = wchar;
        return (1);
    }
    else
    {
        return (0);
    }
}

__PDPCLIB_API__ size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n)
{
    strncpy((char *)pwcs, s, n);
    if (strlen(s) >= n)
    {
        return (n);
    }
    return (strlen((char *)pwcs));
}

__PDPCLIB_API__ size_t wcstombs(char *s, const wchar_t *pwcs, size_t n)
{
    strncpy(s, (const char *)pwcs, n);
    if (strlen((const char *)pwcs) >= n)
    {
        return (n);
    }
    return (strlen(s));
}
