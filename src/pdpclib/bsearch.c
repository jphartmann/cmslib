/*                                                                   */
/*                                John Hartmann 17 Jun 2011 15:42:48 */

/*********************************************************************/
/* Change activity:                                                  */
/*29 Jun 2011  jph Fix order of compare arguments.                   */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include "stdlib.h"
#include "stddef.h"

/* Forward declarations:                                             */
/* End of forward declarations.                                      */

__PDPCLIB_API__ void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *))
{
    size_t try;
    int res;
    const void *ptr;

    while (nmemb > 0)
    {
        try = nmemb / 2;
        ptr = (void *)((char *)base + try * size);
        /* The  man  page  says  the  key is the first one.  This is */
        /* important  when the key is not the same structure as base */
        /* (it could be just a string).  jph                         */
        res = compar(key, ptr);
        if (res == 0)
        {
            return ((void *)ptr);
        }
        else if (res < 0)
        {
            nmemb = nmemb - try - 1;
            base = (const void *)((const char *)ptr + size);
        }
        else
        {
            nmemb = try;
        }
    }
    return (NULL);
}
