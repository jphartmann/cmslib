# Makefile to generate assembler and C modules for use on CMS.  Include
# it from each make file in the directories below it.

# This makefile does not generate native executables.

# Before including this file, the calling makefile must define these
# variables:

# LIB 		The file name of the stacked TEXT deck to be uploaded

# ASMSRC 	The  file  names	(no  extension)  of	assembler modules to
#				include.  Omit if no assembler in directory.

# CSRC		The  file  names	(no  extension)  of the C language source
#				files to include.  Omit if no C source.

# COPY		COPY files and MACRO FILES to be used in assembly.

# H			Additional header files that the C files depend on.

# Additional  optional	variables that the calling makefile may need to
# define:

# BASE		The  directory that contains this makefile.	If the current
#				directory	is   deeper,  BASE  must  be	set  accordingly.
#				Specifically,	 ${BASE}/include	 and	${BASE}/macros  must
#				exist.

# MACROBASE The directory that contains the VM macro libraries (DMSGPI, etc.)

# Environment variables that must be set before doing make:

# VMHOST 	The  host  name  of	your	VM system.	You need to set up a
#				.netrc file to allow ftp.

# It	may  be convenient to import these variables from the environment
# instead of specifying them in all makefiles

# If	there  is  no	assembler  on	the workstation, the C programs are
# compiled and converted to ASSEBMLE files; and the ASSEMBLE, COPY, and
# MACRO files are packaged for upload.  If an assembler is present, the
# files	are assembled and the TEXT decks are combined for upload.  Use
# FPLTLGEN on CMS to create a TXTLIB.	(Do not create a TXTLIB from the
# stakced file; it will have one member only.)

# Intermediary files are stored in this directory
export GENDIR:=z
G:=${GENDIR}

.SUFFIXES: .text .assemble .listing .c .s
.PHONY: all asms copy deck lib cleanlib main

ifndef BASE
 BASE:=..
endif

# No Bourne shell, please and thank you.
SHELL:=${shell which bash}
ifndef SHELL
NOTOK=1
all:
	@echo Please install the bash shell.
endif

G2A:=${shell which gas2asm}
ifndef G2A
NOTOK=1
all:
	@echo Please install the bash gas2asm from https://github.com/jphartmann/gas2asm.git
endif

# We assume that you have the login information in .netrc
ifndef VMHOST
NOTOK=1
all:
	@echo Please define the VMHOST environment variable to contain the host name or IP address of your VM system.
endif

HLASM:=${shell which hlasm}
MACHINE:=${shell uname -m}

ifneq "MACHINE" "s390x"
 GCCBASE:=PATH=${HOME}/x-tools/s390x-ibm-linux-gnu/bin
 CC:=${GCCBASE} s390x-ibm-linux-gnu-cc
# Else no need for the normal PATH; the compiler is self contained.
endif

CFLAGS+=-nostdinc -I. -I${BASE}/include
CFLAGS+=-D__ZVM__ -D__CMS__ -U__gnu_linux__
CFLAGS+=-m31 -march=g5 -fno-use-linker-plugin
CFLAGS+=-fverbose-asm -g -Wall -Werror -Wno-pointer-sign
EFLAGS:=-fexec-charset=IBM-1047 -Wno-format

# The  built-in  shell command in sh (which is often ash/dash) does not
# support -e reliably.	We do this here, but using /bin/echo works well
# with -e.

STAGE=${BASE}/../stage

FTP:=echo site fix 80; echo lcd ${STAGE}; echo put
UPDECK:=(echo bin; ${FTP} @${LIB}.text ${LIB}.text) \
	|ftp ${VMHOST}
UPASMS:=(${FTP}  @${LIB}.assemble ${LIB}.assemble) \
	|ftp ${VMHOST}
UPCOPY:=(${FTP}  @${LIB}.copy ${LIB}.copy) \
	|ftp ${VMHOST}

ifndef MACROBASE
 MACROBASE:=${HOME}/fpl/ebcdic/macros
endif

ASMOPTS:=${ASMOPTS}term
ASMFLAGS:= \
 --noprintoptions --macrobase ${MACROBASE} \
 --options ${ASMOPTS} --maxmessage 10 -o ${GENDIR} \
 --macropath .:${BASE}/macros:dmsgpi.maclib:dmsom.maclib:fplgpi.maclib:fplom.maclib

# Figure out what to do.

# For assemble files
#	 List of source files
@ASMN:=${ASMSRC}} ${addprefix $G/,${CSRC}}
# What needs to be redone when include files change
@S:=${addsuffix .s,${addprefix $G/,${CSRC}}}
#	 For the stacked list
@ASMA:=${addsuffix .assemble, ${ASMSRC}} \
	${addprefix $G/,${addsuffix .assemble,${CSRC}}}
#	 For the assembled text decks
@TEXT:=${addprefix $G/,${addsuffix .text,${ASMSRC} ${CSRC}}}

ifndef NOTOK
ifdef HLASM
 ${info Using local assembler: ${HLASM}}
# Assemble locally
ifdef @TEXT
all: ${STAGE}/@${LIB}.text

${STAGE}/@${LIB}.text: ${@TEXT} | ${STAGE}
	cat ${@TEXT} >${STAGE}/@${LIB}.text
	${UPDECK}

${@TEXT}: ${BASE}/macros/*
endif
# Just create the ASSEMBLE files for upload
endif
else
 ${error make suppressed due to errors reported above.}
all:
	;
endif

# If	there  is  no	workstation  assembler,  this  becomes the default
# target.	On  VM,	assemble  with  the	BATCH  option or spit out the
# individual files.
ifdef ASMA
all: @${LIB}.assemble

@${LIB}.assemble: ${@ASMA} | ${STAGE}
	cat ${@ASMA} >${STAGE}/@${LIB}.assemble
	${UPASMS}
endif

ifdef COPY
all: ${STAGE}/@${LIB}.copy

${STAGE}/@${LIB}.copy: ${COPY} | ${STAGE}
# We want both the prototypes and the member names in uppercase.
# ^^ to uppercase is no doubt a recent Bash concept.
	( for n in ${COPY} ; do \
		fn=$${n%.*}; fnu=$${fn^^}; \
		echo '*COPY' $${fnu} ; cat $$n; done ) >${STAGE}/@${LIB}.copy
	${UPCOPY}
endif

clean:
	rm -f core $G/*

${@S}: ${BASE}/include/*.h
ifdef H
${@S}: $H
endif

# Patterns and recipes

# The  first  compile  is a dry run to catch printf trouble; the second
# one is for real
$G/%.s: %.c | $G
	${CC} -S -o /dev/null ${CFLAGS} $<
	${CC} -S -o $@ ${CFLAGS} ${EFLAGS} $<

$G/%.assemble: $G/%.s
	gas2asm < $< | asmxpnd > $@

# Compile .s converted
$G/%.text: $G/%.assemble
	hlasm ${ASMFLAGS} $< || (rm -f $@; exit 1)

# Compile handwritten assembler
$G/%.text: %.assemble
	hlasm ${ASMFLAGS} $* || (rm -f $@; exit 1)

$G:
	mkdir -p $G

${STAGE}:
	mkdir -p ${STAGE}
