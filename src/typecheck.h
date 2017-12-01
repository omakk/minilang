#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "ast.h"
#include "symbol.h"

int typecheck_prog(SYM_TABLE *t, ASTNode *ast);

enum type eval_exp_type(SYM_TABLE *t,ASTNode *exp);

void report_type_error(const char *msg, int lineno);

int type_error;

#endif
