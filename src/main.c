#include <stdio.h>

int yyparse();

int main()
{
   if( yyparse() == 0) printf("VALID\n");
}
