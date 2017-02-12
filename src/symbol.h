#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"

#define HASH_SIZE 317

typedef struct SYMBOL {
        char            *name;
        char            *type;
        int             value;
        struct SYMBOL   *next;
} SYMBOL;

typedef struct SYM_TABLE {
        SYMBOL              *table[HASH_SIZE];
        struct SYM_TABLE    *next;
} SYM_TABLE;

int sym_hash(char *s)
{
        unsigned int hash = 0;
        while (*s) hash = (hash << 1) + *s++;
        return hash % HASH_SIZE;
}

SYM_TABLE *init_sym_table();

SYMBOL *put_sym(SYM_TABLE *t, char *name, char *type);
SYMBOL *get_sym(SYM_TABLE *t, char *name);

int sym_defined(SYM_TABLE *t, char *name);

void make_sym_table(ASTNode *ast);
void sym_table_from_ast(SYM_TABLE *t, ASTNode *ast);

SYM_TABLE *sym_table;

#endif
