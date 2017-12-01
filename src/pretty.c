#include "pretty.h"
#include "debug.h"

#define TAB_SIZE 8

char *get_construct(enum ast_construct);

void pretty_print(FILE *f, ASTNode *tree, int indent)
{
        switch (tree->construct)
        {
                case CON_IDENT:
                        DBG(("CON_IDENT(%s)\n", tree->val.idval));

                        fprintf(f, "%s", tree->val.idval);
                        break;
                case CON_STRLIT:
                        DBG(("CON_STRLIT(%s)\n", tree->val.strval));

                        fprintf(f, "%s", tree->val.strval);
                        break;
                case CON_INTLIT:
                        DBG(("CON_INTLIT(%d)\n", tree->val.intval));

                        fprintf(f, "%d", tree->val.intval);
                        break;
                case CON_FLOATLIT:
                        DBG(("CON_FLOATLIT(%f)\n", tree->val.floatval));

                        fprintf(f, "%f", tree->val.floatval);
                        break;
                case CON_UOP_MINUS:
                        DBG(("CON_UOP_MINUS(%s)\n", get_construct(tree->val.minusuop->construct)));

                        fprintf(f, "(");
                        fprintf(f, "-");
                        pretty_print(f, tree->val.minusuop, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_MUL:
                        DBG(("CON_BOP_MUL(%s, %s)\n"
                                , get_construct(tree->val.mulbop.left->construct)
                                , get_construct(tree->val.mulbop.right->construct)));


                        fprintf(f, "(");
                        pretty_print(f, tree->val.mulbop.left, indent);
                        fprintf(f, "*");
                        pretty_print(f, tree->val.mulbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_DIV:
                        DBG(("CON_BOP_DIV(%s, %s)\n"
                                , get_construct(tree->val.divbop.left->construct)
                                , get_construct(tree->val.divbop.right->construct)));

                        fprintf(f, "(");
                        pretty_print(f, tree->val.divbop.left, indent);
                        fprintf(f, "/");
                        pretty_print(f, tree->val.divbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_PLUS:
                        DBG(("CON_BOP_PLUS(%s, %s)\n"
                                , get_construct(tree->val.plusbop.left->construct)
                                , get_construct(tree->val.plusbop.right->construct)));

                        fprintf(f, "(");
                        pretty_print(f, tree->val.plusbop.left, indent);
                        fprintf(f, "+");
                        pretty_print(f, tree->val.plusbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_BOP_MINUS:
                        DBG(("CON_BOP_MINUS(%s, %s)\n"
                                , get_construct(tree->val.minusbop.left->construct)
                                , get_construct(tree->val.minusbop.right->construct)));

                        fprintf(f, "(");
                        pretty_print(f, tree->val.minusbop.left, indent);
                        fprintf(f, "-");
                        pretty_print(f, tree->val.minusbop.right, indent);
                        fprintf(f, ")");
                        break;
                case CON_PROGRAM:
                        DBG(("CON_PROGRAM\n"
                                /*, get_construct(tree->val.prog.dcls->construct)
                                , get_construct(tree->val.prog.stmts->construct)*/));

                        if (tree->val.prog.dcls)
                                pretty_print(f, tree->val.prog.dcls,  indent);
                        if (tree->val.prog.stmts)
                                pretty_print(f, tree->val.prog.stmts, indent);
                        break;
                case CON_READ:
                        DBG(("CON_READ(%s)\n", tree->val.readidval->val.idval));

                        fprintf(f, "%*sread %s;\n", indent, "", tree->val.stmt.stmtval.readidval->val.idval);
                        if (tree->val.stmt.next)
                                pretty_print(f, tree->val.stmt.next, indent);
                        break;
                case CON_PRINT:
                        DBG(("CON_PRINT(%s)\n", get_construct(tree->val.stmt.stmtval.printexp->construct)));

                        fprintf(f, "%*sprint ", indent, "");
                        pretty_print(f, tree->val.stmt.stmtval.printexp, indent);
                        fprintf(f, ";\n");
                        if (tree->val.stmt.next)
                                pretty_print(f, tree->val.stmt.next, indent);
                        break;
                case CON_DECL:
                {
                        ASTNode *decl;
                        for (decl = tree; decl; decl=decl->val.decl.next) {
                                DBG(("CON_DECL(%s, %s)\n", decl->val.decl.id->val.idval, get_type(decl->val.decl.type)));
                                fprintf(f, "var %s: %s;\n", decl->val.decl.id->val.idval, get_type(decl->val.decl.type));
                        }
                        break;
                }
                case CON_ASSIGN:
                        DBG(("CON_ASSIGN(%s, %s)\n",
                             tree->val.stmt.stmtval.assign.id->val.idval,
                             get_construct(tree->val.stmt.stmtval.assign.e->construct)));

                        fprintf(f, "%*s%s", indent, "", tree->val.stmt.stmtval.assign.id->val.idval);
                        fprintf(f, " = ");
                        pretty_print(f, tree->val.stmt.stmtval.assign.e, indent);
                        fprintf(f, ";\n");
                        if (tree->val.stmt.next)
                                pretty_print(f, tree->val.stmt.next, indent);
                        break;
                case CON_IF:
                        DBG(("CON_IF\n"));

                        fprintf(f, "%*sif ", indent, "");
                        pretty_print(f, tree->val.stmt.stmtval.ifbranch.cond, indent);
                        fprintf(f, " then\n");
                        if (tree->val.stmt.stmtval.ifbranch.if_body)
                                pretty_print(f, tree->val.stmt.stmtval.ifbranch.if_body, indent + TAB_SIZE);
                        fprintf(f, "%*sendif\n", indent, "");
                        if (tree->val.stmt.next)
                                pretty_print(f, tree->val.stmt.next, indent);
                        break;
                case CON_IF_ELSE:
                        DBG(("CON_IF_ELSE\n"));

                        fprintf(f, "%*sif ", indent, "");
                        pretty_print(f, tree->val.stmt.stmtval.ifelsebranch.cond, indent);
                        fprintf(f, " then\n");
                        if (tree->val.stmt.stmtval.ifelsebranch.if_body)
                                pretty_print(f, tree->val.stmt.stmtval.ifelsebranch.if_body, indent + TAB_SIZE);
                        fprintf(f, "%*selse\n", indent, "");
                        if (tree->val.stmt.stmtval.ifelsebranch.else_body)
                                pretty_print(f, tree->val.stmt.stmtval.ifelsebranch.else_body, indent + TAB_SIZE);
                        fprintf(f, "%*sendif\n", indent, "");
                        if (tree->val.stmt.next)
                                pretty_print(f, tree->val.stmt.next, indent);
                        break;
                case CON_WHILE:
                        DBG(("CON_WHILE\n"));

                        fprintf(f, "%*swhile ", indent, "");
                        pretty_print(f, tree->val.stmt.stmtval.whilebranch.cond, indent);
                        fprintf(f, " do\n");
                        if (tree->val.stmt.stmtval.whilebranch.while_body != NULL)
                                pretty_print(f, tree->val.stmt.stmtval.whilebranch.while_body, indent + TAB_SIZE);
                        fprintf(f, "%*sdone\n", indent, "");
                        if(tree->val.stmt.next)
                                pretty_print(f, tree->val.stmt.next, indent);
                        break;
                default:
                        DBG(("No construct match\n"));

                        fprintf(f, "<-- Something went wrong! This text shouldn't be here! -->");
                        break;
        }
}

char *get_construct(enum ast_construct c)
{
        switch(c)
        {
                case CON_IDENT:     return "CON_IDENT";
                case CON_FLOATLIT:  return "CON_FLOATLIT";
                case CON_INTLIT:    return "CON_INTLIT";
                case CON_STRLIT:    return "CON_STRLIT";
                case CON_BOP_PLUS:  return "CON_BOP_PLUS";
                case CON_BOP_MINUS: return "CON_BOP_MINUS";
                case CON_BOP_MUL:   return "CON_BOP_MUL";
                case CON_BOP_DIV:   return "CON_BOP_DIV";
                case CON_UOP_MINUS: return "CON_UOP_MINUS";
                case CON_IF:        return "CON_IF";
                case CON_IF_ELSE:   return "CON_IF_ELSE";
                case CON_WHILE:     return "CON_WHILE";
                case CON_READ:      return "CON_READ";
                case CON_PRINT:     return "CON_PRINT";
                case CON_DECL:      return "CON_DECL";
                case CON_ASSIGN:    return "CON_ASSIGN";
                case CON_PROGRAM:   return "CON_PROGRAM";
                default:            return "Invalid construct";
        }
}
