%{
#include <stdio.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"int"|"float"|"char"|"string"|"bool" {yylval.string = strdup(yytext);return TYPE;}
"const" {yylval.string = strdup(yytext);return CONST_TYPE;}
"struct" {yylval.string = strdup(yytext);return USER_STRUCT;}
"array" {yylval.string = strdup(yytext);return ARRAY;}
"begin" {return BGIN;}
"end" {return END;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.string = strdup(yytext); return ID;}
":=" {return ASSIGN;}
"0"|[-]?[1-9][0-9]* {return INT_NR;}
("0"|[-]?[1-9][0-9]*)"."[0-9]+ {return FLOAT_NR;}
\'(.)\' {return CHAR;}
\"[^".]*\" {return STRING;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}

 
