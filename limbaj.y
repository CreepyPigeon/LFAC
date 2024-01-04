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
Variable searchForClass(char* className);
bool searchForVariable(char* varName,vector<Variable> searchLocation);
const char* typeToString(int type);

struct Variable* currentVariable;
int scope = 0;
vector<Variable> classDefinitions;
vector<Variable> declaredVariables;

void increaseScope(){
     scope++;
}
void decreaseScope(){
     scope--;
}

%}

%union{
     int type;
     char* string;
     int int_val;
     float float_val;
     bool bool_val;
     char char_val;
     struct Variable* variable;
     struct Expression* expr;
}
%token CONST ARRAY BGIN END WHILE FOR IF ELSE DO PRINT EVAL TYPEOF
%token<string> ID
%token<type> INT_TYPE FLOAT_TYPE CHAR_TYPE STRING_TYPE BOOL_TYPE USER_STRUCT


%right ASSIGN 
%nonassoc EQ NEQ 
%left AND OR
%left LE GE LT GT
%left '+' '-'
%left '*' '/' '%'
%nonassoc NOT
%left '(' ')' '[' ']'

%token<int_val> INT_NR
%token<float_val> FLOAT_NR
%token<char_val> CHAR
%token<string> STRING
%token<bool_val> BOOL

%type <type> TYPE;
%type <expr> EXPR;
%type <variable> struct_var;

%start progr

%%
progr: user_structs global_vars program {
          printf("The programme is correct!\n");
     }
     ;

user_structs :  struct_decl ';'          
	      |  user_structs struct_decl ';'   
	      | ; /* Nimic */

struct_decl : USER_STRUCT ID {
                    if(searchClasses($2)){
                         yyerror("struct with this name already declared");
                         return 0;
                    }
                    currentVariable = new Variable;
                    currentVariable->type = $1;
                    strcpy(currentVariable->typeName, $2);
               } struct_vars_block {
                    classDefinitions.push_back(*currentVariable);
                    debugPrint(*currentVariable);
                    currentVariable = NULL;
               }
               ;
struct_vars_block : '{' struct_vars '}'
               ;
struct_vars : struct_var ';' {currentVariable->structVars.push_back(*$1);}
               | struct_vars struct_var ';' {currentVariable->structVars.push_back(*$2);}
               ;
struct_var : TYPE ID {
                         if(searchForVariable($2,currentVariable->structVars)){
                              yyerror("member with this name already declared");
                              return 0;
                         }
                         $$ = new Variable; $$->type = $1; strcpy($$->name, $2);
                         strcpy($$->typeName, typeToString($1));
                    }
               | ID ID {
                    if(searchForVariable($2,currentVariable->structVars)){
                         yyerror("member with this name already declared");
                         return 0;
                    }
                    if(searchClasses($1) == 0){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    $$ = new Variable;
                    // Stim sigur ca o sa gasim clasa, deoarece am verificat daca exista
                    struct Variable temp = searchForClass($1);
                    $$->structVars = temp.structVars;
                    $$->type = 5;
                    //debugPrint(*$$);
                    strcpy($$->typeName, $1);
                    strcpy($$->name, $2);
               }// Custom classes
               | ARRAY '[' TYPE ',' EXPR ']' ID {
                    $$ = new Variable;
                    $$->isArray = true;
                    $$->type = $3;
                    //$$->arraySize = $5;
                    strcpy($$->name, $7);
               }// Arrays 
               ;
global_vars : global_decl ';'
          | global_vars global_decl ';'
          ;
global_decl : TYPE ID                             // int x
               | TYPE ID ASSIGN EXPR              // int x := 5
               | TYPE ID ASSIGN ID                // int x := y
               | ID ID                            // MyStruct x; - primul ID e clasa, a doilea ID e numele variabilei
               | ARRAY '[' TYPE ',' EXPR ']' ID    // Arrays; am gandit arrays ca fiind
                                                       // array[int,5] myArray; - asta e un exemplu
               | CONST TYPE ASSIGN EXPR      // Constant expressions
                                                  // const int x = 5;
               ;

program : BGIN {increaseScope();} list END {decreaseScope();}  
     ;
list :  statement ';' 
     | list statement ';'
     | FOR '(' EXPR ';' EXPR ';' EXPR ')' list ';'
     | WHILE '(' EXPR ')' list ';'
     | IF '(' EXPR ')' list ';'
     | IF '(' EXPR ')' list ELSE list ';'
     | DO list WHILE '(' EXPR ')' ';'
     | '{' {increaseScope();} list '}' {decreaseScope();}
     ;

statement: ID ASSIGN ID
         | ID ASSIGN EXPR
         | ID ASSIGN 
         ;

// PLACEHOLDER
EXPR: INT_NR;

TYPE : INT_TYPE
     | FLOAT_TYPE
     | CHAR_TYPE
     | STRING_TYPE
     | BOOL_TYPE
     ;
%%
void yyerror(const char * s){
     printf("error: %s at line:%d\n",s,yylineno);
}

const char* typeToString(int type){
     switch(type){
          case 0:
               return "int";
          case 1:
               return "float";
          case 2:
               return "bool";
          case 3:
               return "char";
          case 4:
               return "string";
          default:
               return "unknown";
     }
}

bool searchClasses(char* className){
     string classNameStr = className;
     for(int i = 0; i < classDefinitions.size(); i++){
          string toCompareStr = classDefinitions[i].typeName;
          if(classNameStr == toCompareStr)
               return true;
     }
     return false;
}

Variable searchForClass(char* className){
     string classNameStr = className;
     for(int i = 0; i < classDefinitions.size(); i++){
          string toCompareStr = classDefinitions[i].typeName;
          if(classNameStr == toCompareStr)
               return classDefinitions[i];
     }
     return Variable{0};
}

bool searchForVariable(char* varName,vector<Variable> searchLocation){
     string varNameStr = varName;
     for(int i = 0; i < searchLocation.size(); i++){
          string toCompareStr = searchLocation[i].name;
          if(varNameStr == toCompareStr)
               return true;
     }
     return false;
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse(); 
} 