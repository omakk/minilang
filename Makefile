export DEBUG ?= 0
export TOPDIR=$(shell pwd)

all:
	$(MAKE) -C src
	@echo Compilation complete.

test:
	./test.sh

clean:
	rm -f *.log *.pretty.min *.symbol.txt
	$(MAKE) -C src clean
