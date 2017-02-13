#include <stdlib.h>
#include <string.h>
#include "symbol.h"

SYM_TABLE *init_sym_table()
{
        SYM_TABLE *t;
        t = malloc(sizeof(SYM_TABLE));
        for (int i = 0; i < HASH_SIZE; i++)
                t->table[i] = NULL;
        t->next = NULL;
        return t;
}

SYMBOL *put_sym(SYM_TABLE *t, char *name, char *type)
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

void make_sym_table(ASTNode *ast)
{
        sym_table = malloc(sizeof(SYM_TABLE));
        sym_table_from_ast(sym_table, ast);
}

void sym_table_from_ast(SYM_TABLE *t, ASTNode *ast)
{
        switch(ast->construct)
        {
                case CON_IDENT:
                        
                        if (!sym_defined(t, ast->val.idval))
                                // @Error
                                ;
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
                        if (ast->val.prog.dcls)
                                sym_table_from_ast(t, ast->val.prog.dcls);
                        if (ast->val.prog.stmts)
                                sym_table_from_ast(t, ast->val.prog.stmts);
                        break;
                case CON_DCLS:
                        sym_table_from_ast(t, ast->val.dcls.dcl);
                        if (ast->val.dcls.dcls)
                                sym_table_from_ast(t, ast->val.dcls.dcls);
                        break;
                case CON_STMTS:
                        sym_table_from_ast(t, ast->val.stmts.stmt);
                        if (ast->val.stmts.stmts)
                                sym_table_from_ast(t, ast->val.stmts.stmts);
                        break;
                case CON_READ:
                        if (!sym_defined(t, ast->val.readidval->val.idval))
                                // @Error
                        break;
                case CON_PRINT:
                        sym_table_from_ast(t, ast->val.printexp);
                        break;
                case CON_DECL:
                        if (sym_defined(t, ast->val.decl.id->val.idval))
                                // Declaring a variable that has already been declared
                                // @Error
                                ;
                        else
                                put_sym(t, ast->val.decl.id->val.idval, ast->val.decl.type);
                        break;
               
                case CON_ASSIGN:
                        if (!sym_defined(t, ast->val.assign.id->val.idval))
                             // Cannot assign into undeclared variable
                             // @Error   
                        break;
                case CON_IF:
               
                        sym_table_from_ast(t, ast->val.ifbranch.cond);
                        if (ast->val.ifbranch.if_body)
                                sym_table_from_ast(t, ast->val.ifbranch.if_body);
                        break;
               
                case CON_IF_ELSE:
               
                        sym_table_from_ast(t, ast->val.ifelsebranch.cond);
                        if (ast->val.ifelsebranch.if_body)
                                sym_table_from_ast(t, ast->val.ifelsebranch.if_body);
                        if (ast->val.ifelsebranch.else_body)
                                sym_table_from_ast(t, ast->val.ifelsebranch.else_body);
                        break;
               
                case CON_WHILE:
               
                        sym_table_from_ast(t, ast->val.whilebranch.cond);
                        if (ast->val.whilebranch.while_body)
                                sym_table_from_ast(t, ast->val.whilebranch.while_body);
                        break;
               
                default:
                        break;
        }
}