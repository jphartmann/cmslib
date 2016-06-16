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

#if defined(__ZVM__)
#include <cmsbase.h>
#endif

#ifdef __MVS__
extern int __tso;
#endif

#if USE_MEMMGR
#include "__memmgr.h"
/* GCCMVS 3.4.6 requires 49 MB minimum for full optimization */
/* so we give it 60. GCCMVS 3.2.3 only requires 20 MB */
/* Note that you can set MAX_CHUNK to less than REQ_CHUNK */
/* But don't do this until MVS/380 etc have been changed to */
/* allow multiple memory requests. */
#if defined(MULMEM)
#define MAX_CHUNK 60000000
#define REQ_CHUNK 60000000
#else
#define MAX_CHUNK 60000000 /* maximum size we will store in memmgr */
#define REQ_CHUNK 60000000 /* size that we request from OS */
#endif
void *__lastsup = NULL; /* last thing supplied to memmgr */
#endif

#ifdef __MSDOS__
#ifdef __WATCOMC__
#define CTYP __cdecl
#else
#define CTYP
#endif
void CTYP __allocmem(size_t size, void **ptr);
void CTYP __freemem(void *ptr);
extern unsigned char *__envptr;
void CTYP __exec(char *cmd, void *env);
#endif

#ifdef __gnu_linux__
void *__allocmem(size_t size);
#endif

#if !defined(__ZVM__)
   void (*__userExit[__NATEXIT])(void);
#endif

__PDPCLIB_API__ void *malloc(size_t size)
{
#ifdef __OS2__
    PVOID BaseAddress;
    ULONG ulObjectSize;
    ULONG ulAllocationFlags;
    APIRET rc;

    ulObjectSize = size + sizeof(size_t);
    ulAllocationFlags = PAG_COMMIT | PAG_WRITE | PAG_READ;
    rc = DosAllocMem(&BaseAddress, ulObjectSize, ulAllocationFlags);
    if (rc != 0) return (NULL);
    *(size_t *)BaseAddress = size;
    BaseAddress = (char *)BaseAddress + sizeof(size_t);
    return ((void *)BaseAddress);
#endif
#ifdef __MSDOS__
    void *ptr;

    __allocmem(size, &ptr);
    return (ptr);
#endif
#if USE_MEMMGR
    void *ptr;

    if (size > MAX_CHUNK)
    {
#if defined(__MVS__) || defined(__CMS__) || defined(__gnu_linux__)
#if defined(MULMEM)
        /* If we support multiple memory requests */
        ptr = __getm(size);
#else
        ptr = NULL;
#endif
#elif defined(__WIN32__)
        ptr = GlobalAlloc(0, size + sizeof(size_t));
        if (ptr != NULL)
        {
            *(size_t *)ptr = size;
            ptr = (char *)ptr + sizeof(size_t);
        }
#elif defined(__gnu_linux__)
        ptr = __allocmem(size + sizeof(size_t));
        if (ptr != NULL)
        {
            *(size_t *)ptr = size;
            ptr = (char *)ptr + sizeof(size_t);
        }
#endif
    }
    else
    {
        ptr = memmgrAllocate(&__memmgr, size, 0);
        if (ptr == NULL)
        {
            void *ptr2;

#if defined(__MVS__) || defined(__CMS__)
            /* until MVS/380 is fixed, don't do an additional request,
               unless MULMEM is defined */
#if defined(MULMEM)
            if (1)
#else
            if (__memmgr.start == NULL)
#endif
            {
                ptr2 = __getm(REQ_CHUNK);
            }
            else
            {
                ptr2 = NULL;
            }
#elif defined(__WIN32__)
            ptr2 = GlobalAlloc(0, REQ_CHUNK);
            if (ptr2 != NULL)
            {
                *(size_t *)ptr2 = size;
                ptr2 = (char *)ptr2 + sizeof(size_t);
            }
#elif defined(__gnu_linux__)
            ptr2 = __allocmem(REQ_CHUNK);
            if (ptr2 != NULL)
            {
                *(size_t *)ptr2 = size;
                ptr2 = (char *)ptr2 + sizeof(size_t);
            }
#endif
            if (ptr2 == NULL)
            {
                return (NULL);
            }
            __lastsup = ptr2;
            memmgrSupply(&__memmgr, ptr2, REQ_CHUNK);
            ptr = memmgrAllocate(&__memmgr, size, 0);
        }
    }
    return (ptr);
#else /* not MEMMGR */
#if defined(__MVS__) || defined(__CMS__)
   #if 0
   __sayf(__FILE__ ": getting %ld bytes\n", size);
   #endif
    return (__getm(size));
#elif defined(__WIN32__)
    void *ptr;

    ptr = GlobalAlloc(0, size + sizeof(size_t));
    if (ptr != NULL)
    {
        *(size_t *)ptr = size;
        ptr = (char *)ptr + sizeof(size_t);
    }
    return (ptr);
#elif defined(__gnu_linux__)
    void *ptr;

    ptr = __allocmem(size + sizeof(size_t));
    if (ptr != NULL)
    {
        *(size_t *)ptr = size;
        ptr = (char *)ptr + sizeof(size_t);
    }
    return (ptr);
#endif
#endif /* not MEMMGR */
}

__PDPCLIB_API__ void *calloc(size_t nmemb, size_t size)
{
    void *ptr;
    size_t total;

    if (nmemb == 1)
    {
        total = size;
    }
    else if (size == 1)
    {
        total = nmemb;
    }
    else
    {
        total = nmemb * size;
    }
    ptr = malloc(total);
    if (ptr != NULL)
    {
        memset(ptr, '\0', total);
    }
    return (ptr);
}

__PDPCLIB_API__ void *realloc(void *ptr, size_t size)
{
    char *newptr;
    size_t oldsize;

    if (size == 0)
    {
        if (ptr) free(ptr);
        return (NULL);
    }
#if USE_MEMMGR
    if (memmgrRealloc(&__memmgr, ptr, size) == 0)
    {
        return (ptr);
    }
#endif
    newptr = malloc(size);
    if (newptr == NULL)
    {
        return (NULL);
    }
    if (ptr != NULL)
    {
        oldsize = *((size_t *)ptr - 1);
        if (oldsize < size)
        {
            size = oldsize;
        }
        memcpy(newptr, ptr, size);
        free(ptr);
    }
    return (newptr);
}

__PDPCLIB_API__ void free(void *ptr)
{
#ifdef __OS2__
    if (ptr != NULL)
    {
        ptr = (char *)ptr - sizeof(size_t);
        DosFreeMem((PVOID)ptr);
    }
#endif
#ifdef __MSDOS__
    if (ptr != NULL)
    {
        __freemem(ptr);
    }
#endif
#if USE_MEMMGR
    if (ptr != NULL)
    {
        size_t size;

        size = *((size_t *)ptr - 1);
        if (size > MAX_CHUNK)
        {
#if defined(__MVS__) || defined(__CMS__)
#if defined(MULMEM) || defined(__ZVM__)
            /* Ignore, unless MULMEM is defined, until MVS/380 is fixed */
            __freem(ptr);
#endif
#elif defined(__WIN32__)
            GlobalFree(ptr);
#endif
        }
        else
        {
            memmgrFree(&__memmgr, ptr);
        }
    }
#else /* not using MEMMGR */
#if defined(__MVS__) || defined(__CMS__)
    if (ptr != NULL)
    {
        __freem(ptr);
    }
#endif
#ifdef __WIN32__
    if (ptr != NULL)
    {
        GlobalFree(ptr);
    }
#endif
#endif /* not USE_MEMMGR */
    return;
}


__PDPCLIB_API__ void exit(int status)
{
   int i;
#if defined(__ZVM__)
   #define exiting (__getgbl()->exiting)
#else
   static int exiting;
#endif

   if (exiting) __exit(status);
   exiting = 1;                       /* Prevent recursions          */

   for (i=0; __NATEXIT > i; i++)
      if (__userExit[i]) __userExit[i]();

   for (i=0; __NFILE > i; i++)
      if (__userFiles[i]) fclose(__userFiles[i]);

   __exit(status);
}

#ifdef abs
#undef abs
#endif
__PDPCLIB_API__ int abs(int j)
{
    if (j < 0)
    {
        j = -j;
    }
    return (j);
}

__PDPCLIB_API__ div_t div(int numer, int denom)
{
    div_t x;

    x.quot = numer / denom;
    x.rem = numer % denom;
    return (x);
}

#ifdef labs
#undef labs
#endif
__PDPCLIB_API__ long int labs(long int j)
{
    if (j < 0)
    {
        j = -j;
    }
    return (j);
}

__PDPCLIB_API__ ldiv_t ldiv(long int numer, long int denom)
{
    ldiv_t x;

    x.quot = numer / denom;
    x.rem = numer % denom;
    return (x);
}

__PDPCLIB_API__ int atexit(void (*func)(void))
{
    int x;

    for (x = 0; x < __NATEXIT; x++)
    {
        if (__userExit[x] == 0)
        {
            __userExit[x] = func;
            return (0);
        }
    }
    return (-1);
}

__PDPCLIB_API__ char *getenv(const char *name)
{
#ifdef __OS2__
    PSZ result;

    if (DosScanEnv((void *)name, (void *)&result) == 0)
    {
        return ((char *)result);
    }
#endif
#if defined(__MSDOS__) || defined(__WIN32__)
    char *env;
    size_t lenn;

#ifdef __WIN32__
    env = GetEnvironmentStrings();
    /* jph: and where,pray, is this handle returned?                 */
#else
    env = (char *)__envptr;
#endif
    lenn = strlen(name);
    while (*env != '\0')
    {
        if (strncmp(env, name, lenn) == 0)
        {
            if (env[lenn] == '=')
            {
                return (&env[lenn + 1]);
            }
        }
        env = env + strlen(env) + 1;
    }
#endif
#if defined(__ZVM__)
   /* And for anything remotely unixy                                */

   char ** ep = environ;
   const size_t len = name ? strlen(name) : 0;

   if (!name || !ep || !len) return NULL;

   for (; *ep; ep++)
   {
      size_t i;
      char * var = *ep;

      for (i = 0; len>i; i++)
         if (name[i] != var[i]) break;

      if (len == i && '=' == var[i]) return var + i + 1;
   }
#endif
    return (NULL);
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
