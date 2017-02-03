%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "ast.h"
    
    extern char      *yytext;
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
%token <type>      TYPE_INT 
%token <type>      TYPE_FLOAT          
%token <type>      TYPE_STRING 
%token <intval>    INTLITERAL
%token <floatval>  FLOATLITERAL
%token <strval>    STRLITERAL
%token <ident>     IDENTIFIER

%type <type> type
%type <node> program dcls dcl stmts stmt exp

%start program

%left '+' '-'
%left '*' '/'
%precedence NEG

%%

program : dcls stmts
          { ast = make_ast_node_prog($1, $2); }
        ;

dcls    : dcl dcls
        | %empty
        ;

dcl     : VAR IDENTIFIER COLON type SEMICOLON
          { $$ = make_ast_node_decl($2, $4); }
        ;

type    : TYPE_INT      
        | TYPE_FLOAT    
        | TYPE_STRING   
        ;

stmts   : stmt stmts 
        | %empty
        ;

stmt    : READ IDENTIFIER SEMICOLON
          { $$ = make_ast_node_read($2); }
        | PRINT exp SEMICOLON
          { $$ = make_ast_node_print($2); }
        | IDENTIFIER '=' exp SEMICOLON
          { $$ = make_ast_node_assign($1, $3); }
        | IF exp THEN stmts ENDIF
          { $$ = make_ast_node_ifbranch($2, $4); }
        | IF exp THEN stmts ELSE stmts ENDIF
          { $$ = make_ast_node_ifelsebranch($2, $4, $6); }
        | WHILE exp DO stmts DONE
          { $$ = make_ast_node_whilebranch($2, $4); }
        ;

exp     : IDENTIFIER
          { $$ = make_ast_node_ident($1); }
        | INTLITERAL
          { $$ = make_ast_node_intlit($1); }
        | FLOATLITERAL
          { $$ = make_ast_node_floatlit($1); }
        | STRLITERAL
          { $$ = make_ast_node_strlit($1); }
        | exp '+' exp
          { $$ = make_ast_node_plusbop($1, $3); }
        | exp '-' exp
          { $$ = make_ast_node_minusbop($1, $3); }
        | exp '*' exp
          { $$ = make_ast_node_mulbop($1, $3); }
        | exp '/' exp
          { $$ = make_ast_node_divbop($1, $3); }
        | '-' exp %prec NEG
          { $$ = make_ast_node_minusuop($2); }
        | '(' exp ')'
          { $$ = make_ast_node_parenexp($2); }
        ;

%%

void yyerror(char const *msg)
{
    fprintf(stderr, "INVALID: %s on line %d\n", msg, yylineno);
    exit(1);
}
