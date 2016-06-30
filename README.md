# cmslib
Support for cross compiled C to native CMS and a C library.

Except for the added `makefile` an unmodified version of `zlib-1.2.8`
is cross compiled to `zlib.txtlib`.

Required utilities and packages
-------------------------------

[`gas2asm`] (https://github.com/jphartmann/gas2asm) converts the -S
output from gcc to HLASM input.  Required.

[`txtlib`] (https://github.com/jphartmann/CMS-TXTLIB) generates the
target libraries when object decks can be created at the workstation.
OPtional.
