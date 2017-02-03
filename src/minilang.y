%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "ast.h"
    extern char *yytext;
    extern int yylineno;
    void yyerror(char const *msg);
%}

%union
{
    char    *type;
    int     intval;
    float   floatval;
    char    *strval;
    char    *ident;
    ASTNode *node;
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

program : dcls stmts ;

dcls    : dcl dcls
        | %empty
        ;

dcl     : VAR IDENTIFIER COLON type SEMICOLON ;

type    : TYPE_INT      
        | TYPE_FLOAT    
        | TYPE_STRING   
        ;

stmts   : stmt stmts 
        | %empty
        ;

stmt    : READ IDENTIFIER SEMICOLON
        | PRINT exp SEMICOLON
        | IDENTIFIER '=' exp SEMICOLON
        | IF exp THEN stmts ENDIF
        | IF exp THEN stmts ELSE stmts ENDIF
        | WHILE exp DO stmts DONE
        ;

exp     : IDENTIFIER
        | INTLITERAL
        | FLOATLITERAL
        | STRLITERAL
        | exp '+' exp
        | exp '-' exp
        | exp '*' exp
        | exp '/' exp
        | '-' exp %prec NEG
        | '(' exp ')'
        ;

%%

void yyerror(char const *msg)
{
    fprintf(stderr, "INVALID: %s on line %d\n", msg, yylineno);
    exit(1);
}
