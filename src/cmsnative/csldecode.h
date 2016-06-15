/* Decode information for CSL calls                                  */
/*                                John Hartmann 20 Jun 2011 09:20:06 */

/*********************************************************************/
/* Change activity:                                                  */
/*20 Jun 2011  New module.                                           */
/*********************************************************************/


/* Forward declarations:                                             */
/* End of forward declarations.                                      */

enum csltype
{
   t_char,                            /* character                   */
   t_fchr,                            /* char with length            */
   t_sbin,                            /* integer                     */
   t_table_char,                      /* Table of character args     */
   t_table_sbin,                      /* Table of signed bin args    */
};

/*********************************************************************/
/* One parameter                                                     */
/*********************************************************************/

struct cslparm
{
   unsigned int required: 1;
   unsigned int input: 1;
   unsigned int output: 1;
   enum csltype type;
   int length;                        /* -1 for *                    */
   const char * name;                 /* Manual entry                */
};

struct cslcall
{
   const char * name;
   const int minparms;
   const int maxparms;
   const struct cslparm * first;
};

struct cslcallinfo
{
   int count;
   const struct cslcall * calls;
};
