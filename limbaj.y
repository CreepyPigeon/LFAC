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
}
%token  BGIN END ASSIGN INT_NR FLOAT_NR CONST_TYPE USER_STRUCT
%token<string> ID TYPE
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

struct_var : TYPE ID 

global_vars : decl ';'
          | global_vars decl ';'


decl       :  TYPE ID { if(!ids.existsVar($2)) {
                          ids.addVar($1,$2);
                     }
                    }
           | TYPE ID '(' list_param ')'  
           | TYPE ID '(' ')' 
     
           ;

list_param : param
            | list_param ','  param 
            ;
            
param : TYPE ID 
      ; 
      

program : BGIN list END  
     ;
     

list :  statement ';' 
     | list statement ';'
     ;

statement: ID ASSIGN ID
         | ID ASSIGN value  		 
         | ID '(' call_list ')'
         ;
        
call_list : value
           | call_list ',' value
           ;

value : INT_NR
     | FLOAT_NR
     | CHAR 
     | STRING 
     ;
%%
void yyerror(const char * s){
printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     cout << "Variables:" <<endl;
     ids.printVars();
    
} 