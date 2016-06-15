/* Selected BSD string ops                                           */
/*                                John Hartmann 20 Jun 2011 11:31:52 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_STRINGS_H)
   #define _JPH_STRINGS_H

#define strcasecmp _stracmp
#define strncasecmp _strnacmp

extern int strcasecmp(const char * s1, const char * s2);
extern int strncasecmp(const char * s1, const char * s2, size_t length);

#endif
