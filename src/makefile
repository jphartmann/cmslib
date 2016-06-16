# Build all stuff to upload.

BELOW:=cmsbase cmsio cmsnative cmsother glibc pdpclib

default:
	@echo Doing nothing.

BASE:=.

include cms390.makefile

clean:
	rm ${STAGE}/*
	( for d in $BELOW; do make -C $$d $MAKEFLAGS; done )
