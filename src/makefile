# Build all stuff to upload.
.PHONY: default allclean all

TAR:=../../cmslib-exec/fplgcc.tar

BELOW:=cmsbase cmslib glibc pdpclib pipeline

default:
	@echo Doing nothing.  Specify clean or all.

clean:
	( for d in ${BELOW}; do make -C $$d clean; done )

all:
	( for d in ${BELOW}; do make -C $$d || break; done )

all: tar

tar: ${TAR}

SAMPS:=fplgcc.makefile minimal/minimal.c minimal/makefile
SP:=${addprefix samples/,${SAMPS}}
${TAR}: include/*.h include/sys/*.h include/netinet/*.h ${SP}
	tar -cf ${TAR} include -C samples ${SAMPS} include
