/* uname                                                             */
/*                                John Hartmann 28 Jul 2011 13:38:47 */

/*********************************************************************/
/* Change activity:                                                  */
/*28 Jul 2011  New header file.                                      */
/*********************************************************************/


#if !defined(_JPH_UTSNAME_H)
   #define _JPH_UTSNAME_H

struct utsname
{
    char * sysname;    /* Operating system name (e.g., "Linux") */
    char * release;    /* OS release (e.g., "2.6.28") */
    char * version;    /* OS version */
    char * machine;    /* Hardware identifier */
};

extern int uname(struct utsname *buf);

#endif
