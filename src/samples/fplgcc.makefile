# Compile a program and upload the assemble file(s)

# Makefile	to  generate  assembler  from  C  programs  for use on CMS.
# Include it from each make file in the directories below it.

# This makefile does not generate native executables.

# Before including this file, the calling makefile must define these
# variables:

# LIB 		The file name of the stacked ASSEMBLE deck to be uploaded.

# CSRC		The  file  names	(no  extension)  of the C language source
#				files to include.

# H			Additional	header  files	that the C files depend on.  The
#				include	directory  is	assumed;  you	need not specify its
#				contents.

# Additional  optional	variables that the calling makefile may need to
# define:

# BASE		The  directory that contains this makefile.	The default is
#				..  (the  parent	directory).   If the current directory is
#				deeper,	 BASE  must  be  set  accordingly.	 Specifically,
#				${BASE}/include must exist.

# Environment variables that must be set before doing make:

# VMHOST 	The  host  name  of	your	VM system.	You need to set up a
#				.netrc file to allow ftp.

# It	may  be convenient to import these variables from the environment
# instead of specifying them in all makefiles

.SUFFIXES: .text .assemble .listing .c .s .eptable

# Intermediary files are stored in this directory
ifndef GENDIR
 export GENDIR:=z
endif

G:=${GENDIR}

# Where this makefile is relative to the makefile that includes it
ifndef BASE
 BASE:=..
endif

# No Bourne shell, please and thank you.
SHELL:=${shell which bash}
ifndef SHELL
NOTOK=1
${info Please install the bash shell.}
endif

@G2A:=${shell which gas2asm}
ifndef @G2A
NOTOK=1
${info Please install gas2asm from https://github.com/jphartmann/gas2asm.git}
endif

@MACHINE:=${shell uname -m}
ifneq "@MACHINE" "s390x"
 @GCCBASE:=PATH=${HOME}/x-tools/s390x-ibm-linux-gnu/bin
 CC:=${@GCCBASE} s390x-ibm-linux-gnu-cc
# Else no need for the normal PATH; the compiler is self contained.
endif

CFLAGS+=-nostdinc -I. -I${BASE}/include
CFLAGS+=-D__ZVM__ -D__CMS__ -U__gnu_linux__
CFLAGS+=-m31 -march=g5 -fno-use-linker-plugin
CFLAGS+=-fverbose-asm -g -Wall -Werror -Wno-pointer-sign
EFLAGS:=-fexec-charset=IBM-1047 -Wno-format -O

A:=${addsuffix .assemble,${CSRC}}
ASMS:=${addprefix $G/,$A}

ifdef NOTOK
${error make suppressed due to errors reported above.}
endif

all: ${ASMS}
	(cd $G && cat $A >@${LIB}.assemble)
P:=echo put @${LIB}.assemble ${LIB}.assemble;

ifdef EPTABLE
E:=${EPTABLE}.assemble
all: $G/$E
P+=echo put $E;
endif

nothing:
	@echo Doing nothing.

clean:
	rm -f core $G/*

up: all
	(echo site fix 80; echo lcd $G; $P echo quit) \
	|ftp ${VMHOST}

# Patterns and recipes

# The  first  compile  is a dry run to catch printf trouble; the second
# one is for real
$G/%.s: %.c | $G
	${CC} -S -o /dev/null ${CFLAGS} $<
	${CC} -S -o $@ ${CFLAGS} ${EFLAGS} $<

$G/%.assemble: $G/%.s
	gas2asm < $< | asmxpnd > $@

$G:
	mkdir -p $G

$G/%.assemble: %.eptable
	rexx makefp.rexx $< $@
