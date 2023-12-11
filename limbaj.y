%{
#include <iostream>
#include <vector>
#include "IdList.h"
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);
class IdList ids;
%}

%union {
     char* string;
     int int_val;
     float float_val;
     bool bool_val;
     char char_val;
}
%token CONST ARRAY BGIN END USER_STRUCT WHILE FOR IF ELSE DO PRINT
%token<string> INT_TYPE FLOAT_TYPE CHAR_TYPE STRING_TYPE BOOL_TYPE ID

%token<int_val> INT_NR
%token<float_val> FLOAT_NR
%token<char_val> CHAR
%token<string> STRING
%token<bool_val> BOOL

%token ASSIGN EQ NEQ LT GT LE GE AND OR NOT

%start progr



%%
progr: user_structs global_vars program {printf("The programme is correct!\n");}
     ;

user_structs :  struct_decl ';'          
	      |  user_structs struct_decl ';'   
	      ;

struct_decl : USER_STRUCT ID struct_vars_block
               ;
struct_vars_block : '{' struct_vars '}'
struct_vars : struct_var ';'
               | struct_vars struct_var ';'
               ;
struct_var : TYPE ID 
               | ID ID // Custom classes
               | ARRAY '[' TYPE ',' CONST_NR ']' ID // Arrays 
               ;
global_vars : global_decl ';'
          | global_vars global_decl ';'
          ;
global_decl : TYPE ID                             // int x
               | TYPE ID ASSIGN EXPR              // int x := 5
               | TYPE ID ASSIGN ID                // int x := y
               | ID ID                            // MyStruct x; - primul ID e clasa, a doilea ID e numele variabilei
               | ID ID ASSIGN ID                  // MyStruct x = y;
               | ARRAY '[' TYPE ',' CONST_NR ']' ID    // Arrays; am gandit arrays ca fiind
                                                       // array[int,5] myArray; - asta e un exemplu
               | CONST TYPE ASSIGN EXPR      // Constant expressions
                                                  // const int x = 5;
               ;

program : BGIN list END  
     ;
list :  statement ';' 
     | list statement ';'
     ;

statement: ID ASSIGN ID
         | ID ASSIGN EXPR
         ;

// De implementat
// EXPR: 

//Temp rules
CONST_NR : INT_NR;
EXPR : INT_NR;

TYPE : INT_TYPE
     | FLOAT_TYPE
     | CHAR_TYPE
     | STRING_TYPE
     | BOOL_TYPE
     | ID
     ;

VALUE : INT_NR
     | FLOAT_NR
     | CHAR 
     | STRING 
     | BOOL
     ;
%%
void yyerror(const char * s){
printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse(); 
} 