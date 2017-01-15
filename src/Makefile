CC = gcc

CFLAGS = -Wall -g -ansi -pedantic

default: minilang

minilang: y.tab.o lex.yy.o main.o
	$(CC) $(CFLAGS) y.tab.o lex.yy.o main.o -o minilang -ll

y.tab.c: minilang.y
	bison --yacc --defines minilang.y

lex.yy.c: minilang.l
	flex minilang.l

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o lex.yy.c y.tab.c y.tab.h minilang
