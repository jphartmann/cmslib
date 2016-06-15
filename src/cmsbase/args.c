/* Built 9 Feb 2015 20:07:43 */ 
/* From  ARGS     FSM      H1 V         79        102          1  2/09/15 20:07:39 */ 
  
#if 0 
* Argument scanning.  DOFSM to generate code
 
* State names in column 1
* Transitions indented.  <input> <nustate> <action>.  Multiple inputs separated
*    new state * means stay in current state; action - means none
 
* Initial state.  After white space
white
         white     *         -
         end       *         stop
         any       token     begtoken,incr
         digit     fd        begfd,fdigit
         redir     redir     doredir
         esc       tokesc    begtoken
         dq        dqs1      begstr,begtoken
         sq        sqs1      begstr,begtoken
 
token
         white     white     endtoken
         end       *         endtoken,stop
         any       token     incr
         digit     *         incr  ; not special after something else
         redir     redir     endtoken,doredir
         esc       tokesc    -
         dq        dqs1      begstr
         sq        sqs1      begstr
 
tokesc
         end       *         error1 ; Nothing to escape
         white,any,digit,redir,esc,dq,sq  token incr ; Any old char
 
dqs1
         end       *         error2 ;unterminated strig
         white,any,digit,redir,sq  *  incr
         esc       dqsx      -
         dq        token     -
 
dqsx     ; escape in double quoted string
         end       *         error1 ; Nothing to escape
         white,any,digit,redir,esc,dq,sq  dqs1  incr ; Any old char
 
sqs1
         end       *         error2 ;unterminated strig
         white,any,digit,redir,dq,esc  *  incr
         sq        token     -
 
fd
         digit     *         fdigit
         end       *         nofd,endtoken,stop
         white     fdwhite   -
         redir     redir     doredir,setfd ; don-t take default fd
         any       token     nofd,incr
         esc       tokesc    nofd
         dq        dqs1      nofd,begstr
         sq        sqs1      nofd,begstr
 
fdwhite
         white     *         -
         end       *         nofd,endtoken,stop
         redir     redir     doredir,setfd ; don-t take default fd
         digit     fd        nofd,endtoken,begfd,fdigit
         any       token     nofd,endtoken,begtoken,incr
         esc       tokesc    nofd,endtoken,begtoken
         dq        dqs1      nofd,endtoken,begtoken,begstr
         sq        sqs1      nofd,endtoken,begtoken,begstr
 
* We are committed to want a file name here
redir  ; after > >> < want file name for redirect
         end       *         error3 ; no file name
         white     *         -
         redir     redir     error4 ; Invalid token sequence
         any,digit fname     fnchar
         esc       fnesc     -
         dq        dqfn      begstr
         sq        sqfn      begstr
 
fname
         end       *         redirfile,stop
         white     white     redirfile
         any,digit *         fnchar
         esc       fnesc     -
         dq        dqfn      begstr
         sq        sqfn      begstr
 
fnesc
         end       *         error1 ; Nothing to escape
         white,any,digit,redir,esc,dq,sq  fname fnchar ; Any old char
 
dqfn
         end       *         error2 ;unterminated strig
         white,any,digit,redir,sq  *  fnchar
         esc       dqfx      -
         dq        fname     -
 
dqfx     ; escape in double quoted string
         end       *         error1 ; Nothing to escape
         white,any,digit,redir,esc,dq,sq  dqfn  fnchar ; Any old char
 
sqfn
         end       *         error2 ;unterminated strig
         white,any,digit,redir,dq,esc  *  fnchar
         sq        fname     -
#endif
  
enum fsmstates 
{ 
   state_white,
   state_token,
   state_tokesc,
   state_dqs1,
   state_dqsx,
   state_sqs1,
   state_fd,
   state_fdwhite,
   state_redir,
   state_fname,
   state_fnesc,
   state_dqfn,
   state_dqfx,
   state_sqfn,
};
  
#if defined(FSMDEBUG) 
static char * decode_fsmstates[] = 
{ 
   "white",
   "token",
   "tokesc",
   "dqs1",
   "dqsx",
   "sqs1",
   "fd",
   "fdwhite",
   "redir",
   "fname",
   "fnesc",
   "dqfn",
   "dqfx",
   "sqfn",
};
#endif
 
#define FSMSTATES 14
#define TYPE_FSMSTATES unsigned char
  
enum fsminputs 
{ 
   input_any,
   input_digit,
   input_dq,
   input_end,
   input_esc,
   input_redir,
   input_sq,
   input_white,
};
  
#if defined(FSMDEBUG) 
static char * decode_fsminputs[] = 
{ 
   "any",
   "digit",
   "dq",
   "end",
   "esc",
   "redir",
   "sq",
   "white",
};
#endif
 
#define FSMINPUTS 8
#define TYPE_FSMINPUTS unsigned char
  
enum fsmactions 
{ 
   action_none,
   action_begfd,
   action_begstr,
   action_begtoken,
   action_doredir,
   action_endtoken,
   action_error1,
   action_error2,
   action_error3,
   action_error4,
   action_fdigit,
   action_fnchar,
   action_incr,
   action_nofd,
   action_redirfile,
   action_setfd,
   action_stop,
};
  
#if defined(FSMDEBUG) 
static char * decode_fsmactions[] = 
{ 
   "none",
   "begfd",
   "begstr",
   "begtoken",
   "doredir",
   "endtoken",
   "error1",
   "error2",
   "error3",
   "error4",
   "fdigit",
   "fnchar",
   "incr",
   "nofd",
   "redirfile",
   "setfd",
   "stop",
};
#endif
 
#define FSMACTIONS 17
#define TYPE_FSMACTIONS unsigned char
#define ACTMAX 5
  
struct xition 
{ 
   TYPE_FSMSTATES nustate; 
   TYPE_FSMACTIONS actions[ACTMAX]; 
}; 
  
static struct xition navigate[FSMSTATES][FSMINPUTS] = 
{
   [state_white] = 
      {
         [input_white] =     { state_white,      { action_none, 0 } },
         [input_end] =       { state_white,      { action_stop, 0 } },
         [input_any] =       { state_token,      { action_begtoken, action_incr, 0 } },
         [input_digit] =     { state_fd,         { action_begfd, action_fdigit, 0 } },
         [input_redir] =     { state_redir,      { action_doredir, 0 } },
         [input_esc] =       { state_tokesc,     { action_begtoken, 0 } },
         [input_dq] =        { state_dqs1,       { action_begstr, action_begtoken, 0 } },
         [input_sq] =        { state_sqs1,       { action_begstr, action_begtoken, 0 } },
      },
   [state_token] = 
      {
         [input_white] =     { state_white,      { action_endtoken, 0 } },
         [input_end] =       { state_token,      { action_endtoken, action_stop, 0 } },
         [input_any] =       { state_token,      { action_incr, 0 } },
         [input_digit] =     { state_token,      { action_incr, 0 } },
         [input_redir] =     { state_redir,      { action_endtoken, action_doredir, 0 } },
         [input_esc] =       { state_tokesc,     { action_none, 0 } },
         [input_dq] =        { state_dqs1,       { action_begstr, 0 } },
         [input_sq] =        { state_sqs1,       { action_begstr, 0 } },
      },
   [state_tokesc] = 
      {
         [input_end] =       { state_tokesc,     { action_error1, 0 } },
         [input_white] =     { state_token,      { action_incr, 0 } },
         [input_any] =       { state_token,      { action_incr, 0 } },
         [input_digit] =     { state_token,      { action_incr, 0 } },
         [input_redir] =     { state_token,      { action_incr, 0 } },
         [input_esc] =       { state_token,      { action_incr, 0 } },
         [input_dq] =        { state_token,      { action_incr, 0 } },
         [input_sq] =        { state_token,      { action_incr, 0 } },
      },
   [state_dqs1] = 
      {
         [input_end] =       { state_dqs1,       { action_error2, 0 } },
         [input_white] =     { state_dqs1,       { action_incr, 0 } },
         [input_any] =       { state_dqs1,       { action_incr, 0 } },
         [input_digit] =     { state_dqs1,       { action_incr, 0 } },
         [input_redir] =     { state_dqs1,       { action_incr, 0 } },
         [input_sq] =        { state_dqs1,       { action_incr, 0 } },
         [input_esc] =       { state_dqsx,       { action_none, 0 } },
         [input_dq] =        { state_token,      { action_none, 0 } },
      },
   [state_dqsx] = 
      {
         [input_end] =       { state_dqsx,       { action_error1, 0 } },
         [input_white] =     { state_dqs1,       { action_incr, 0 } },
         [input_any] =       { state_dqs1,       { action_incr, 0 } },
         [input_digit] =     { state_dqs1,       { action_incr, 0 } },
         [input_redir] =     { state_dqs1,       { action_incr, 0 } },
         [input_esc] =       { state_dqs1,       { action_incr, 0 } },
         [input_dq] =        { state_dqs1,       { action_incr, 0 } },
         [input_sq] =        { state_dqs1,       { action_incr, 0 } },
      },
   [state_sqs1] = 
      {
         [input_end] =       { state_sqs1,       { action_error2, 0 } },
         [input_white] =     { state_sqs1,       { action_incr, 0 } },
         [input_any] =       { state_sqs1,       { action_incr, 0 } },
         [input_digit] =     { state_sqs1,       { action_incr, 0 } },
         [input_redir] =     { state_sqs1,       { action_incr, 0 } },
         [input_dq] =        { state_sqs1,       { action_incr, 0 } },
         [input_esc] =       { state_sqs1,       { action_incr, 0 } },
         [input_sq] =        { state_token,      { action_none, 0 } },
      },
   [state_fd] = 
      {
         [input_digit] =     { state_fd,         { action_fdigit, 0 } },
         [input_end] =       { state_fd,         { action_nofd, action_endtoken, action_stop, 0 } },
         [input_white] =     { state_fdwhite,    { action_none, 0 } },
         [input_redir] =     { state_redir,      { action_doredir, action_setfd, 0 } },
         [input_any] =       { state_token,      { action_nofd, action_incr, 0 } },
         [input_esc] =       { state_tokesc,     { action_nofd, 0 } },
         [input_dq] =        { state_dqs1,       { action_nofd, action_begstr, 0 } },
         [input_sq] =        { state_sqs1,       { action_nofd, action_begstr, 0 } },
      },
   [state_fdwhite] = 
      {
         [input_white] =     { state_fdwhite,    { action_none, 0 } },
         [input_end] =       { state_fdwhite,    { action_nofd, action_endtoken, action_stop, 0 } },
         [input_redir] =     { state_redir,      { action_doredir, action_setfd, 0 } },
         [input_digit] =     { state_fd,         { action_nofd, action_endtoken, action_begfd, action_fdigit, 0 } },
         [input_any] =       { state_token,      { action_nofd, action_endtoken, action_begtoken, action_incr, 0 } },
         [input_esc] =       { state_tokesc,     { action_nofd, action_endtoken, action_begtoken, 0 } },
         [input_dq] =        { state_dqs1,       { action_nofd, action_endtoken, action_begtoken, action_begstr, 0 } },
         [input_sq] =        { state_sqs1,       { action_nofd, action_endtoken, action_begtoken, action_begstr, 0 } },
      },
   [state_redir] = 
      {
         [input_end] =       { state_redir,      { action_error3, 0 } },
         [input_white] =     { state_redir,      { action_none, 0 } },
         [input_redir] =     { state_redir,      { action_error4, 0 } },
         [input_any] =       { state_fname,      { action_fnchar, 0 } },
         [input_digit] =     { state_fname,      { action_fnchar, 0 } },
         [input_esc] =       { state_fnesc,      { action_none, 0 } },
         [input_dq] =        { state_dqfn,       { action_begstr, 0 } },
         [input_sq] =        { state_sqfn,       { action_begstr, 0 } },
      },
   [state_fname] = 
      {
         [input_end] =       { state_fname,      { action_redirfile, action_stop, 0 } },
         [input_white] =     { state_white,      { action_redirfile, 0 } },
         [input_any] =       { state_fname,      { action_fnchar, 0 } },
         [input_digit] =     { state_fname,      { action_fnchar, 0 } },
         [input_esc] =       { state_fnesc,      { action_none, 0 } },
         [input_dq] =        { state_dqfn,       { action_begstr, 0 } },
         [input_sq] =        { state_sqfn,       { action_begstr, 0 } },
      },
   [state_fnesc] = 
      {
         [input_end] =       { state_fnesc,      { action_error1, 0 } },
         [input_white] =     { state_fname,      { action_fnchar, 0 } },
         [input_any] =       { state_fname,      { action_fnchar, 0 } },
         [input_digit] =     { state_fname,      { action_fnchar, 0 } },
         [input_redir] =     { state_fname,      { action_fnchar, 0 } },
         [input_esc] =       { state_fname,      { action_fnchar, 0 } },
         [input_dq] =        { state_fname,      { action_fnchar, 0 } },
         [input_sq] =        { state_fname,      { action_fnchar, 0 } },
      },
   [state_dqfn] = 
      {
         [input_end] =       { state_dqfn,       { action_error2, 0 } },
         [input_white] =     { state_dqfn,       { action_fnchar, 0 } },
         [input_any] =       { state_dqfn,       { action_fnchar, 0 } },
         [input_digit] =     { state_dqfn,       { action_fnchar, 0 } },
         [input_redir] =     { state_dqfn,       { action_fnchar, 0 } },
         [input_sq] =        { state_dqfn,       { action_fnchar, 0 } },
         [input_esc] =       { state_dqfx,       { action_none, 0 } },
         [input_dq] =        { state_fname,      { action_none, 0 } },
      },
   [state_dqfx] = 
      {
         [input_end] =       { state_dqfx,       { action_error1, 0 } },
         [input_white] =     { state_dqfn,       { action_fnchar, 0 } },
         [input_any] =       { state_dqfn,       { action_fnchar, 0 } },
         [input_digit] =     { state_dqfn,       { action_fnchar, 0 } },
         [input_redir] =     { state_dqfn,       { action_fnchar, 0 } },
         [input_esc] =       { state_dqfn,       { action_fnchar, 0 } },
         [input_dq] =        { state_dqfn,       { action_fnchar, 0 } },
         [input_sq] =        { state_dqfn,       { action_fnchar, 0 } },
      },
   [state_sqfn] = 
      {
         [input_end] =       { state_sqfn,       { action_error2, 0 } },
         [input_white] =     { state_sqfn,       { action_fnchar, 0 } },
         [input_any] =       { state_sqfn,       { action_fnchar, 0 } },
         [input_digit] =     { state_sqfn,       { action_fnchar, 0 } },
         [input_redir] =     { state_sqfn,       { action_fnchar, 0 } },
         [input_dq] =        { state_sqfn,       { action_fnchar, 0 } },
         [input_esc] =       { state_sqfn,       { action_fnchar, 0 } },
         [input_sq] =        { state_fname,      { action_none, 0 } },
      }, 
}; 
