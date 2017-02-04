#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "pretty.h"

int yyparse();
extern FILE *yyin;
ASTNode  *ast;

char *pretty_output_file (char *s)
{
    char *res = s;
    while (*res != '.') res++;
    
    strcpy(res, ".pretty.min");

    return s;
}   

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    if (yyparse() == 0)
            printf("VALID\n");
    
    //printf("%s\n", pretty_output_file(argv[1]));
    FILE *f = fopen(pretty_output_file(argv[1]), "w");
    pretty_print(f, ast);

    return 0;
}
