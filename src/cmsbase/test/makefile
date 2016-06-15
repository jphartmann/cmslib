# Test driver module.  tscan is a shell script calling it
all: check

sarg: scanargmain.c ../scanarg.c ../args.c
	cc -o $@ $< -Wall -Werror -I..

tscan.out: sarg tscan makefile
	./tscan >tscan.out

check: tscan.out
	diff tscan.out tscan.ok
	@echo '>>> Test completed OK. <<<'

checkok:
	cp -p tscan.out tscan.ok
