/* Memory manager.                                                   */
/*                                John Hartmann 17 Jun 2011 14:11:28 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include <cmsbase.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*********************************************************************/
/* Prefix to an allocated area.                                      */
/*********************************************************************/

struct __heap
{
   size_t size;
   union
   {
      char eye[4];
      #define EYE "zvm"
      #define FREE "fre"
      size_t fill;                    /* 8 bytes, perhaps            */
   };
   char user[0];                      /* What user sees              */
};

/* Forward declarations:                                             */
static struct __heap * verptr(void * ptr);
/* End of forward declarations.                                      */

/*********************************************************************/
/* Low level routines to allocate and free.                          */
/*********************************************************************/

void *
__getm(unsigned size)
{
   unsigned toget = size + sizeof(struct __heap);

   struct __heap * m=__gethp(toget);

   if (m)
   {
      memcpy(m->eye, EYE, 4);
      #if 0
      __sayf("Got %d bytes at %p %p\n", toget, m, m->user);
      #endif
      return m->user;
   }

   __WERROR("__getm Cannot allocate %d bytes.", size);
   __traceb();
   __exit(18);
   return m;
}

void
__freem(void * p)
{
   struct __heap * m;

   if (!p) return;
   m = verptr(p);
   if (!m) return;
   memcpy(m->eye, FREE, 4);
   __freehp(m->size, m);
}

/*********************************************************************/
/* stdlib declared stuff.                                            */
/*********************************************************************/

void *
malloc(size_t size)
{
   return (__getm(size));
}

void *
calloc(size_t nmemb, size_t size)
{
   size_t toget = nmemb * size;
   void * ptr = __getm(toget);

   if (ptr) memset(ptr, 0, toget);
   return ptr;
}

void *
realloc(void *ptr, size_t size)
{
   struct __heap * m;
   void * nu;

   if (!ptr) return __getm(size);
   if (!size)
   {
      __freem(ptr);
      return 0;
   }

   m = verptr(ptr);
   if (!m) return 0;

   if (m->size >= size) return ptr;

   nu = __getm(size);
   if (!nu) return 0;
   memcpy(nu, ptr, m->size);
   __freem(ptr);
   return nu;
}

void
free(void *ptr)
{
   __freem(ptr);
}

/*********************************************************************/
/* Verify the pointer passed to free() amd realloc()                 */
/*********************************************************************/

static struct __heap *
verptr(void * ptr)
{
   struct __heap * m = ptr;

   m--;
   if (memcmp(m->eye, EYE, 4))        /* Not currently allocated     */
   {
      if (memcmp(m->eye, FREE, 4))
         __sayf("Storage at %p was not allocated by malloc().", ptr);
      else
         __sayf("Storage at %p has already been freed.", ptr);
      __traceb();
      return 0;
   }
   return m;
}
