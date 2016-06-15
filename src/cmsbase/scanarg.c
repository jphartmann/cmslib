/* Scan and tokenise argument string.                                */
/*                                John Hartmann 24 Jan 2015 16:20:19 */

/*********************************************************************/
/* Redirection  is  n>f,  but  n  but be a separate token.  That is, */
/* ab2>err  redirects  standard  output to err (not standard error). */
/* And so does '2'>err.  So we shall have to enter lookahead when we */
/* meet a digit after white space.                                   */
/*                                                                   */
/* Quotes  are  simply  removed,  so we must process I/O redirection */
/* immediately as you cannot distinguish '>' and > later.            */
/*                                                                   */
/* Change activity:                                                  */
/*24 Jan 2015  New module.                                           */
/*********************************************************************/

#include <stdio.h>
#include <assert.h>

/* Forward declarations:                                             */
static int errmsg(const int offs, const char * s, const char * msg, const int rc);
static enum fsminputs decinput(int i, const char * s, int len);
static int __cntargs(const char * s, int len, int * tc, int * bc, int * bsize, int debug);
static int __doargv(const char * s, int len, char ** av, char * t, int bsize, int debug);
/* End of forward declarations.                                      */

/*********************************************************************/
/* Build the argv strings.  This is not quite as trivial as it might */
/* seem.                                                             */
/*                                                                   */
/* We  use  a  two-pass  process.   The first pass counts tokens and */
/* bytes; the second builds the actual strings.                      */
/*********************************************************************/

#include "args.c"

static const unsigned char enc[256] =
{
   [0] = input_white,
   [' '] = input_white,
   ['\t'] = input_white,
   ['\r'] = input_white,
   ['\n'] = input_white,
   ['0' ... '9'] = input_digit,
   ['>'] = input_redir,
   ['<'] = input_redir,
   ['"'] = input_dq,
   ['\\'] = input_esc,
   ['\''] = input_sq,
};

static int
__cntargs(const char * s, int len, int * tc, int * bc, int * bsize, int debug)
{
   int ix;
   int qbeg = 17;
   enum fsmstates state = state_white;
   int fdcount = 42;              /* Count in file descriptor number */
   int fncount = 37;                /* Buffer required for file name */

   *tc = 0;
   *bc = 0;
   *bsize = 0;

   for (ix = 0; ; ix++)
   {
      enum fsminputs inc = decinput(ix, s, len);
      struct xition px = navigate[state][inc];
      int j;

#if defined(FSMDEBUG)
      if (debug) printf("state %d %s input %d %s -> %d %s\n",
         state, decode_fsmstates[state],
         inc, decode_fsminputs[inc],
         px.nustate, decode_fsmstates[px.nustate]);
#endif

      state = px.nustate;
      for (j = 0; ; j++)
      {
         enum fsmactions act = px.actions[j];

         if (!act) break;
#if defined(FSMDEBUG)
         if (debug) printf("  action %d %s have %d tokens, %d bytes.\n",
            act, decode_fsmactions[act], *tc, *bc);
#endif

         switch (act)
         {
            case action_none:
               assert(0);
            case action_begstr:
               qbeg = ix;
               break;
            case action_begfd:
               fdcount = 0;
               break;
            case action_begtoken:
               (*tc)++;
               break;
            case action_doredir:      /* > or <                      */
               if ('>' == s[ix] && '>' == s[ix+1]) ix++;
               fncount = 0;
               break;
            case action_endtoken:
               qbeg = 0;
               break;
            case action_error1:
               return errmsg(ix, s, "Nothing to escape", 16);
            case action_error2:
               return errmsg(qbeg, s, "Unterminated string", 17);
            case action_error3:
               return errmsg(ix, s, "Missing file name", 18);
            case action_error4:
               return errmsg(ix, s, "Invalid token sequence", 19);
            case action_fdigit:
               fdcount++;             /* Have one more               */
               break;
            case action_fnchar:
               fncount++;
               break;
            case action_incr:
               (*bc)++;
               break;
            case action_nofd:         /* Number not followed by nose */
               (*tc)++;
               (*bc) += fdcount;
               break;
            case action_redirfile:    /* Have file name              */
               if (fncount > *bsize) *bsize = fncount;
               break;
            case action_setfd:
               break;
            case action_stop:
               return 0;
            default:
               assert(0);
         }
      }
   }
   return 0;
}

/*********************************************************************/
/* Second pass for real.  Return codes are trouble with redirecting. */
/*********************************************************************/

static int
__doargv(const char * s, int len, char ** av, char * t, int bsize, int debug)
{
   int ix;
   int fdbeg = 0;
   char * mode = "?";
   int tokens = 0;
   int fd = -1;
   int usefd = 0;
   enum fsmstates state = state_white;
   char fname[bsize + 1];             /* File name buffer            */
   int fdcount = 42;              /* Count in file descriptor number */
   int fncount = 37;                /* Buffer required for file name */

   /* 1.5 loop to process end of string too                          */
   for (ix = 0; ; ix++)
   {
      enum fsminputs inc = decinput(ix, s, len);
      struct xition px = navigate[state][inc];
      int j;

      /* No point in debugging here; it is identical to pass 1       */
      state = px.nustate;
      for (j = 0; ; j++)
      {
         enum fsmactions act = px.actions[j];
         int k;
         int rv;

         if (!act) break;
         switch (act)
         {
            case action_none:
               assert(0);
            case action_begfd:
               fdcount = 0;
               fdbeg = ix;
               fd = 0;
               break;
            case action_begstr:
               break;
            case action_begtoken:
               av[tokens++] = t;
               break;
            case action_doredir:
               if ('<' == s[ix])
               {
                  mode = "r";
                  usefd = 0;
               }
               else if ('>' != s[ix+1])
               {
                  mode = "w";
                  usefd = 1;
               }
               else
               {
                  ix++;
                  mode = "a";
                  usefd = 1;
               }
               fncount = 0;
               memset(fname, 0, bsize + 1);
               break;
            case action_endtoken:
               *t++ = 0;
               break;
            case action_error1:
            case action_error2:
            case action_error3:
            case action_error4:
               assert(0);
               break;
            case action_fdigit:
               fd *= 10;
               fd += 0xf & s[ix];
               fdcount++;
               break;
            case action_fnchar:
               fname[fncount++] = s[ix];
               break;
            case action_incr:
               *t++ = s[ix];
               break;
            case action_nofd:
#if defined(FSMDEBUG)
               if (debug) printf("Number is %d bytes start %d.\n", fdcount, fdbeg);
#endif
               av[tokens++] = t;
               for (k = 0; fdcount > k; k++)
                  *t++ = s[k + fdbeg];
               break;
            case action_redirfile:
               rv = scanopen(usefd, fname, mode);
               if (rv) return rv;     /* Could not open              */
               break;
            case action_setfd:
               usefd = fd;            /* This instead                */
               break;
            case action_stop:
               av[tokens] = NULL;
               return 0;
            default:
               assert(0);
         }
      }
   }
   return 0;                          /* For gcc                     */
}

/*********************************************************************/
/* Decode input or signal end                                        */
/*********************************************************************/

static enum fsminputs
decinput(int i, const char * s, int len)
{
   assert(i < len + 1);               /* Missing end transition      */
   if (len == i) return input_end;    /* Past end                    */
   return enc[0xff & s[i]];
}

/*********************************************************************/
/* Issue rror message and set return code.                           */
/*********************************************************************/

static int
errmsg(const int offs, const char * s, const char * msg, const int rc)
{
   __sayf("Error offset %d:  %s.\n", offs, msg);
   __sayf("%s\n", s);
   __sayf("%*s^\n", offs, "");

   return rc;
}
