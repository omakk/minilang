#include <stdlib.h>
#include "ast.h"

ASTNode *make_ast_node_ident (char * id)
{
        ASTNode *node   = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct = CON_IDENT;
        node->val.idval = id;
        return node;
}

ASTNode *make_ast_node_read (char *id)
{
        ASTNode *node   = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct = CON_READ;
        node->val.idval = id;
        return node;
}

ASTNode *make_ast_node_strlit (char *s)
{
        ASTNode *node    = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct  = CON_STRLIT;
        node->val.strval = s;
        return node;
}

ASTNode *make_ast_node_intlit (int i)
{
        ASTNode *node    = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct  = CON_INTLIT;
        node->val.intval = i;
        return node;
}

ASTNode *make_ast_node_floatlit (float f)
{
        ASTNode *node    = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct  = CON_FLOATLIT;
        node->val.intval = f;
        return node;
}

ASTNode *make_ast_node_print (ASTNode *e)
{
        ASTNode *node      = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct    = CON_PRINT;
        node->val.printexp = e;
        return node;
}

ASTNode *make_ast_node_minusuop (ASTNode *e)
{
        ASTNode *node      = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct    = CON_UOP_MINUS;
        node->val.printexp = e;
        return node;
}

ASTNode *make_ast_node_decl (char *id, char *type)
{
        ASTNode *node        = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct      = CON_DECL;
        node->val.decl.idval = id;
        node->val.decl.type  = type;
        return node;
}

ASTNode *make_ast_node_assign (char *id, ASTNode *e)
{
        ASTNode *node          = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct        = CON_ASSIGN;
        node->val.assign.idval = id;
        node->val.assign.e     = e;
        return node;
}

ASTNode *make_ast_node_mulop (ASTNode *l, ASTNode *r)
{
        ASTNode *node         = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct       = CON_OP_MUL;
        node->val.mulop.left  = l;
        node->val.mulop.right = r;
        return node;
}


ASTNode *make_ast_node_divop (ASTNode *l, ASTNode *r)
{
        ASTNode *node         = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct       = CON_OP_DIV;
        node->val.divop.left  = l;
        node->val.divop.right = r;
        return node;
}


ASTNode *make_ast_node_plusop (ASTNode *l, ASTNode *r)
{
        ASTNode *node          = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct        = CON_OP_PLUS;
        node->val.plusop.left  = l;
        node->val.plusop.right = r;
        return node;
}


ASTNode *make_ast_node_minusop (ASTNode *l, ASTNode *r)
{
        ASTNode *node           = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct         = CON_OP_MINUS;
        node->val.minusop.left  = l;
        node->val.minusop.right = r;
        return node;
}

ASTNode *make_ast_node_whilebranch(ASTNode *cond, ASTNode *while_body)
{
        ASTNode *node                    = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct                  = CON_WHILE;
        node->val.whilebranch.cond       = cond;
        node->val.whilebranch.while_body = while_body;
        return node;
}

ASTNode *make_ast_node_ifbranch (ASTNode *cond, ASTNode *if_body)
{
        ASTNode *node              = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct            = CON_IF;
        node->val.ifbranch.cond    = cond;
        node->val.ifbranch.if_body = if_body;
        return node;
}

ASTNode *make_ast_node_ifelsebranch (ASTNode *cond, ASTNode *if_body, ASTNode *else_body)
{
        ASTNode *node                = (ASTNode *) malloc(sizeof(ASTNode));
        node->construct              = CON_IF_ELSE;
        node->val.ifbranch.cond      = cond;
        node->val.ifbranch.if_body   = if_body;
        node->val.ifbranch.else_body = else_body;
        return node;
}
