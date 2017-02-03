#include <stdio.h>
#include "ast.h"

int yyparse();
ASTNode  *ast;

int main()
{
    if (yyparse() == 0)
            printf("VALID\n");
    
    return 0;
}
