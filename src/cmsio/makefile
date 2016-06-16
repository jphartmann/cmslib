LIB:=fplcmsio

CSRC:=${basename ${wildcard *.c}}
CFLAGS:=-I.
H:=${wildcard *.h}

include ../cms390.makefile

${GENDIR}/rusage.s: ../include/sys/resource.h
