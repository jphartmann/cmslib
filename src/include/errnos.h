/* Define numbers and strings together                               */
/*                                John Hartmann 28 Jun 2011 15:15:31 */

/*********************************************************************/
/* Change activity:                                                  */
/*28 Jun 2011  New header file.                                      */
/*********************************************************************/

   __ERRNO(__noerr, "No error")       /* 0                           */
   __ERRNO(EDOM,    "Domain error")   /* 1                           */
   __ERRNO(ERANGE,  "Range error")    /* 2                           */
   __ERRNO(ENOENT,  "Object does not exist")                    /* 3 */
   __ERRNO(EACCES,  "Access denied")  /* 4                           */
   __ERRNO(EINVAL,  "Value is not valid")                       /* 5 */
   __ERRNO(ENOMEM,  "No memory allocated")                      /* 6 */
   __ERRNO(EIO,     "I/O error")      /* 7                           */
   __ERRNO(EEXISTS, "File exists")    /* 8                           */
   __ERRNO(EBADF,   "File descriptor not valid")                /* 9 */
   __ERRNO(EMFILE,  "Maximum number of files already open")    /* 10 */
   __ERRNO(ECONNRESET, "Connection reset")                     /* 11 */

