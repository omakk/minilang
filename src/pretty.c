#include <stdio.h>
#include "pretty.h"

void pretty_print(ASTNode *tree)
{
        switch (tree->construct)
        {
                case CON_IDENT:
                        break;
                case CON_STRLIT:
                        break;
                case CON_INTLIT:
                        break;
                case CON_FLOATLIT:
                        break;
                case CON_UOP_MINUS:
                        break;
                case CON_BOP_MUL:
                        break;
                case CON_BOP_DIV:
                        break;
                case CON_BOP_PLUS:
                        break;
                case CON_BOP_MINUS:
                        break;
                case CON_READ:
                        break;
                case CON_PRINT:
                        break;
                case CON_DECL:
                        break;
                case CON_ASSIGN:
                        break;
                case CON_IF:
                        break;
                case CON_IF_ELSE:
                        break;
                case CON_WHILE:
                        break;
                default:
                        printf("Somethign went wrong!\n");
                        break;
        }
}
