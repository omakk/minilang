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
        ASTNode *node       = malloc(sizeof(ASTNode));
        node->lineno        = lineno;
        node->construct     = CON_READ;
        node->val.readidval = make_ast_node_ident(id, lineno);
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
        ASTNode *node      = malloc(sizeof(ASTNode));
        node->lineno       = lineno;
        node->construct    = CON_PRINT;
        node->val.printexp = e;
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
        return node;
}

ASTNode *make_ast_node_assign (char *id, ASTNode *e, int lineno)
{
        ASTNode *node        = malloc(sizeof(ASTNode));
        node->lineno         = lineno;
        node->construct      = CON_ASSIGN;
        node->val.assign.id  = make_ast_node_ident(id, lineno);
        node->val.assign.e   = e;
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

ASTNode *make_ast_node_dcls (ASTNode *dcl, ASTNode *dcls, int lineno)
{
        ASTNode *node          = malloc(sizeof(ASTNode));
        node->lineno           = lineno;
        node->construct        = CON_DCLS;
        node->val.dcls.dcl     = dcl;
        node->val.dcls.dcls    = dcls;
        return node;
}

ASTNode *make_ast_node_stmts (ASTNode *stmt, ASTNode *stmts, int lineno)
{
        ASTNode *node           = malloc(sizeof(ASTNode));
        node->lineno            = lineno;
        node->construct         = CON_STMTS;
        node->val.stmts.stmt    = stmt;
        node->val.stmts.stmts   = stmts;
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
        ASTNode *node                    = malloc(sizeof(ASTNode));
        node->lineno                     = lineno;
        node->construct                  = CON_WHILE;
        node->val.whilebranch.cond       = cond;
        node->val.whilebranch.while_body = while_body;
        return node;
}

ASTNode *make_ast_node_ifbranch (ASTNode *cond, ASTNode *if_body, int lineno)
{
        ASTNode *node              = malloc(sizeof(ASTNode));
        node->lineno               = lineno;
        node->construct            = CON_IF;
        node->val.ifbranch.cond    = cond;
        node->val.ifbranch.if_body = if_body;
        return node;
}

ASTNode *make_ast_node_ifelsebranch (ASTNode *cond, ASTNode *if_body, ASTNode *else_body, int lineno)
{
        ASTNode *node                    = malloc(sizeof(ASTNode));
        node->lineno                     = lineno;
        node->construct                  = CON_IF_ELSE;
        node->val.ifelsebranch.cond      = cond;
        node->val.ifelsebranch.if_body   = if_body;
        node->val.ifelsebranch.else_body = else_body;
        return node;
}
