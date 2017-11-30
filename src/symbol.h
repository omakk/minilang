#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include "ast.h"

#define HASH_SIZE 317

typedef struct SYMBOL {
        const char      *name;
        enum type        type;
        struct SYMBOL   *next;
} SYMBOL;

typedef struct SYM_TABLE {
        SYMBOL              *table[HASH_SIZE];
        struct SYM_TABLE    *next;
} SYM_TABLE;

SYM_TABLE *init_sym_table();

SYMBOL *put_sym(SYM_TABLE *t, const char *name, enum type type);
SYMBOL *get_sym(SYM_TABLE *t, const char *name);

int sym_defined(SYM_TABLE *t, const char *name);

void make_sym_table(FILE *f, ASTNode *ast);
void sym_table_from_ast(FILE *f, SYM_TABLE *t, ASTNode *ast);
void report_sym_error(const char *msg, const char *name, int lineno);

SYM_TABLE *sym_table;

#endif
