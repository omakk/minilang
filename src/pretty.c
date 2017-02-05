#include "pretty.h"

#define TAB_SIZE 4

void pretty_print(FILE *f, ASTNode *tree, int indent)
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
                        fprintf(f, "(");
                        fprintf(f, "-");
                        pretty_print(f, tree->val.minusuop.e, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_MUL:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.mulbop.left, indent);
                        fprintf(f, "*");
                        pretty_print(f, tree->val.mulbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_DIV:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.divbop.left, indent);
                        fprintf(f, "/");
                        pretty_print(f, tree->val.divbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_PLUS:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.plusbop.left, indent);
                        fprintf(f, "+");
                        pretty_print(f, tree->val.plusbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_MINUS:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.minusbop.left, indent);
                        fprintf(f, "-");
                        pretty_print(f, tree->val.minusbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_PAREN_EXP:
                        fprintf(f, "(");
                        pretty_print(f, tree->val.parenexp.e, indent);
                        fprintf(f, ")");
                        break;
                case CON_PROGRAM:
                        if (tree->val.prog.dcls  != NULL)  pretty_print(f, tree->val.prog.dcls,  indent);
                        if (tree->val.prog.stmts != NULL)  pretty_print(f, tree->val.prog.stmts, indent);
                        break;
                case CON_DCLS:
                        pretty_print(f, tree->val.dcls.dcl,  indent);
                        if (tree->val.dcls.dcls != NULL)   pretty_print(f, tree->val.dcls.dcls, indent);
                        break;
                case CON_STMTS:
                        pretty_print(f, tree->val.stmts.stmt,  indent);
                        if (tree->val.stmts.stmts != NULL) pretty_print(f, tree->val.stmts.stmts, indent);
                        break;
                case CON_READ:
                        fprintf(f, "%*sread %s;\n", indent, "", tree->val.idval);
                        break;
                case CON_PRINT:
                        fprintf(f, "%*sprint ", indent, "");
                        pretty_print(f, tree->val.printexp.e, indent);
                        fprintf(f, ";\n");
                        break;
                case CON_DECL:
                        fprintf(f, "var %s: %s;\n", tree->val.decl.idval, tree->val.decl.type);
                        break;
                case CON_ASSIGN:
                        fprintf(f, "%*s%s = ", indent, "", tree->val.assign.idval);
                        pretty_print(f, tree->val.assign.e, indent);
                        fprintf(f, ";\n");
                        break;
                case CON_IF:
                        fprintf(f, "%*sif ", indent, "");
                        pretty_print(f, tree->val.ifbranch.cond, indent);
                        fprintf(f, " then\n");
                        if (tree->val.ifbranch.if_body != NULL)
                                pretty_print(f, tree->val.ifbranch.if_body, indent + TAB_SIZE);
                        fprintf(f, "%*sendif\n", indent, "");
                        break;
                case CON_IF_ELSE:
                        fprintf(f, "%*sif ", indent, "");
                        pretty_print(f, tree->val.ifelsebranch.cond, indent);
                        fprintf(f, " then\n");
                        if (tree->val.ifelsebranch.if_body != NULL)
                                pretty_print(f, tree->val.ifelsebranch.if_body,   indent + TAB_SIZE);
                        fprintf(f, "%*selse\n", indent, "");
                        if (tree->val.ifelsebranch.else_body != NULL)
                                pretty_print(f, tree->val.ifelsebranch.else_body, indent + TAB_SIZE);
                        fprintf(f, "%*sendif\n", indent, "");
                        break;
                case CON_WHILE:
                        fprintf(f, "%*swhile ", indent, "");
                        pretty_print(f, tree->val.whilebranch.cond, indent);
                        fprintf(f, " do\n");
                        if (tree->val.whilebranch.while_body != NULL) 
                                pretty_print(f, tree->val.whilebranch.while_body, indent + TAB_SIZE);
                        fprintf(f, "%*sdone\n", indent, "");
                        break;
                default:
                        fprintf(f, "Something went horribly wrong!\n");
                        break;
        }
}
