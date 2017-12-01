#include <stdlib.h>
#include "typecheck.h"

void report_type_error(const char *msg, int lineno)
{
        fprintf(stderr, "INVALID: %s; line: %d\n", msg, lineno);
        exit(1);
}

enum type eval_exp_type(SYM_TABLE *t, ASTNode *exp)
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
        case CON_STRLIT:     return TSTRING; break;
        case CON_INTLIT:     return TINT;    break;
        case CON_FLOATLIT:   return TFLOAT;  break;
        case CON_UOP_MINUS:
        {
                enum type type;
                type = eval_exp_type(t, exp->val.minusuop);
                switch(type)
                {
                case TINT:
                case TFLOAT:
                        return type;
                        break;
                default:
                        report_type_error("type error; unary negation expected \"int\" or \"float\"", exp->lineno);
                }
                break;
        }
        case CON_BOP_MUL:
        {
                enum type type_l, type_r;

                type_l = eval_exp_type(t, exp->val.mulbop.left);
                type_r = eval_exp_type(t, exp->val.mulbop.right);

                switch(type_l)
                {
                case TINT:
                        return type_r;
                        break;
                case TSTRING:
                        if (type_r == TINT)
                                return TSTRING;
                        else
                                report_type_error("type error: string multiplication expected \"int\"", exp->lineno);
                        break;
                case TFLOAT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return TFLOAT;
                        else
                                report_type_error("type error: float multiplication expected \"float\" or \"int\"", exp->lineno);
                        break;
                default:
                        break;
                }
                break;
        }
        case CON_BOP_DIV:
        {
                enum type type_l, type_r;

                type_l = eval_exp_type(t, exp->val.divbop.left);
                type_r = eval_exp_type(t, exp->val.divbop.right);

                switch(type_l)
                {
                case TINT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return type_r;
                        else
                                report_type_error("type error: int division expected \"int\" or \"float\"", exp->lineno);
                        break;
                case TFLOAT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return type_r;
                        else
                                report_type_error("type error: int division expected \"int\" or \"float\"", exp->lineno);
                        break;
                default:
                        report_type_error("type error: division operation expected \"float\" or \"int\"", exp->lineno);
                        break;
                }
                break;
        }
        case CON_BOP_PLUS:
        {
                enum type type_l, type_r;

                type_l = eval_exp_type(t, exp->val.plusbop.left);
                type_r = eval_exp_type(t, exp->val.plusbop.right);

                switch(type_l)
                {
                case TINT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return type_r;
                        else
                                report_type_error("type error: int addition expected \"int\" or \"float\"", exp->lineno);
                        break;
                case TSTRING:
                        if (type_r == TSTRING)
                                return TSTRING;
                        else
                                report_type_error("type error: string concatenation expected \"string\"", exp->lineno);
                        break;
                case TFLOAT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return type_r;
                        else
                                report_type_error("type error: float addition expected \"float\" or \"int\"", exp->lineno);
                        break;
                default:
                        report_type_error("type error: addition type error", exp->lineno);
                        break;
                }
                break;
        }
        case CON_BOP_MINUS:
        {
                enum type type_l, type_r;

                type_l = eval_exp_type(t, exp->val.minusbop.left);
                type_r = eval_exp_type(t, exp->val.minusbop.right);

                switch (type_l)
                {
                case TINT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return type_r;
                        else
                                report_type_error("type error: Subtraction from int expects \"int\" or \"float\"", exp->lineno);
                        break;
                case TFLOAT:
                        if (type_r == TINT || type_r == TFLOAT)
                                return type_r;
                        else
                                report_type_error("type error: Subtraction from float expects \"float\" or \"int\"", exp->lineno);
                        break;
                default:
                        report_type_error("type error: Subtraction op expects \"float\" or \"int\"", exp->lineno);
                        break;
                }
                break;
        }
        default:
                report_type_error("Could note evaluate type", exp->lineno);
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
        case CON_ASSIGN:
        {
                enum type type_lhs, type_rhs;
                SYMBOL *s;
                s = get_sym(t, ast->val.stmt.stmtval.assign.id->val.idval);
                type_lhs = s->type;
                type_rhs = eval_exp_type(t, ast->val.stmt.stmtval.assign.e);

                switch (type_lhs)
                {
                case TFLOAT:
                        if (type_rhs != TINT && type_rhs != TFLOAT)
                                report_type_error("assignment type error", ast->lineno);
                        break;
                default:
                        if (type_lhs != type_rhs)
                                report_type_error("assignment type error", ast->lineno);
                        break;
                }
                if (ast->val.stmt.next)
                        typecheck_prog(t, ast->val.stmt.next);
                break;
        }
        case CON_READ:
                if (ast->val.stmt.next)
                        typecheck_prog(t, ast->val.stmt.next);
                break;
        case CON_PRINT:
                eval_exp_type(t, ast->val.stmt.stmtval.printexp);
                if (ast->val.stmt.next)
                        typecheck_prog(t, ast->val.stmt.next);
                break;
        case CON_IF:
        {
                enum type ifcond_type;
                ifcond_type = eval_exp_type(t, ast->val.stmt.stmtval.ifbranch.cond);

                if (ifcond_type != TINT)
                        report_type_error("type error: if condition must evaluate to \"int\"", ast->lineno);
                if (ast->val.stmt.stmtval.ifbranch.if_body != NULL)
                        typecheck_prog(t, ast->val.stmt.stmtval.ifbranch.if_body);
                if (ast->val.stmt.next)
                        typecheck_prog(t, ast->val.stmt.next);
                break;
        }
        case CON_IF_ELSE:
        {
                enum type iftype_cond;
                iftype_cond = eval_exp_type(t, ast->val.stmt.stmtval.ifelsebranch.cond);

                if (iftype_cond != TINT)
                        report_type_error("type error: if condition must evaluate to \"int\"", ast->lineno);

                if (ast->val.stmt.stmtval.ifelsebranch.if_body != NULL)
                        typecheck_prog(t, ast->val.stmt.stmtval.ifelsebranch.if_body);
                if (ast->val.stmt.stmtval.ifelsebranch.else_body != NULL)
                        typecheck_prog(t, ast->val.stmt.stmtval.ifelsebranch.else_body);
                if (ast->val.stmt.next)
                        typecheck_prog(t, ast->val.stmt.next);
                break;
        }
        case CON_WHILE:
        {
                enum type whilecond_type;
                whilecond_type = eval_exp_type(t, ast->val.stmt.stmtval.whilebranch.cond);

                if (whilecond_type != TINT)
                        report_type_error("type error: while condition must evaluate to \"int\"", ast->lineno);

                if (ast->val.stmt.stmtval.whilebranch.while_body != NULL)
                        typecheck_prog(t, ast->val.stmt.stmtval.whilebranch.while_body);
                if (ast->val.stmt.next)
                        typecheck_prog(t, ast->val.stmt.next);
                break;
        }
        default:
                break;
        }
}
