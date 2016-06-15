/* Memory manager.                                                   */
/*                                John Hartmann 17 Jun 2011 14:11:28 */

/*********************************************************************/
/* Change activity:                                                  */
/*17 Jun 2011  New module.                                           */
/*********************************************************************/

#include <cmsbase.h>
#include <string.h>
#include <stdio.h>

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
/* End of forward declarations.                                      */

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
   m=p;
   m--;
   if (memcmp(m->eye, EYE, 4))
   {
      if (memcmp(m->eye, FREE, 4)){ __sayf("Bad free() %p.", p);}
      else __sayf("Duplicate free of %p.", p);
      __traceb();
      return;
   }
   memcpy(m->eye, FREE, 4);
   __freehp(m->size, m);
}
