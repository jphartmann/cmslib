/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stdlib.c - implementation of stuff in stdlib.h                   */
/*                                                                   */
/*********************************************************************/

#include "stdlib.h"
#include "string.h"
#include "stddef.h"
#include <stdio.h>

/* VSE is similar to MVS */
#if defined(__VSE__)
#define __MVS__ 1
#endif

/* PDOS and MSDOS use the same interface most of the time */
#if defined(__PDOS__) && !defined(__MVS__)
#define __MSDOS__
#endif

#ifdef __OS2__
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#include <os2.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#if __MVSCMS__
#include "mvssupa.h"
#endif

#ifdef __MVS__
extern int __tso;
#endif

__PDPCLIB_API__ div_t div(int numer, int denom)
{
    div_t x;

    x.quot = numer / denom;
    x.rem = numer % denom;
    return (x);
}

__PDPCLIB_API__ ldiv_t ldiv(long int numer, long int denom)
{
    ldiv_t x;

    x.quot = numer / denom;
    x.rem = numer % denom;
    return (x);
}



/* The following code was taken from Paul Markham's "EXEC" program,
   and adapted to create a system() function.  The code is all
   public domain */

__PDPCLIB_API__ int system(const char *string)
{
#if !defined(__ZVM__)
#ifdef __OS2__
    char err_obj[100];
    APIRET rc;
    RESULTCODES results;

    if (string == NULL)
    {
        return (1);
    }
    rc = DosExecPgm(err_obj, sizeof err_obj, EXEC_SYNC,
                    (PSZ)string, NULL, &results, (PSZ)string);
    if (rc != 0)
    {
        return (rc);
    }
    return ((int)results.codeResult);
#endif
#ifdef __WIN32__
    BOOL rc;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    DWORD ExitCode;

    memset(&si, 0, sizeof si);
    si.cb = sizeof si;
    memset(&pi, 0, sizeof pi);
    rc = CreateProcess(NULL,
                       (char *)string,
                       NULL,
                       NULL,
                       FALSE,
                       0,
                       NULL,
                       NULL,
                       &si,
                       &pi);
    if (!rc)
    {
        return (GetLastError());
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &ExitCode);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return (ExitCode);
#endif
#ifdef __MSDOS__
    static unsigned char cmdt[140];
    static struct {
        int env;
        unsigned char *cmdtail;
        char *fcb1;
        char *fcb2;
    } parmblock = { 0, cmdt, NULL, NULL };
    size_t len;
    char *cmd;

    if (string == NULL)
    {
        return (1);
    }
    len = strlen(string);
    cmdt[0] = (unsigned char)(len + 3);
    memcpy(&cmdt[1], "/c ", 3);
    memcpy(&cmdt[4], string, len);
    memcpy(&cmdt[len + 4], "\r", 2);
    cmd = getenv("COMSPEC");
    if (cmd == NULL)
    {
        cmd = "\\command.com";
    }
    __exec(cmd, &parmblock);
    return (0);
#endif
#if defined(MUSIC)
    return (__system(strlen(string), string));
#elif defined(__MVS__)
    char pgm[9];
    size_t pgm_len;
    size_t cnt;
    char *p;

    p = strchr(string, ' ');
    if (p == NULL)
    {
        p = strchr(string, '\0');
    }

    pgm_len = p - string;
    /* don't allow a program name greater than 8 */

    if (pgm_len > 8)
    {
        return (-1);
    }
    memcpy(pgm, string, pgm_len);
    pgm[pgm_len] = '\0';

    /* uppercase the program name */
    for (cnt = 0; cnt < pgm_len; cnt++)
    {
        pgm[cnt] = toupper((unsigned char)pgm[cnt]);
    }

    /* point to parms */
    if (*p != '\0')
    {
        p++;
    }

    /* all parms now available */
    /* we use 1 = batch or 2 = tso */
    return (__system(__tso ? 2: 1, pgm_len, pgm, strlen(p), p));
#endif
#else
    /* Pass command to the cms subcommand to be executed. */
    struct eplist epl = {string, string, string + strlen(string), 0};
    struct pl { char verb[8]; char fence[8]; } opl = {"CMS     ",  FENCE };
    int rv = __svc204(&epl, opl.verb, 0x2 << 24, 0);
    return rv;
#endif
}
