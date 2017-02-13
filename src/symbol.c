#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"

int sym_hash(char *s)
{
        unsigned int hash = 0;
        while (*s) hash = (hash << 1) + *s++;
        return hash % HASH_SIZE;
}

SYM_TABLE *init_sym_table()
{
        int i;
        SYM_TABLE *t;
        t = malloc(sizeof(SYM_TABLE));
        for (i = 0; i < HASH_SIZE; i++)
                t->table[i] = NULL;
        t->next = NULL;
        return t;
}

SYMBOL *put_sym(SYM_TABLE *t, char *name, const char *type)
{
        int i = sym_hash(name);
        SYMBOL *s;
        
        for (s = t->table[i]; s; s = s->next)
                if  (strcmp(s->name, name) == 0) return s;
        
        s = malloc(sizeof(SYMBOL));
        s->name = name;
        s->type = type;
        s->next = t->table[i];
        t->table[i] = s;
        
        return s;
}

SYMBOL *get_sym(SYM_TABLE *t, char *name)
{
        int i = sym_hash(name);
        SYMBOL *s;
        
        for ( s = t->table[i]; s; s = s->next)
                if (strcmp(s->name, name) == 0) return s;
        
        if (t->next == NULL) return NULL;

        return get_sym(t->next, name);
}

int sym_defined (SYM_TABLE *t, char *name)
{
        int i = sym_hash(name);
        SYMBOL *s;

        for (s = t->table[i]; s; s = s->next)
                if (strcmp(s->name, name) == 0) return 1;

        if (t->next == NULL) return 0;

        return sym_defined(t->next, name);
}

void make_sym_table(FILE *f, ASTNode *ast)
{
        sym_table = malloc(sizeof(SYM_TABLE));
        sym_table_from_ast(sym_table, ast);
        print_sym_table(f, sym_table);
}

void report_sym_error(const char *msg, char *name, int lineno)
{
        fprintf(stderr, "INVALID: %s \"%s\"; line: %d\n", msg, name, lineno);
        exit(1);
}

void sym_table_from_ast(SYM_TABLE *t, ASTNode *ast)
{
        switch(ast->construct)
        {
                case CON_IDENT:
                        
                        if (!sym_defined(t, ast->val.idval))
                                report_sym_error("undeclared identifier", ast->val.idval, ast->lineno);
                        break;
                
                case CON_UOP_MINUS: sym_table_from_ast(t, ast->val.minusuop);       break;
                case CON_BOP_MUL:   sym_table_from_ast(t, ast->val.mulbop.left);
                                    sym_table_from_ast(t, ast->val.mulbop.right);   break;
                case CON_BOP_DIV:   sym_table_from_ast(t, ast->val.divbop.left);
                                    sym_table_from_ast(t, ast->val.divbop.right);   break;
                case CON_BOP_PLUS:  sym_table_from_ast(t, ast->val.plusbop.left);
                                    sym_table_from_ast(t, ast->val.plusbop.right);  break; 
                case CON_BOP_MINUS: sym_table_from_ast(t, ast->val.minusbop.left);
                                    sym_table_from_ast(t, ast->val.minusbop.right); break;
                case CON_PROGRAM:
                        if (ast->val.prog.dcls != NULL)
                                sym_table_from_ast(t, ast->val.prog.dcls);
                        if (ast->val.prog.stmts != NULL)
                                sym_table_from_ast(t, ast->val.prog.stmts);
                        break;
                case CON_DCLS:
                        sym_table_from_ast(t, ast->val.dcls.dcl);
                        if (ast->val.dcls.dcls != NULL)
                                sym_table_from_ast(t, ast->val.dcls.dcls);
                        break;
                case CON_STMTS:
                        sym_table_from_ast(t, ast->val.stmts.stmt);
                        if (ast->val.stmts.stmts != NULL)
                                sym_table_from_ast(t, ast->val.stmts.stmts);
                        break;
                case CON_READ:
                        if (!sym_defined(t, ast->val.readidval->val.idval))
                                report_sym_error("undeclared identifier", ast->val.idval, ast->lineno);
                        break;
                case CON_PRINT:
                        sym_table_from_ast(t, ast->val.printexp);
                        break;
                case CON_DECL:
                        if (sym_defined(t, ast->val.decl.id->val.idval)) {
                                /* Multiple declarations of the same variable found */
                                report_sym_error("multiple delcarations",
                                                  ast->val.decl.id->val.idval,
                                                  ast->lineno);
                        } else {
                                put_sym(t, ast->val.decl.id->val.idval, ast->val.decl.type);
                        }
                        break;
               
                case CON_ASSIGN:
                        if (!sym_defined(t, ast->val.assign.id->val.idval)) {
                                /* Cannot assign into undeclared variable */
                                report_sym_error("assignment of undeclared identifier",
                                                  ast->val.assign.id->val.idval,
                                                  ast->lineno);
                        }
                        break;
                case CON_IF:
                        sym_table_from_ast(t, ast->val.ifbranch.cond);
                        if (ast->val.ifbranch.if_body != NULL)
                                sym_table_from_ast(t, ast->val.ifbranch.if_body);
                        break;
               
                case CON_IF_ELSE:
                        sym_table_from_ast(t, ast->val.ifelsebranch.cond);
                        if (ast->val.ifelsebranch.if_body != NULL)
                                sym_table_from_ast(t, ast->val.ifelsebranch.if_body);
                        if (ast->val.ifelsebranch.else_body != NULL)
                                sym_table_from_ast(t, ast->val.ifelsebranch.else_body);
                        break;
               
                case CON_WHILE:
                        sym_table_from_ast(t, ast->val.whilebranch.cond);
                        if (ast->val.whilebranch.while_body != NULL)
                                sym_table_from_ast(t, ast->val.whilebranch.while_body);
                        break;
               
                default:
                        break;
        }
}

void print_sym_table(FILE *f, SYM_TABLE *t)
{
        int i;
        SYMBOL *s;

        for (i = 0; i < HASH_SIZE; i++) {
                for ( s = t->table[i]; s; s = s->next)
                        fprintf(f, "%s: %s\n", s->name, s->type);
        }
}
