#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "pretty.h"

int yyparse();
extern FILE *yyin;
ASTNode  *ast;

char *pretty_output_file (char *s)
{
        char *fname, *res;
        const char slash = '/';

        fname = strrchr(s, slash);
        res = (char *) malloc(sizeof(fname)+8);
        if (fname != NULL)
                sscanf(fname, "/%[^.].min", res);
        else
                sscanf(s, "%[^.].%*s", res);
        
        res = strcat(res, ".pretty.min");
        
        return res;
}   

int main(int argc, char *argv[])
{
    char *out_fn;
    FILE *f;

    yyin = fopen(argv[1], "r");
    if (yyparse() == 0)
            printf("VALID\n");
    
    out_fn = pretty_output_file(argv[1]);
    f = fopen(out_fn, "w");
    printf("Printing ast to %s...\n", out_fn);
    pretty_print(f, ast, 0);
    
    free(out_fn);
    fclose(f);

    return 0;
}
