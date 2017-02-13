#include <stdlib.h>
#include <string.h>
#include "typecheck.h"

void report_type_error(const char *msg, int lineno)
{
        fprintf(stderr, "INVALID: %s; line: %d\n", msg, lineno);
        exit(1);
}

const char *eval_exp_type(SYM_TABLE *t, ASTNode *exp)
{
        switch(exp->construct)
        {
                case CON_IDENT:
                {
                        SYMBOL *s;
                        s = get_sym(t, exp->val.idval);
                        return s->type;
                        break;
                }
                case CON_STRLIT:     return "string"; break;
                case CON_INTLIT:     return "int";    break;
                case CON_FLOATLIT:   return "float";  break;
                case CON_UOP_MINUS:
                {
                        const char *type;
                        type = eval_exp_type(t, exp->val.minusuop);
                        if (strcmp(type, "int") == 0) {
                               return "int";
                        }
                        if (strcmp(type, "float") == 0) {
                               return "float";
                        }
                        report_type_error("type error; unary negation expected \"int\" or \"float\"", exp->lineno); 
                        break;
                }
                case CON_BOP_MUL:
                {        
                        const char *type_l, *type_r;

                        type_l = eval_exp_type(t, exp->val.mulbop.left);
                        type_r = eval_exp_type(t, exp->val.mulbop.right);
                        
                        if (strcmp(type_l, "int") == 0) {
                                return type_r;
                        } else if (strcmp(type_l, "string") == 0) {
                                if (strcmp(type_r, "int") == 0) {
                                        return "string";
                                } else {
                                        report_type_error("type error: string multiplication expected \"int\"", exp->lineno);
                                }
                        } else {
                                if ((strcmp(type_r, "int") == 0) || (strcmp(type_r, "float") == 0)) {
                                        return "float";
                                } else {
                                        report_type_error("type error: float multiplication expected \"float\" or \"int\"", exp->lineno);
                                } 
                        }
                        break;
                }
                case CON_BOP_DIV:
                {
                        const char *type_l, *type_r;

                        type_l = eval_exp_type(t, exp->val.divbop.left);
                        type_r = eval_exp_type(t, exp->val.divbop.right);
                        
                        if (strcmp(type_l, "int") == 0) {
                                if (strcmp(type_l, "string") == 0) {
                                        report_type_error("type error: int division expected \"int\" or \"float\"", exp->lineno);
                                } else { 
                                        return type_r;
                                }
                        } else if (strcmp(type_l, "float") == 0) {
                                if (strcmp(type_l, "string") == 0) {
                                        report_type_error("type error: float division expected \"float\" or \"int\"", exp->lineno);
                                } else { 
                                        return type_r;
                                }
                        } else {
                                report_type_error("type error: division operation expected \"float\" or \"int\"", exp->lineno); 
                        }
                        break;
                }
                case CON_BOP_PLUS:
                {
                        const char *type_l, *type_r;

                        type_l = eval_exp_type(t, exp->val.plusbop.left);
                        type_r = eval_exp_type(t, exp->val.plusbop.right);
                        
                        if (strcmp(type_l, "int") == 0) {
                                if (strcmp(type_l, "string") == 0) {
                                        report_type_error("type error: int addition expected \"int\" or \"float\"", exp->lineno);
                                } else { 
                                        return type_r;
                                }
                        } else if (strcmp(type_l, "string") == 0) {
                                if (strcmp(type_r, "string") != 0) {
                                        report_type_error("type error: string concatenation expected \"string\"", exp->lineno);
                                } else {
                                        return "string";
                                }
                        } else {
                                if ((strcmp(type_r, "int") == 0) || (strcmp(type_r, "float") == 0)) {
                                        return "float";
                                } else {
                                        report_type_error("type error: float addition expected \"float\" or \"int\"", exp->lineno);
                                } 
                        }
                        break;
                }
                case CON_BOP_MINUS:
                {
                        const char *type_l, *type_r;

                        type_l = eval_exp_type(t, exp->val.minusbop.left);
                        type_r = eval_exp_type(t, exp->val.minusbop.right);
                        
                        if (strcmp(type_l, "int") == 0) {
                                if (strcmp(type_l, "string") == 0) {
                                        report_type_error("type error: int subtraction expected \"int\" or \"float\"", exp->lineno);
                                } else { 
                                        return type_r;
                                }
                        } else if (strcmp(type_l, "float") == 0) {
                                if (strcmp(type_r, "string") == 0) {
                                        report_type_error("type error: float subtraction expected \"float\" or \"int\"", exp->lineno);
                                } else {
                                        return "float";
                                }
                        } else {
                                report_type_error("type error: subtraction operation expected \"float\" or \"int\"", exp->lineno); 
                        }
                        break;
                }
                default:
                        report_type_error("could note evaluate type", exp->lineno);
                        break;
        }

}

void typecheck_prog(SYM_TABLE *t, ASTNode *ast)
{
        switch(ast->construct)
        {
                case CON_PROGRAM:
                        if (ast->val.prog.stmts != NULL)
                                typecheck_prog(t, ast->val.prog.stmts);
                        break;
                case CON_STMTS:
                        typecheck_prog(t, ast->val.stmts.stmt);
                        if (ast->val.stmts.stmts != NULL)
                                typecheck_prog(t, ast->val.stmts.stmts);
                        break;
                case CON_ASSIGN:
                {
                        const char *type_ident, *type_exp;
                        SYMBOL *s;
                        s = get_sym(t, ast->val.assign.id->val.idval);
                        type_ident = s->type;
                        type_exp   = eval_exp_type(t, ast->val.assign.e);

                        if (strcmp(type_ident, "float") == 0) {
                                if (strcmp(type_exp, "string") == 0)
                                        report_type_error("assignment type error", ast->lineno);
                        } else if (strcmp(type_ident, type_exp) != 0) {
                                report_type_error("assignment type error", ast->lineno);
                        }

                        break;
                }
                case CON_READ:
                        break;
                case CON_PRINT:
                        eval_exp_type(t, ast->val.printexp);
                        break;
                case CON_IF:
                {
                        const char *type_cond;
                        type_cond = eval_exp_type(t, ast->val.ifbranch.cond);

                        if (strcmp(type_cond, "int") != 0)
                                report_type_error("type error: if condition expected \"int\"", ast->lineno);

                        if (ast->val.ifbranch.if_body != NULL)
                                typecheck_prog(t, ast->val.ifbranch.if_body);
                        
                        break;
                }
                case CON_IF_ELSE:
                {
                        const char *type_cond;
                        type_cond = eval_exp_type(t, ast->val.ifelsebranch.cond);

                        if (strcmp(type_cond, "int") != 0)
                                report_type_error("type error: if condition expected \"int\"", ast->lineno);

                        if (ast->val.ifelsebranch.if_body != NULL)
                                typecheck_prog(t, ast->val.ifelsebranch.if_body);
                        if (ast->val.ifelsebranch.else_body != NULL)
                                typecheck_prog(t, ast->val.ifelsebranch.else_body);
                        
                        break;
                }
                case CON_WHILE:
                {
                        const char *type_cond;
                        type_cond = eval_exp_type(t, ast->val.whilebranch.cond);

                        if (strcmp(type_cond, "int") != 0)
                                report_type_error("type error: while condition expected \"int\"", ast->lineno);

                        if (ast->val.whilebranch.while_body != NULL)
                                typecheck_prog(t, ast->val.whilebranch.while_body);
                        break;
                }
                default:
                        break;
        }
}
