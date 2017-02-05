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

minilang: pretty.o ast.o y.tab.o lex.yy.o main.o
	$(CC) $(CFLAGS) pretty.o ast.o y.tab.o lex.yy.o main.o -o minilang $(lib)

y.tab.c: minilang.y
	bison --yacc --defines minilang.y

lex.yy.c: minilang.l
	flex minilang.l

ast.o: ast.c
	$(CC) $(CFLAGS) -c ast.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

pretty.o: pretty.c
	$(CC) $(CFLAGS) -c pretty.c

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h minilang; rm -f ../*.log; rm -f ../*.pretty.min
