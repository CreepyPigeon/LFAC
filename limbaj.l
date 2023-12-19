%{
#include <stdio.h>
#include <string>
#include "limbaj.tab.h"

int yycollumnno=1;

%}
%option noyywrap
%%

"int" {yylval.type = INT;return INT_TYPE;}
"float" {yylval.type = FLOAT;return FLOAT_TYPE;}
"char" {yylval.type = CHAR;return CHAR_TYPE;}
"string" {yylval.type = STRING;return STRING_TYPE;}
"bool" {yylval.type = BOOL;return BOOL_TYPE;}
"struct" {yylval.type = USER_STRUCT; return USER_STRUCT;}

"const" {return CONST;}
"array" {return ARRAY;}
"begin" {return BGIN;}
"end"   {return END;}

"print"     {return PRINT;}
"if"        {return IF;}
"else"      {return ELSE;}
"while"     {return WHILE;}
"do"        {return DO;}
"for"       {return FOR;}

("false"|"true")                    {yylval.bool_val = (yytext[0]=='t'); return BOOL;}
[_a-zA-Z][_a-zA-Z0-9]*              {yylval.string = strdup(yytext); return ID;} // Identificatori pt structs/variabile

"0"|[-]?[1-9][0-9]*                 {yylval.int_val = atoi(yytext); return INT_NR;}
("0"|[-]?[1-9][0-9]*)"."[0-9]+      {yylval.float_val = atof(yytext); return FLOAT_NR;}
\'(.)\'                             {yylval.char_val = yytext[1]; return CHAR;}
\"([^"\n]|\\\")*\"                  {   // Match la tot ce intre ghilimele mai putin ", \n, \"
                                        yylval.string = (char*)malloc(yyleng-1);
                                        strncpy(yylval.string, yytext+1, yyleng-2);
                                        return STRING;
                                    }

":=" {return ASSIGN;}
"==" {return EQ;}
"!=" {return NEQ;}
"<"  {return LT;}
"<=" {return LE;}
">"  {return GT;}
">=" {return GE;}
"&&" {return AND;}
"||" {return OR;}
"!"  {return NOT;}


[ \t\r]*\n {yylineno++;} //Some new line
[ \t]+ {} //Whitespaces


. {return yytext[0];} //Returnam orice caracter

 
