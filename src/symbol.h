#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include "ast.h"

#define HASH_SIZE 317

typedef struct SYMBOL {
        char            *name;
        const char      *type;
        struct SYMBOL   *next;
} SYMBOL;

typedef struct SYM_TABLE {
        SYMBOL              *table[HASH_SIZE];
        struct SYM_TABLE    *next;
} SYM_TABLE;

SYM_TABLE *init_sym_table();

SYMBOL *put_sym(SYM_TABLE *t, char *name, const char *type);
SYMBOL *get_sym(SYM_TABLE *t, char *name);

int sym_defined(SYM_TABLE *t, char *name);

void make_sym_table(FILE *f, ASTNode *ast);
void sym_table_from_ast(SYM_TABLE *t, ASTNode *ast);
void report_sym_error(const char *msg, char *name, int lineno);
void print_sym_table(FILE *f, SYM_TABLE *t);

SYM_TABLE *sym_table;

#endif
