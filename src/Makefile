CC ?= gcc
CFLAGS=-Wall -Wextra -g -pedantic

INCLUDES = -I$(TOPDIR)/include
CFLAGS += $(INCLUDES)

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG
endif

UNAME := $(shell uname)
COMPILER := $(shell $(CC) -v 2>&1 | grep -E '(gcc|clang|LLVM) version' | grep -oE '(clang|gcc)')
ifeq ($(UNAME), Linux)
	LIBS = -lfl
    ifeq ($(COMPILER),clang)
		CFLAGS += -fblocks
		LIBS += -lBlocksRuntime
    endif
endif
ifeq ($(UNAME), Darwin)
	LIBS = -ll
    ifeq ($(COMPILER),clang)
		CFLAGS += -fblocks
    endif
endif

SRCS = typecheck.c symbol.c pretty.c ast.c y.tab.c lex.yy.c main.c
OBJS = $(SRCS:.c=.o)
OUTPUT_FILES = lex.yy.c y.tab.c y.tab.h $(MAIN).out $(OBJS)
MAIN = minilang

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN).out $(LIBS)

y.tab.c: $(MAIN).y
	bison --yacc --defines $(MAIN).y

lex.yy.c: $(MAIN).l
	flex $(MAIN).l

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUT_FILES)
