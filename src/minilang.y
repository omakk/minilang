%{
    #include <stdio.h>
    extern char *yytext;
    void yyerror();
%}

%union
{
    char    *keyword;
    char    *type;
    
    int     intliteral;
    float   floatliteral;
    char    *strliteral;
    char    *strconst;
}

%token                  COLON           ":"
%token                  SEMICOLON       ";"
%token <keyword>        VAR             "var"
%token <keyword>        WHILE           "while"
%token <keyword>        DO              "do"
%token <keyword>        DONE            "done"
%token <keyword>        IF              "if"
%token <keyword>        THEN            "then"
%token <keyword>        ELSE            "else"
%token <keyword>        ENDIF           "endif"
%token <keyword>        PRINT           "print"
%token <keyword>        READ            "read"
%token <type>           INT             "int"
%token <type>           FLOAT           "float"
%token <type>           STRING          "string"
%token <intliteral>     INTLITERAL
%token <floatliteral>   FLOATLITERAL
%token <strliteral>     STRLITERAL
%token <strconst>       IDENTIFIER

%type <type> type

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

type    : INT      
        | FLOAT    
        | STRING   
        ;

stmts   : stmt stmts 
        | %empty
        ;

stmt    : READ IDENTIFIER SEMICOLON
        | PRINT exp SEMICOLON
        | PRINT STRLITERAL SEMICOLON
        | IDENTIFIER '=' exp SEMICOLON
        | IDENTIFIER '=' STRLITERAL SEMICOLON
        | IF exp THEN stmts ifend ENDIF
        | WHILE exp DO stmts DONE
        ;

ifend   : ELSE stmts
        | %empty

exp     : IDENTIFIER
        | INTLITERAL
        | FLOATLITERAL
        | exp '+' exp
        | exp '-' exp
        | exp '*' exp
        | exp '/' exp
        | '-' exp %prec NEG
        | '(' exp ')'
        ;

%%

void yyerror()
{
    printf("INVALID: Syntax error before %s\n", yytext);
}
