%{
#include "y.tab.h"
%}

DIGIT   [0-9]
IDENT   [a-zA-Z_][a-zA-Z0-9_]*
INT     0|[1-9][0-9]*
%%

[ \t\n]+            /* Ignore */

"var"               { return VAR; }
"while"             { return WHILE; }
"do"                { return DO; }
"done"              { return DONE; }
"if"                { return IF; }
"then"              { return THEN; }
"else"              { return ELSE; }
"endif"             { return ENDIF; }
"float"             { return FLOAT; }
"int"               { return INT; }
"string"            { return STRING; }
"print"             { return PRINT; }
"read"              { return READ; }

{IDENT}             { return IDENTIFIER; }
{INT}               { return INTLITERAL; }
{INT}"."{DIGIT}+    { return FLOATLITERAL; }
\"(\\.|[^\\"])*\"   { return STRLITERAL; }

";"                 { return SEMICOLON; }
":"                 { return COLON; }
"="                 { return '='; } 
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"("                 { return '('; }
")"                 { return ')'; }

(\/\/).*            { /* Single-line comment ignore */ }
.                   { /* Ignore everything else */ }
%%
