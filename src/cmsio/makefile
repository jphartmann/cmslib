LIB:=fplcmsio

CSRC:=${basename ${wildcard *.c}}
CFLAGS:=-I.
H:=${wildcard *.h}

include ../cms390.makefile

${GENDIR}/stdiovp.text: fplpop.h
${GENDIR}/time.text: ../include/sys/time.h
${GENDIR}/rusage.text: ../include/sys/resource.h

