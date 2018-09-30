#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <defer.h>
#include <debug.h>

#include "ast.h"
#include "pretty.h"
#include "symbol.h"
#include "typecheck.h"

int yyparse();
extern FILE *yyin;
extern SYM_TABLE *sym_table;
extern int sym_error;
extern int type_error;
ASTNode *ast;

char *change_file_extension (const char *path, const char *extension)
{
        char *fname, *res;
        const char slash = '/';

        fname = strrchr(path, slash);
        if (fname != NULL) {
                res = malloc(strlen(fname)+ strlen(extension) - 3); /* (3 = strlen(".min") - null byte) */
                sscanf(fname, "/%[^.].min", res);
        } else {
                res = malloc(strlen(path)+ strlen(extension) - 3); /* (3 = strlen(".min") - null byte) */
                sscanf(path, "%[^.].min", res);
        }
        
        strcat(res, extension);
       
        return res;
}   

int main(int argc, const char *argv[])
{
        int parse_res;
        char *pretty_out_fn, *sym_out_fn;
        FILE *pretty_f, *sym_f;

        if (argc != 2) {
                printf("Usage: minilang <script.min>\n");
                exit(1);
        }

        yyin = fopen(argv[1], "r");

        parse_res = yyparse();
        if (parse_res) {
                exit(1);
        }
        defer(free_sym_table(sym_table));
        defer(free_ast(ast));

        pretty_out_fn = change_file_extension(argv[1], ".pretty.min");
        defer(free(pretty_out_fn));

        sym_out_fn = change_file_extension(argv[1], ".symbol");
        defer(free(sym_out_fn));

        pretty_f = fopen(pretty_out_fn, "w");
        defer(fclose(pretty_f));

        DBG(("Printing ast to %s...\n", pretty_out_fn));
        pretty_print(pretty_f, ast, 0);

        sym_f = fopen(sym_out_fn, "w");
        defer(fclose(sym_f));

        DBG(("Printing symbol table to %s...\n", sym_out_fn));
        make_sym_table(sym_f, ast);
        if (sym_error) {
                exit(1);
        }

        DBG(("Typechecking program"));
        typecheck_prog(sym_table, ast);
        if (type_error) {
                exit(1);
        }

        printf("VALID\n");

        return 0;
}
