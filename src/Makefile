CC = gcc
CFLAGS =  -w -g -ansi -pedantic

DEBUG ?= 0
ifeq ($(DEBUG), 1)
		CFLAGS += -DDEBUG
endif

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	lib = -lfl
endif
ifeq ($(UNAME), Darwin)
	lib = -ll
endif

default: minilang

minilang: y.tab.o lex.yy.o main.o
	$(CC) $(CFLAGS) y.tab.o lex.yy.o main.o -o minilang $(lib)

y.tab.c: minilang.y
	bison --yacc --defines minilang.y

lex.yy.c: minilang.l
	flex minilang.l

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h minilang; rm -f ../*.log