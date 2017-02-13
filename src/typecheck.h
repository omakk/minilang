#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "ast.h"
#include "symbol.h"

void typecheck_prog(SYM_TABLE *t, ASTNode *ast);

const char *eval_exp_type(SYM_TABLE *t,ASTNode *exp);

void report_type_error(const char *msg, int lineno);

#endif
