/* CMS Callable services stuff                                       */
/*                                John Hartmann 20 Jun 2011 06:42:28 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_CSL_H)
   #define _JPH_CSL_H

enum __csl_debug
{
   __csl_quiet,                       /* No info                     */
   __csl_error,                       /* Log errors                  */
   __csl_verbose,                     /* Log all calls               */
};

extern enum __csl_debug __csldbg;
extern int __cslrc;
extern int __cslrsn;

/* Build parameter list and invoke routine                           */
extern int tocsl(int count, const char * name, ...);
extern int oscall(int (* f)(void), int count, ...);

#endif
