#include "pretty.h"

void pretty_print(FILE *f, ASTNode *tree)
{
        switch (tree->construct)
        {
                case CON_IDENT:
                        fprintf(f, "%s", tree->val.idval);
                        break;
                case CON_STRLIT:
                        fprintf(f, "%s", tree->val.strval);
                        break;
                case CON_INTLIT:
                        fprintf(f, "%d", tree->val.intval);
                        break;
                case CON_FLOATLIT:
                        fprintf(f, "%f", tree->val.floatval);
                        break;
                case CON_UOP_MINUS:
                        fprintf(f, "-");
                        fprintf(f, "(");
                        pretty_print(f, tree->val.minusuop.e);
                        fprintf(f, ")");
                        break;
                case CON_BOP_MUL:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.mulbop.left);
                        fprintf(f, "*");
                        pretty_print(f, tree->val.mulbop.right);
                        fprintf(f, ")");
                        break;
                case CON_BOP_DIV:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.divbop.left);
                        fprintf(f, "/");
                        pretty_print(f, tree->val.divbop.right);
                        fprintf(f, ")");
                        break;
                case CON_BOP_PLUS:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.plusbop.left);
                        fprintf(f, "+");
                        pretty_print(f, tree->val.plusbop.right);
                        fprintf(f, ")");
                        break;
                case CON_BOP_MINUS:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.minusbop.left);
                        fprintf(f, "-");
                        pretty_print(f, tree->val.minusbop.right);
                        fprintf(f, ")");
                        break;
                case CON_PAREN_EXP:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.parenexp.e);
                        fprintf(f, ")");
                        break;
                case CON_PROGRAM:
                        if (tree->val.prog.dcls  != NULL) pretty_print(f, tree->val.prog.dcls);
                        fprintf(f, "\n");
                        if (tree->val.prog.stmts != NULL) pretty_print(f, tree->val.prog.stmts);
                        break;
                case CON_DCLS:
                        if (tree->val.dcls.dcl != NULL)   pretty_print(f, tree->val.dcls.dcl);
                        if (tree->val.dcls.dcls != NULL)  pretty_print(f, tree->val.dcls.dcls);
                        break;
                case CON_STMTS:
                        if (tree->val.stmts.stmt != NULL)   pretty_print(f, tree->val.stmts.stmt);
                        if (tree->val.stmts.stmts != NULL)  pretty_print(f, tree->val.stmts.stmts);
                        break;
                case CON_READ:
                        fprintf(f, "read %s;\n", tree->val.idval);
                        break;
                case CON_PRINT:
                        fprintf(f, "print");
                        fprintf(f, " (");
                        pretty_print(f, tree->val.printexp.e);
                        fprintf(f, ");\n");
                        break;
                case CON_DECL:
                        fprintf(f, "var %s: %s;\n", tree->val.decl.idval, tree->val.decl.type);
                        break;
                case CON_ASSIGN:
                        fprintf(f, "%s = (", tree->val.assign.idval);
                        pretty_print(f, tree->val.assign.e);
                        fprintf(f, ");\n");
                        break;
                case CON_IF:
                        fprintf(f, "if");
                        fprintf(f, " (");
                        pretty_print(f, tree->val.ifbranch.cond);
                        fprintf(f, ") ");
                        fprintf(f, "then\n\t");
                        pretty_print(f, tree->val.ifbranch.if_body);
                        fprintf(f, "\nendif\n");
                        break;
                case CON_IF_ELSE:
                        fprintf(f, "if");
                        fprintf(f, " (");
                        pretty_print(f, tree->val.ifelsebranch.cond);
                        fprintf(f, ") ");
                        fprintf(f, "then\n\t");
                        pretty_print(f, tree->val.ifelsebranch.if_body);
                        fprintf(f, "\n");
                        fprintf(f, "else\n\t");
                        pretty_print(f, tree->val.ifelsebranch.else_body);
                        fprintf(f, "\nendif\n");
                        break;
                case CON_WHILE:
                        fprintf(f, "while");
                        fprintf(f, " (");
                        pretty_print(f, tree->val.whilebranch.cond);
                        fprintf(f, ") ");
                        fprintf(f, "do\n\t");
                        pretty_print(f, tree->val.whilebranch.while_body);
                        fprintf(f, "\ndone\n");
                        break;
                default:
                        fprintf(f, "Something went wrong!\n");
                        break;
        }
}
