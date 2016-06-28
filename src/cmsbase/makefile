# Basic	C/390  runtime.	These  routines  will start a C program, but
# provide	no  library  function  other	than	a	few  low  level  CMS
# interfaces.	 If  you  are	looking	to  run library-less C code as a
# subroutine, this is all you need, perhaps even more than you need.

# To	call	a	C subroutine, sau inflate(), all you need is to set up a
# stack frame.  stack390 is the one-stop shopping for that.

LIB:=fplcbase
ASMOPTS:=rent,

ASMSRC:=run390 stack390 low390 csl390 stor390 tod390 subc390 fplgcc
# cmspipe
COPY:=run390.copy

CSRC:=go390 const onosj

include ../cms390.makefile

install:
	cp -p makefp.rexx ${HOME}/bin

${@TEXT}: run390.copy

$G/go390.s: scanarg.c args.c

check:
	make -C test check

getfsm:
	( echo cd john.100 ; echo get args.c )| ftp cphart

