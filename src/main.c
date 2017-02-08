#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "pretty.h"

int yyparse();
extern FILE *yyin;
ASTNode  *ast;

char *pretty_output_file (char *s)
{
        char *fname;
        const char slash = '/';

        fname = strrchr(s, slash);
        char *res = (char *) malloc(sizeof(fname)+8);
        sscanf(fname, "/%[^.].min", res);
        res = strcat(res, ".pretty.min");
        
        return res;
}   

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    if (yyparse() == 0)
            printf("VALID\n");
    
    //printf("%s\n", pretty_output_file(argv[1]));
    char *out_fn = pretty_output_file(argv[1]);
    FILE *f = fopen(out_fn, "w");
    printf("Printing ast to %s...\n", out_fn);
    pretty_print(f, ast, 0);
    fclose(f);

    return 0;
}
