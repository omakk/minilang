%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "ast.h"
    #include "debug.h"
    
    extern int      yylineno;
    extern ASTNode      *ast;
    
    void yyerror(char const *msg);
%}

%union
{
    char               *type;
    int               intval;
    float           floatval;
    char             *strval;
    char              *ident;
    struct  ASTNode    *node;
}

%define parse.lac full
%define parse.error verbose

%token  COLON
%token  SEMICOLON
%token  VAR
%token  WHILE
%token  DO
%token  DONE
%token  IF
%token  THEN
%token  ELSE
%token  ENDIF
%token  PRINT
%token  READ
%token <type>      TYPE_INT TYPE_FLOAT TYPE_STRING
%token <intval>    INTLITERAL
%token <floatval>  FLOATLITERAL
%token <strval>    STRLITERAL
%token <ident>     IDENTIFIER

%type <type> type
%type <node> program dcls dcl stmts stmt exp

%start program

%left '+' '-'
%left '*' '/'
%right NEG

%%

program : dcls stmts
          { ast = make_ast_node_prog($1, $2, @1.first_line); }
        ;

dcls    : dcl dcls
          { $$ = prepend_dcl($1, $2); }
        | %empty
          { $$ = NULL; }
        ;

dcl     : VAR IDENTIFIER COLON type SEMICOLON
          { $$ = make_ast_node_decl($2, make_type($4), @1.first_line); }
        ;

type    : TYPE_INT      
          { $$ = "int"; }
        | TYPE_FLOAT
          { $$ = "float"; }
        | TYPE_STRING
          { $$ = "string"; }
        ;

stmts   : stmt stmts 
          { $$ = prepend_stmt($1, $2); }
        | %empty
          { $$ = NULL; }
        ;

stmt    : READ IDENTIFIER SEMICOLON
          { $$ = make_ast_node_read($2, @1.first_line); }
        | PRINT exp SEMICOLON
          { $$ = make_ast_node_print($2, @1.first_line); }
        | IDENTIFIER '=' exp SEMICOLON
          { $$ = make_ast_node_assign($1, $3, @1.first_line); }
        | IF exp THEN stmts ENDIF
          { $$ = make_ast_node_ifbranch($2, $4, @1.first_line); }
        | IF exp THEN stmts ELSE stmts ENDIF
          { $$ = make_ast_node_ifelsebranch($2, $4, $6, @1.first_line); }
        | WHILE exp DO stmts DONE
          { $$ = make_ast_node_whilebranch($2, $4, @1.first_line); }
        ;

exp     : IDENTIFIER
          { $$ = make_ast_node_ident($1, @1.first_line); }
        | INTLITERAL
          { $$ = make_ast_node_intlit($1, @1.first_line); }
        | FLOATLITERAL
          { $$ = make_ast_node_floatlit($1, @1.first_line); }
        | STRLITERAL
          { $$ = make_ast_node_strlit($1, @1.first_line); }
        | exp '+' exp
          { $$ = make_ast_node_plusbop($1, $3, @2.first_line); }
        | exp '-' exp
          { $$ = make_ast_node_minusbop($1, $3, @2.first_line); }
        | exp '*' exp
          { $$ = make_ast_node_mulbop($1, $3, @2.first_line); }
        | exp '/' exp
          { $$ = make_ast_node_divbop($1, $3, @2.first_line); }
        | '-' exp %prec NEG
          { $$ = make_ast_node_minusuop($2, @1.first_line); }
        | '(' exp ')'
          { $$ = $2; }
        ;

%%

void yyerror(char const *msg)
{
    fprintf(stderr, "INVALID: %s on line %d\n", msg, yylineno);
    exit(1);
}
