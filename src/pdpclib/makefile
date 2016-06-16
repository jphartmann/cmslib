LIB:=fplpdp

CSRC:=${basename ${wildcard *.c}}
CFLAGS:=-I.
include ../cms390.makefile

${@TEXT}: ../include/*.h

${GENDIR}/time.s: ../include/sys/time.h
