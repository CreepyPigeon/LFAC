%{
#include <stdio.h>
#include <string>
#include "limbaj.tab.h"

int yycollumnno=1;

%}
%option noyywrap
%%

"int" {yylval.string = strdup(yytext);return INT_TYPE;}
"float" {yylval.string = strdup(yytext);return FLOAT_TYPE;}
"char" {yylval.string = strdup(yytext);return CHAR_TYPE;}
"string" {yylval.string = strdup(yytext);return STRING_TYPE;}
"bool" {yylval.string = strdup(yytext);return BOOL_TYPE;}

"const" {return CONST;}
"array" {return ARRAY;}
"begin" {return BGIN;}
"end"   {return END;}

"struct"    {return USER_STRUCT;}
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

 
