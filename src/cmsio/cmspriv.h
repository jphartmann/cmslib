/* Private header file for the cms C library.                        */
/*                                John Hartmann 11 Feb 2015 12:16:57 */

/*********************************************************************/
/* Change activity:                                                  */
/*11 Feb 2015  New header file.                                      */
/*********************************************************************/

#if !defined(_JPH_CMSPRIV_H)
#define _JPH_CMSPRIV_H

enum _einval_reason
{
   _einv_rsn_bad_mode1,        /* Bad first character of mode string */
   _einv_rsn_bad_mode_char,  /* Unexpected character uin mode string */
   _einv_rsn_bad_fd_acc,           /* Bad access for file descriptor */
   _einv_rsn_bad_fd_none,             /* File descriptor not open    */
   _einv_rsn_bad_fn_onesl,            /* / not followed by / or :    */
   _einv_rsn_bad_fn_modelong,         /* /xxx/                       */
   _einv_rsn_bad_fn_fplong,           /* /xxxxxxxxx:                 */
   _einv_rsn_bad_fn_fpfsunterm,     /* No slash terminating filepool */
   _einv_rsn_bad_fn_fslong,           /* ~xxxxxxxxx:                 */
   _einv_rsn_bad_fn_dplong,           /* Directory path too long     */
   _einv_rsn_bad_fn_leaddot,          /* .xx                         */
   _einv_rsn_bad_fn_noft,             /* xx                          */
   _einv_rsn_bad_fn_fnftlong,
   _einv_rsn_bad_fn_fsmissing,        /* No file space               */
   _einv_rsn_bad_dmsexist,            /* Error on DMSEXIST           */
   _einv_rsn_bad_lrecl,               /* No number after lrecl=      */
   _einv_rsn_bad_recfm,
   _einv_rsn_recfm_diff,              /* Not same as existing file   */
   _einv_rsn_bad_mode,
   _einv_rsn_bad_mode_del,
   _einv_rsn_long_opt,                /* Option string is too long   */
};

enum _enoent_reason
{
   _enoent_rsn_rdonly,                /* ain't there                 */
};

extern int __decofl(const char * mode, int * fb, int * lenfb);
extern struct __file * _getfile(int fd, int acc);
extern int _seterr_(
   const int rv,                      /* Desired return value        */
   const int eno,                     /* errno                       */
   const int reason,                  /* Unique reason code          */
   const char * __restrict msg,       /* Message explaining trouble  */
   const char * __restrict object,    /* Object if any               */
   const char * fn,
   int line
   );
#define _seterr(rv, eno, rs, m, o) _seterr_(rv, eno, rs, m, o, __FILE__, __LINE__)

#endif
