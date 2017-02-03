%{
#include <string.h>
#include "y.tab.h"
#include "debug.h"
void yyerror(char const *);
%}

%option yylineno

DIGIT   [0-9]
IDENT   [a-zA-Z_][a-zA-Z0-9_]*
INT     0|[1-9][0-9]*
%%

[ \t\n]+                    /* Ignore */

"var"                       { DBG(("tVAR(%s)\n", yytext)); return VAR; }
"while"                     { DBG(("tWHILE(%s)\n", yytext)); return WHILE; }
"do"                        { DBG(("tDO(%s)\n", yytext)); return DO; }
"done"                      { DBG(("tDONE(%s)\n", yytext)); return DONE; }
"if"                        { DBG(("tIF(%s)\n", yytext)); return IF; }
"then"                      { DBG(("tTHEN(%s)\n", yytext)); return THEN; }
"else"                      { DBG(("tELSE(%s)\n", yytext)); return ELSE; }
"endif"                     { DBG(("tENDIF(%s)\n", yytext)); return ENDIF; }
"print"                     { DBG(("tPRINT(%s)\n", yytext)); return PRINT; }
"read"                      { DBG(("tREAD(%s)\n", yytext)); return READ; }

"float"                     { DBG(("tTYPE_FLOAT(%s)\n", yytext));
                              yylval.type = "float";
                              return TYPE_FLOAT; }
"int"                       { DBG(("tTYPE_INT(%s)\n", yytext));
                              yylval.type = "int";
                              return TYPE_INT; }
"string"                    { DBG(("tTYPE_STRING(%s)\n", yytext));
                              yylval.type = "string";
                              return TYPE_STRING; }

{IDENT}                     { DBG(("tIDENT(%s)\n", yytext));
                              yylval.ident = strdup(yytext);
                              return IDENTIFIER; } 
{INT}                       { DBG(("tINT(%s)\n", yytext));
                              yylval.intval = atoi(yytext);
                              return INTLITERAL; } 
({INT}\.{DIGIT}+)           { DBG(("tFLOAT(%s)\n", yytext)); 
                              yylval.floatval = atof(yytext);
                              return FLOATLITERAL; }

\"(\\[abfnrtvb\"\\]|[^\\"])*\"               { /*
                                                Citation for regex:
                                                http://www.lysator.liu.se/c/ANSI-C-grammar-l.html
                                              */
                                                DBG(("tSTRING(%s)\n", yytext));
                                                yylval.strval = strdup(yytext);
                                                return STRLITERAL; } 

";"                         { DBG(("tSEMICOLON(%s)\n", yytext)); return SEMICOLON; }
":"                         { DBG(("tCOLON(%s)\n", yytext)); return COLON; }
"="                         { DBG(("tEQUAL(%s)\n", yytext)); return '='; } 
"+"                         { DBG(("tPLUS(%s)\n", yytext)); return '+'; }
"-"                         { DBG(("tMINUS(%s)\n", yytext)); return '-'; }
"*"                         { DBG(("tTIMES(%s)\n", yytext)); return '*'; }
"/"                         { DBG(("tDIV(%s)\n", yytext)); return '/'; }
"("                         { DBG(("tOPEN_P(%s)\n", yytext)); return '('; }
")"                         { DBG(("tCLOSE_P(%s)\n", yytext)); return ')'; }

(\/\/).*                    { /* Single-line comment ignore */ }
.                           { yyerror("syntax error"); }
%%
