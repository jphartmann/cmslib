# Build all stuff to upload.
.PHONY: default allclean all

BELOW:=cmsbase cmsio cmsnative cmsother glibc pdpclib macro

default:
	@echo Doing nothing.

BASE:=.

include cms390.makefile

allclean:
	rm -f ${STAGE}/*
	( for d in ${BELOW}; do make -C $$d clean; done )

all:
	( for d in ${BELOW}; do make -C $$d ; done )

BIN:=${subst @,,${notdir ${wildcard ${STAGE}/*.text}}}
BINP:=${foreach file,${BIN},"; put @${file} ${file}"}
ASC:=${subst @,,${notdir ${wildcard ${STAGE}/*.copy}}}
ASC+=${subst @,,${notdir ${wildcard ${STAGE}/*.assemble}}}
ASCP:=${foreach file,${ASC},"; put @${file} ${file}"}

upload:
	@echo bin ${BIN} binp ${BINP} ascii ${ASC} ascp ${ASCP}


