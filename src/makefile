# Build all stuff to upload.
.PHONY: default allclean all

TAR:=../../cmslib-exec/fplgcc.tar

BELOW:=cmsbase cmslib glibc pdpclib

default:
	@echo Doing nothing.  Specify clean or all.

clean:
	( for d in ${BELOW}; do make -C $$d clean; done )

all:
	( for d in ${BELOW}; do make -C $$d || break; done )

all: tar

tar: ${TAR}

${TAR}: include/*.h include/sys/*.h include/netinet/*.h samples/fplgcc.makefile
	tar -cf ${TAR} include -C samples fplgcc.makefile
