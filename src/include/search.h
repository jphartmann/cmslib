/* AVL trees or an approximation.                                    */
/*                                 John Hartmann 9 Jun 2011 13:01:05 */

/*********************************************************************/
/* Change activity:                                                  */
/* 9 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_SEARCH_H)
   #define _JPH_SEARCH_H



   typedef enum {preorder, postorder, endorder, leaf} VISIT;

       void *tsearch(const void *key, void **rootp,
                       int (*compar)(const void *, const void *));

       void *tfind(const void *key, void * const *rootp,
                       int (*compar)(const void *, const void *));

       void *tdelete(const void *key, void **rootp,
                       int (*compar)(const void *, const void *));

       void twalk(const void *root, void (*action)(const void *nodep,
                                          const VISIT which,
                                          const int depth));

       #if defined(_GNU_SOURCE) || defined(__USE_GNU)

       void tdestroy(void *root, void (*free_node)(void *nodep));

       #endif


#endif
