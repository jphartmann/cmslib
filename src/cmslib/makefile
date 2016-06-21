LIB:=fplcmslib

CSRC:=${basename ${wildcard *.c}}
CFLAGS:=-I.

include ../cms390.makefile

${GENDIR}/rusage.s: ../include/sys/resource.h
${GENDIR}/csldec.s: csldecode.h
