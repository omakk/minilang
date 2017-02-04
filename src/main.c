#include <stdio.h>
#include "ast.h"
#include "pretty.h"

int yyparse();
ASTNode  *ast;

int main()
{
    if (yyparse() == 0)
            printf("VALID\n");
    
    FILE *f = fopen("ast.min", "w");
    pretty_print(f, ast);

    return 0;
}
