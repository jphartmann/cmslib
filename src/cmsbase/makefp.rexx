/* Build function package.                                           */
/*                                John Hartmann 27 Jun 2016 11:28:28 */
Signal on novalue

/*********************************************************************/
/* This  program  is  equivalent in that it generates an entry point */
/* table.                                                            */
/*                                                                   */
/* But  it  also  generates  the top level procedure and the program */
/* descriptors for the contents of the fileter package.              */
/*                                                                   */
/* The input format is slightly different from a n EPTABLE file.     */
/*                                                                   */
/* Options  are  keyword=value pairs separated by white space or new */
/* line.  The name= keyword must be first.                           */
/*                                                                   */
/* name=       Program name for the EP table.                        */
/* code=       C function to execute.  Max 8 chars.                  */
/* min=        Minimum abbreviation (third word).                    */
/* From PIPDESC:                                                     */
/* commit=     Commit level.  Default is -2.                         */
/* first=                                                            */
/* args=                                                             */
/* streams=                                                          */
/*********************************************************************/

parse arg infile outfile .

If outfile = ''
   Then call exit "Specify input and output file names."

ix = 0
rv = 0
extrns = ''

/* Position of these is important.  Add at end                       */
/* .        1    2    3   4      5     6    7                        */
keywords = 'NAME CODE MIN COMMIT FIRST ARGS STREAMS'

call sysfiledelete outfile
call out '* Generated' date() time(),,
   '  COPY    PGMID',,
   'gccfilts modbeg FREETYPE=NONE,amode=31',,
   ' extproc (&pgmid.gccin,STACK)',,
   'GOGCC    PROC  SAREA=STACK,ENTRY=NO,WORKBASE=R10',,
   'GBLPTRS  DS    2F             cmslibglobal and cmsthreadglobal',,
   ' FLAGDEF DIDCOMMIT',,
   'BUF1     PIPBFR 0',,
   'TOKEN    DS    D',,
   "PARMS    DS    6F'0'          R0 - 5 for scanning",,
   ' pbegin',,
   ' stm 1,5,parms+4',,
   ' pipcall gccin',,
   ' pexit rc=(r15)',,
   'eptab loctr',,
   ' pipept pipept,entry=YES,secondary=NO',,
   'gccfilts loctr'

call init
do line = 1 while lines(infile) > 0
   todo = linein(infile)
   orig = todo
   do while todo \= ''
      parse var todo kwd '=' value todo
      kwd = translate(strip(kwd))
      If value = ''
         Then call err 'Equal sign or value missing for "'kwd'".'
      If kwds = '' & kwd \= 'NAME'
         Then call err 'Expecting NAME=.  Found' kwd'.'
         else call proc
   end
end
If kwds = ''
   Then exit rv
call dump
call out ' procend GOGCC',,
   'eptab loctr',,
   ' PIPEPTED ',,
   ' modend print=gen'
say ix 'entries processed.'
exit rv

/*********************************************************************/
/* Prepare for a new entry.                                          */
/*********************************************************************/

init:
fail = 0
kwds = ''
kwd. = ''
kwd.4 = -2                            /* Default commit              */
return

/*********************************************************************/
/* Process a keyword/value pair.                                     */
/*********************************************************************/

proc:
kwix = wordpos(kwd, keywords)
If kwix = 0
   Then
      Do
         call err 'Keyword "'kwd'" is not valid.'
         return
      End
if kwd = 'NAME' & ix > 0
   Then call dump

ok = 1
signal value '@'kwd                     /* Validate                    */
back:
If ok \= 1
   Then return
kwds = kwds kwd
kwd.kwix = value
return

/*********************************************************************/
/* Validation routines                                               */
/*********************************************************************/

@NAME:
value = translate(value);
kwd.3 = min(length(value), 8)
ix = ix + 1
signal back

@CODE:
if length(value) > 8
   then call err 'C function name "'value'"is longer than 8.  It will be mangled by gas2asm.'
signal back

@MIN:
call cknum 1, 8
If \ok | fail
   Then return
If value <= length(kwd.1)
   Then return
call warn 'Minimum length' value 'is reduced to length of name:' length(kwd.1)
value = length(kwd.1)
signal back

@COMMIT:
call cknum -999999999, 999999999
If ok & value > 0
   Then call warn 'Positive commit level' value 'is unusual.'
signal back

@FIRST:
call yesno
signal back

@ARGS:
call yesno
signal back

@STREAMS:
call cknum 1, 999999999
signal back

cknum:
Select
   When \datatype(value, 'Whole')
      Then call err kwd'='value 'is not a whole number.'
   when value < arg(1)
      then call err kwd'='value 'is too small.  Minimum is' arg(1)
   when value > arg(2)
      then call err kwd'='value 'is too large.  Maximum is' arg(2)
   otherwise
end
return

yesno:
value = translate(value);
If wordpos(value, 'YES NO') > 0
   Then return
call err kwd=value 'is not YES or NO.'
return


/*********************************************************************/
/* Met a name keyword.  Create program descriptor.                   */
/*********************************************************************/

dump:
pn = 'filt'right(ix, 4, 0)
call out cont(pn 'pipdesc FP=NO,TYPE=FILTER,BUFFER=BUF1,'),,
   cont(contd('entry=NO,RUN_AUTHORISED=NO,commit='kwd.4)',')
do i = 5 to words(keywords)
   If kwd.i = ''
      Then iterate
   call out cont(contd(word(keywords, i)'='kwd.i','))
end
call out contd('syntax=(=0,parms,:0,'kwd.2',=0,0,STOP)'),,
   'eptab loctr',,
   ' pipepten' kwd.1','pn',min='kwd.3,,
   'gccfilts loctr'
If wordpos(kwd.2, extrns) = 0
   Then
      Do
         call out ' extrn' kwd.2
         extrns = extrns kwd.2
      End
call init
return

/*********************************************************************/
/* Generate a continued statement                                    */
/*********************************************************************/

cont:
return left(arg(1), 71)'+'

contd:
return left(' ', 14) arg(1)

/*********************************************************************/
/* Subroutines                                                       */
/*********************************************************************/

out:
do ! = 1 to arg()
   call lineout outfile, left(arg(!), 80)
end
return

err:
say 'From line' right(line, 3)': ' orig
say 'Warning: ' arg(1)
return

err:
say 'From line' right(line, 3)': ' orig
say 'Error: ' arg(1)
rv = max(rv, 16)
ok = 0                                /* Set abort flag              */
fail = 1
return

exit:
say arg(1)
exit 20
