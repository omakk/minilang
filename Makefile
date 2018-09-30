DEBUG ?= 0
TOPDIR := $(shell pwd)
export

all:
	$(MAKE) -C src
	@echo Compilation complete.

test:
	./test.sh

clean:
	rm -f *.log *.pretty.min *.symbol
	$(MAKE) -C src clean
