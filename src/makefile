# Build all stuff to upload.
.PHONY: default allclean all

BELOW:=cmsbase cmslib glibc pdpclib

default:
	@echo Doing nothing.

clean:
	( for d in ${BELOW}; do make -C $$d clean; done )

all:
	( for d in ${BELOW}; do make -C $$d || break; done )
