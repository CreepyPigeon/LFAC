%{
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "IdList.h"

using namespace std;

extern FILE* yyin;
extern char* yytext;
extern int yylineno;

extern int yylex();

void yyerror(const char * s);

bool searchClasses(char* className);

Variable currentVariable;

vector<string> customClasses;
vector<Variable> declaredVariables;

%}

%union{
     char* string;
     int int_val;
     float float_val;
     bool bool_val;
     char char_val;
     Type type;
     Variable* variable;
}
%token CONST ARRAY BGIN END WHILE FOR IF ELSE DO PRINT
%token<string> ID
%token<type> INT_TYPE FLOAT_TYPE CHAR_TYPE STRING_TYPE BOOL_TYPE USER_STRUCT

%left '+' '-'
%left '*' '/'
%nonassoc '!'
%left '(' ')'
%nonassoc EQ NEQ LT LE GT GE NOT

%token<int_val> INT_NR
%token<float_val> FLOAT_NR
%token<char_val> CHAR
%token<string> STRING
%token<bool_val> BOOL

%token ASSIGN EQ NEQ LT GT LE GE AND OR NOT

%type <int_val> ARITH_EXPR EXPR
%type <bool_val> BOOL_EXPR
%type <variable> struct_var
%type <type> TYPE

%start progr

%%
progr: user_structs global_vars program {printf("The programme is correct!\n");}
     ;

user_structs :  struct_decl ';'          
	      |  user_structs struct_decl ';'   
	      ;

struct_decl : USER_STRUCT ID struct_vars_block {
                    if(searchClasses($2)){
                         yyerror("struct with this name already exists");
                         return;
                    }
                    customClasses.push_back($2);
                    strcpy(currentVariable.name, $2);
                    currentVariable.type = $1;
                    currentVariable.isConst = false;
                    currentVariable.isArray = false;
               }
               ;
struct_vars_block : '{' struct_vars '}'
               ;
struct_vars : struct_var ';' {currentVariable.structVars.push_back($1);}
               | struct_vars struct_var ';' {currentVariable.structVars.push_back($2);}
               ;
struct_var : TYPE ID {$$ = new Variable; $$->type = $1; strcpy($$->name, $2);}
               | ID ID {$$ = new Variable; $$->type = USER_STRUCT; 
                    if(searchClasses($2)){
                         yyerror("struct with this name already exists");
                         return;
                    }
                    strcpy($$->name, $2);
               }// Custom classes
               | ARRAY '[' TYPE ',' CONST_NR ']' ID // Arrays 
               ;
global_vars : global_decl ';'
          | global_vars global_decl ';'
          ;
global_decl : TYPE ID                             // int x
               | TYPE ID ASSIGN EXPR              // int x := 5
               | TYPE ID ASSIGN ID                // int x := y
               | ID ID                            // MyStruct x; - primul ID e clasa, a doilea ID e numele variabilei
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
         | ID ASSIGN BOOL_EXPR
         ;

// De implementat
// EXPR: 

EXPR : ARITH_EXPR
     | BOOL_EXPR
     ;

ARITH_EXPR : ARITH_EXPR '+' ARITH_EXPR {$$ = $1 + $3; }
           | ARITH_EXPR '-' ARITH_EXPR {$$ = $1 - $3; }
           | ARITH_EXPR '*' ARITH_EXPR {$$ = $1 * $3; }
           | ARITH_EXPR '/' ARITH_EXPR {$$ = $1 / $3; }
           | '(' ARITH_EXPR ')' {$$ = $2; }
           | INT_NR {$$ = $1; }
           ;

BOOL_EXPR : BOOL_EXPR EQ BOOL_EXPR {$$ = $1 == $3; }
          | BOOL_EXPR NEQ BOOL_EXPR {$$ = $1 != $3; }
          | BOOL_EXPR LT BOOL_EXPR {$$ = $1 < $3; }
          | BOOL_EXPR LE BOOL_EXPR {$$ = $1 <= $3; }
          | BOOL_EXPR GT BOOL_EXPR {$$ = $1 > $3; }
          | BOOL_EXPR GE BOOL_EXPR {$$ = $1 >= $3; }
          | ARITH_EXPR {$$ = $1; }
          ;
//Temp rules
CONST_NR : INT_NR;
EXPR : INT_NR;

TYPE : INT_TYPE
     | FLOAT_TYPE
     | CHAR_TYPE
     | STRING_TYPE
     | BOOL_TYPE
     | ID {if(searchClasses($1)){
               $$ = USER_STRUCT;
          }}
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

bool searchClasses(char* className){
     for(int i = 0; i < customClasses.size(); i++){
          if(customClasses[i] == className){
               return true;
          }
     }
     return false;
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse(); 
} 