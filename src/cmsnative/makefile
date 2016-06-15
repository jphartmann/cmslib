# CMS specific low level library routines

LIB:=fplclib

CFLAGS:=-I.
CSRC:=${basename ${wildcard *.c}}

include ../cms390.makefile

${@TEXT}: ../include/*.h

${GENDIR}/csldec.text: csldecode.h
