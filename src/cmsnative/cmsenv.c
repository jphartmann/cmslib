/* Environment and other static stuff that should not be in go390    */
/*                                 John Hartmann 5 May 2014 16:59:09 */

/*********************************************************************/
/* Change activity:                                                  */
/* 5 May 2014  New module.                                           */
/*********************************************************************/

char ** environ;

long long __epoch=(70L*365L+70L/4L)*86400LL*1000000LL;

/* These  guys  are  populated by the library startup in goosj.c &c. */
/* We  do  need  a  pointer  to  an  array  rather  than an array of */
/* pointers.  In theory the array can be extended.                   */
typedef struct FILE FILE;
FILE * __userFiles[10];
int __fileslots = 10;

/* Forward declarations:                                             */
/* End of forward declarations.                                      */
