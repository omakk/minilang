CC = gcc
CFLAGS =  -Wall -Wextra -g -ansi -pedantic

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

SRCS = typecheck.c symbol.c pretty.c ast.c y.tab.c lex.yy.c main.c
OBJS = $(SRCS:.c=.o)
MAIN = minilang

all: $(MAIN)
	@echo minilang compiler compilation complete.

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN) $(lib)

y.tab.c: $(MAIN).y
	bison --yacc --defines $(MAIN).y

lex.yy.c: $(MAIN).l
	flex $(MAIN).l

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h minilang; rm -f ../*.log; rm -f ../*.pretty.min ../*.symbol.txt
