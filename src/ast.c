#include <stdlib.h>
#include <string.h>
#include "ast.h"

const char *get_type(enum type type)
{
        switch(type)
        {
        case TINT:
                return "int";
                break;
        case TFLOAT:
                return "float";
                break;
        case TSTRING:
                return "string";
                break;
        default:
                break;
        }

        return NULL;
}

enum type make_type(const char *type)
{
        if (strcmp(type, "int") == 0)
                return TINT;
        else if (strcmp(type, "float") == 0)
                return TFLOAT;
        /* else if (strcmp(type, "string") == 0)
                return TSTRING; */
        else
                return TSTRING;
}

ASTNode *make_ast_node_ident (char * id, int lineno)
{
        ASTNode *node   = malloc(sizeof(ASTNode));
        node->lineno    = lineno;
        node->construct = CON_IDENT;
        node->val.idval = id;
        return node;
}

ASTNode *make_ast_node_read (char *id, int lineno)
{
        ASTNode *node                    = malloc(sizeof(ASTNode));
        node->lineno                     = lineno;
        node->construct                  = CON_READ;
        node->val.stmt.stmtval.readidval = make_ast_node_ident(id, lineno);
        node->val.stmt.next              = NULL;
        return node;
}

ASTNode *make_ast_node_strlit (char *s, int lineno)
{
        ASTNode *node    = malloc(sizeof(ASTNode));
        node->lineno     = lineno;
        node->construct  = CON_STRLIT;
        node->val.strval = s;
        return node;
}

ASTNode *make_ast_node_intlit (int i, int lineno)
{
        ASTNode *node    = malloc(sizeof(ASTNode));
        node->lineno     = lineno;
        node->construct  = CON_INTLIT;
        node->val.intval = i;
        return node;
}

ASTNode *make_ast_node_floatlit (float f, int lineno)
{
        ASTNode *node      = malloc(sizeof(ASTNode));
        node->lineno       = lineno;
        node->construct    = CON_FLOATLIT;
        node->val.floatval = f;
        return node;
}

ASTNode *make_ast_node_print (ASTNode *e, int lineno)
{
        ASTNode *node                   = malloc(sizeof(ASTNode));
        node->lineno                    = lineno;
        node->construct                 = CON_PRINT;
        node->val.stmt.stmtval.printexp = e;
        node->val.stmt.next             = NULL;
        return node;
}

ASTNode *make_ast_node_minusuop (ASTNode *e, int lineno)
{
        ASTNode *node      = malloc(sizeof(ASTNode));
        node->lineno       = lineno;
        node->construct    = CON_UOP_MINUS;
        node->val.minusuop = e;
        return node;
}

ASTNode *make_ast_node_decl (char *id, enum type type, int lineno)
{
        ASTNode *node        = malloc(sizeof(ASTNode));
        node->lineno         = lineno;
        node->construct      = CON_DECL;
        node->val.decl.id    = make_ast_node_ident(id, lineno);
        node->val.decl.type  = type;
        node->val.decl.next  = NULL;
        return node;
}

ASTNode *make_ast_node_assign (char *id, ASTNode *e, int lineno)
{
        ASTNode *node                     = malloc(sizeof(ASTNode));
        node->lineno                      = lineno;
        node->construct                   = CON_ASSIGN;
        node->val.stmt.stmtval.assign.id  = make_ast_node_ident(id, lineno);
        node->val.stmt.stmtval.assign.e   = e;
        node->val.stmt.next               = NULL;
        return node;
}

ASTNode *make_ast_node_prog (ASTNode *dcls, ASTNode *stmts, int lineno)
{
        ASTNode *node          = malloc(sizeof(ASTNode));
        node->lineno           = lineno;
        node->construct        = CON_PROGRAM;
        node->val.prog.dcls    = dcls;
        node->val.prog.stmts   = stmts;
        return node;
}

ASTNode *make_ast_node_mulbop (ASTNode *l, ASTNode *r, int lineno)
{
        ASTNode *node          = malloc(sizeof(ASTNode));
        node->lineno           = lineno;
        node->construct        = CON_BOP_MUL;
        node->val.mulbop.left  = l;
        node->val.mulbop.right = r;
        return node;
}


ASTNode *make_ast_node_divbop (ASTNode *l, ASTNode *r, int lineno)
{
        ASTNode *node          = malloc(sizeof(ASTNode));
        node->lineno           = lineno;
        node->construct        = CON_BOP_DIV;
        node->val.divbop.left  = l;
        node->val.divbop.right = r;
        return node;
}


ASTNode *make_ast_node_plusbop (ASTNode *l, ASTNode *r, int lineno)
{
        ASTNode *node           = malloc(sizeof(ASTNode));
        node->lineno            = lineno;
        node->construct         = CON_BOP_PLUS;
        node->val.plusbop.left  = l;
        node->val.plusbop.right = r;
        return node;
}


ASTNode *make_ast_node_minusbop (ASTNode *l, ASTNode *r, int lineno)
{
        ASTNode *node            = malloc(sizeof(ASTNode));
        node->lineno             = lineno;
        node->construct          = CON_BOP_MINUS;
        node->val.minusbop.left  = l;
        node->val.minusbop.right = r;
        return node;
}

ASTNode *make_ast_node_whilebranch(ASTNode *cond, ASTNode *while_body, int lineno)
{
        ASTNode *node                                 = malloc(sizeof(ASTNode));
        node->lineno                                  = lineno;
        node->construct                               = CON_WHILE;
        node->val.stmt.stmtval.whilebranch.cond       = cond;
        node->val.stmt.stmtval.whilebranch.while_body = while_body;
        node->val.stmt.next                           = NULL;
        return node;
}

ASTNode *make_ast_node_ifbranch (ASTNode *cond, ASTNode *if_body, int lineno)
{
        ASTNode *node                           = malloc(sizeof(ASTNode));
        node->lineno                            = lineno;
        node->construct                         = CON_IF;
        node->val.stmt.stmtval.ifbranch.cond    = cond;
        node->val.stmt.stmtval.ifbranch.if_body = if_body;
        node->val.stmt.next                     = NULL;
        return node;
}

ASTNode *make_ast_node_ifelsebranch (ASTNode *cond, ASTNode *if_body, ASTNode *else_body, int lineno)
{
        ASTNode *node                                 = malloc(sizeof(ASTNode));
        node->lineno                                  = lineno;
        node->construct                               = CON_IF_ELSE;
        node->val.stmt.stmtval.ifelsebranch.cond      = cond;
        node->val.stmt.stmtval.ifelsebranch.if_body   = if_body;
        node->val.stmt.stmtval.ifelsebranch.else_body = else_body;
        node->val.stmt.next                           = NULL;
        return node;
}

ASTNode *prepend_dcl(ASTNode *dcl, ASTNode *dcls)
{
        if (!dcl)
                return NULL;
        if (dcls)
                dcl->val.decl.next = dcls;
        return dcl;
}

ASTNode *prepend_stmt(ASTNode *stmt, ASTNode *stmts)
{
        if (!stmt)
                return NULL;
        if (stmts)
                stmt->val.stmt.next = stmts;
        return stmt;
}

void free_ast(ASTNode *root)
{
        if (!root)
                return;
        switch(root->construct)
        {
        case CON_IDENT:
                free(root->val.idval);
                free(root);
                break;
        case CON_FLOATLIT:
                free(root);
                break;
        case CON_INTLIT:
                free(root);
                break;
        case CON_STRLIT:
                free(root->val.strval);
                free(root);
                break;
        case CON_BOP_PLUS:
                free_ast(root->val.plusbop.left);
                free_ast(root->val.plusbop.right);
                free(root);
                break;
        case CON_BOP_MINUS:
                free_ast(root->val.minusbop.left);
                free_ast(root->val.minusbop.right);
                free(root);
                break;
        case CON_BOP_MUL:
                free_ast(root->val.mulbop.left);
                free_ast(root->val.mulbop.right);
                free(root);
                break;
        case CON_BOP_DIV:
                free_ast(root->val.divbop.left);
                free_ast(root->val.divbop.right);
                free(root);
                break;
        case CON_UOP_MINUS:
                free_ast(root->val.minusuop);
                free(root);
                break;
        case CON_IF:
                free_ast(root->val.stmt.stmtval.ifbranch.cond);
                free_ast(root->val.stmt.stmtval.ifbranch.if_body);
                free_ast(root->val.stmt.next);
                free(root);
                break;
        case CON_IF_ELSE:
                free_ast(root->val.stmt.stmtval.ifelsebranch.cond);
                free_ast(root->val.stmt.stmtval.ifelsebranch.if_body);
                free_ast(root->val.stmt.stmtval.ifelsebranch.else_body);
                free_ast(root->val.stmt.next);
                free(root);
                break;
        case CON_WHILE:
                free_ast(root->val.stmt.stmtval.whilebranch.cond);
                free_ast(root->val.stmt.stmtval.whilebranch.while_body);
                free_ast(root->val.stmt.next);
                free(root);
                break;
        case CON_READ:
                free_ast(root->val.stmt.stmtval.readidval);
                free_ast(root->val.stmt.next);
                free(root);
                break;
        case CON_PRINT:
                free_ast(root->val.stmt.stmtval.printexp);
                free_ast(root->val.stmt.next);
                free(root);
                break;
        case CON_DECL:
                free_ast(root->val.decl.next);
                free(root);
                break;
        case CON_ASSIGN:
                free_ast(root->val.stmt.stmtval.assign.id);
                free_ast(root->val.stmt.stmtval.assign.e);
                free_ast(root->val.stmt.next);
                free(root);
                break;
        case CON_PROGRAM:
                free_ast(root->val.prog.dcls);
                free_ast(root->val.prog.stmts);
                free(root);
                break;
        }
}
