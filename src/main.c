#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "debug.h"
#include "pretty.h"
#include "symbol.h"

int yyparse();
extern FILE *yyin;
ASTNode  *ast;

char *change_file_extension (const char *s, const char *extension)
{
        char *dup, *fname, *res;
        const char slash = '/';

        dup = strdup(s);
        fname = strrchr(dup, slash);
        if (fname != NULL) {
                res = malloc(strlen(fname)+ strlen(extension) - 3); /* (3 = strlen(".min") - null tbyte) */
                sscanf(fname, "/%[^.].min", res);
        } else {
                res = malloc(strlen(dup)+ strlen(extension) - 3); /* (3 = strlen(".min") - null tbyte) */
                sscanf(dup, "%[^.].min", res);
        }
        
        strcat(res, extension);
       
        free(dup);

        return res;
}   

int main(int argc, const char *argv[])
{
    char *pretty_out_fn;
    char *sym_out_fn;
    FILE *pretty_f;
    FILE *sym_f;

    yyin = fopen(argv[1], "r");
    
    yyparse();
    
    pretty_out_fn = change_file_extension(argv[1], ".pretty.min");
    sym_out_fn    = change_file_extension(argv[1], ".symbol.txt");
    
    pretty_f = fopen(pretty_out_fn, "w");
    DBG(("Printing ast to %s...\n", pretty_out_fn));
    pretty_print(pretty_f, ast, 0);
    free(pretty_out_fn);
    fclose(pretty_f);
    
    sym_f = fopen(sym_out_fn, "w");
    DBG(("Printing symbol table to %s...\n", sym_out_fn));
    make_sym_table(sym_f, ast);
    free(sym_out_fn);
    fclose(sym_f);

    printf("VALID\n");

    return 0;
}
