%{
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "utility.h"

using namespace std;

struct Variable* currentVariable;
struct Function* currentFunction;
struct Func_Params* currentFuncParams;

vector<Variable> classDefinitions;
vector<Variable> declaredVariables;
vector<Function> declaredFunctions;

%}

%union{
     int type;
     char* string;
     int int_val;
     float float_val;
     bool bool_val;
     char char_val;
     struct Variable* variable;
     struct Ast* ast;
     struct Function* function;
     struct Func_Params* func_param;
}

%token CONST ARRAY BGIN END WHILE FOR IF ELSE DO PRINT EVAL TYPEOF RETURN
%token<string> ID
%token<type> INT_TYPE FLOAT_TYPE CHAR_TYPE STRING_TYPE BOOL_TYPE USER_STRUCT

%right ASSIGN 
%nonassoc EQ NEQ 
%left AND OR
%left LE GE LT GT
%left '+' '-' '*' '/' '%'
%nonassoc NOT
%left '(' ')' '[' ']'

%precedence NOELSE
%precedence ELSE

%token<int_val> INT_NR
%token<float_val> FLOAT_NR
%token<char_val> CHAR
%token<string> STRING
%token<bool_val> BOOL

%type <type> TYPE;
%type <ast> EXPR;
%type <variable> struct_var;
%type <func_param> func_decl_list;
%type <func_param> func_list;
%type <variable> func_param;
%type <variable> var_access;
%type <function> func_call;

%start progr

%%
progr: user_structs functions global_vars program {
               printf("Program compiled successfully\n");
     }
     | user_structs functions program {
               printf("Program compiled successfully\n");
     }
     | functions global_vars program {
               printf("Program compiled successfully\n");
     }
     | user_structs program {
               printf("Program compiled successfully\n");
     }
     | functions program {
               printf("Program compiled successfully\n");
     }
     | global_vars program {
               printf("Program compiled successfully\n");
     }
     | program {
               printf("Program compiled successfully\n");
     }
     ;

user_structs :  struct_decl ';'          
	      |  user_structs struct_decl ';'
           ;

struct_decl : USER_STRUCT ID {
                    if(searchClasses($2)){
                         yyerror("struct with this name already declared");
                         return 0;
                    }
                    newVar(currentVariable, $1, $2,false, false, false, scope);
                    strcpy(currentVariable->typeName, $2);
               } struct_vars_block {
                    classDefinitions.push_back(*currentVariable);
                    debugPrintVar(*currentVariable);
                    currentVariable = NULL;
               }
               ;
struct_vars_block : '{' struct_vars '}'
               ;
struct_vars : struct_var ';' {currentVariable->structVars.push_back(*$1);}
               | struct_vars struct_var ';' {currentVariable->structVars.push_back(*$2);}
               ;
struct_var : TYPE ID {
                         if(searchForVariable($2,currentVariable->structVars)>-1){
                              yyerror("member with this name already declared");
                              return 0;
                         }
                         newVar($$, $1, $2,false, false, false, scope);
                    }
               | ID ID {
                    if(searchForVariable($2,currentVariable->structVars)>-1){
                         yyerror("member with this name already declared");
                         return 0;
                    }
                    if(!searchClasses($1)){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    newVar($$,5,$2,false,false,false,scope);
                    // Stim sigur ca o sa gasim clasa, deoarece am verificat daca exista
                    struct Variable temp = searchForClass($1);
                    strcpy($$->typeName, $1);
                    $$->structVars = temp.structVars;
               }// Custom classes
               | ARRAY '[' TYPE ';' EXPR ']' ID {
                    evalAST($5);
                    if($5->type != 0){
                         yyerror("array size must be an integer");
                         return 0;
                    }
                    newVar($$, $3, $7,false, true, false, scope);
                    $$->arraySize = $5->int_val;
                    if($$->arraySize <= 0){
                         yyerror("array size must be positive");
                         return 0;
                    }
                    for(int i = 0; i < $$->arraySize; i++){
                         struct Variable* temp = new Variable;
                         temp->type = $3;
                         strcpy(temp->typeName, typeToString($3));
                         $$->arrayElements.push_back(*temp);
                    }
                    freeAST($5);
               }// Arrays 
               ;


// FUNCTION DECLARATIONS
functions: func_decl {
               declaredFunctions.push_back(*currentFunction);
               debugPrintFunc(*currentFunction);
               currentFunction = NULL;
          }
         | functions func_decl {
               declaredFunctions.push_back(*currentFunction);
               debugPrintFunc(*currentFunction);
               currentFunction = NULL;
          }
         ;

func_decl : TYPE ID '(' {currentFuncParams = new Func_Params;} {increaseScope($2);} func_decl_list ')' '{' list RETURN EXPR ';' '}' {
               decreaseScope();
               if(searchForFunction($2)>-1){
                    yyerror("function with this name already declared");
                    return 0;
               }
               currentFunction = new Function;
               currentFunction->type = $1;
               strcpy(currentFunction->typeName, typeToString($1));
               strcpy(currentFunction->name, $2);
               currentFunction->params = *currentFuncParams;
               if($11->type != currentFunction->type){
                    yyerror("function return type does not match");
                    return 0;
               }
          }
          | TYPE ID '(' ')' '{' {increaseScope($2);} list RETURN EXPR ';' '}' {
               decreaseScope();
               if(searchForFunction($2)>-1){
                    yyerror("function with this name already declared");
                    return 0;
               }
               currentFunction = new Function;
               currentFunction->type = $1;
               strcpy(currentFunction->typeName, typeToString($1));
               strcpy(currentFunction->name, $2);
               if($9->type != currentFunction->type){
                    yyerror("function return type does not match");
                    return 0;
               }
          }
          ;

func_decl_list : func_param {
                    if(searchForVariable($1->name,currentFuncParams->params)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    currentFuncParams->params.push_back(*$1);declaredVariables.push_back(*$1);
               }
               | func_decl_list ',' func_param {
                    if(searchForVariable($3->name,currentFuncParams->params)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    currentFuncParams->params.push_back(*$3);declaredVariables.push_back(*$3);
               }
               ;

func_param : TYPE ID {
               newVar($$, $1, $2,false, false, false, scope);
          }
           | ID ID {$$ = new Variable; if(!searchClasses($1)){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    newVar($$,5,$2,false,false,false,scope);
                    struct Variable temp = searchForClass($1);
                    $$->structVars = temp.structVars;
                    //debugPrint(*$$);
                    strcpy($$->typeName, $1);
               }
           ;


// GLOBAL VARIABLES
global_vars : var_decl ';'
          | global_vars var_decl ';'
          ;
var_decl : TYPE ID{
                    if(searchForVariable($2,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable;
                    newVar(var, $1, $2,false, false, false, scope);
                    debugPrintVarDetailed(*var);
                    declaredVariables.push_back(*var);
               }// int x
               | TYPE ID ASSIGN EXPR{
                    if(searchForVariable($2,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    evalAST($4);
                    newVar(var, $1, $2,false, false, true, scope);
                    if(var->type != $4->type){
                         yyerror("variable types do not match");
                         return 0;
                    }
                    switch($1){
                         case 0:
                              var->int_val = $4->int_val;
                              break;
                         case 1:
                              var->float_val = $4->float_val;
                              break;
                         case 2:
                              var->bool_val = $4->bool_val;
                              break;
                         case 3:
                              var->char_val = $4->char_val;
                              break;
                         case 4:
                              strcpy(var->string, $4->string);
                              break;
                    }
                    debugPrintVarDetailed(*var);
                    declaredVariables.push_back(*var);
                    freeAST($4);
               }// int x := 5
               /* | TYPE ID ASSIGN ID{
                    if(searchForVariable($2,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    int other_var = searchForVariable($4,declaredVariables);
                    if(other_var==-1){
                         yyerror("variable with this name not declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, $2);
                    var->type = $1; 
                    if(var->type != declaredVariables[other_var].type){
                         yyerror("variable types do not match");
                         return 0;
                    }
                    if(declaredVariables[other_var].isArray){
                         yyerror("cannot assign array to variable");
                         return 0;
                    }
                    if(declaredVariables[other_var].isInit == 0){
                         yyerror("cannot assign uninitialized variable");
                         return 0;
                    }
                    strcpy(var->typeName, typeToString($1));
                    var->scope = scope;
                    switch($1){
                         case 0:
                              var->int_val = declaredVariables[other_var].int_val;
                              break;
                         case 1:
                              var->float_val = declaredVariables[other_var].float_val;
                              break;
                         case 2:
                              var->bool_val = declaredVariables[other_var].bool_val;
                              break;
                         case 3:
                              var->char_val = declaredVariables[other_var].char_val;
                              break;
                         case 4:
                              strcpy(var->string, declaredVariables[other_var].string);
                              break;
                    }
                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }// int x := y */
               | ID ID{
                    if(searchForVariable($2,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    if(!searchClasses($1)){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    struct Variable* var = new Variable;
                    newVar(var,5,$2,false,false,false,scope);
                    struct Variable temp = searchForClass($1);
                    strcpy(var->typeName, $1);
                    debugPrintVarDetailed(*var);
                    var->structVars = temp.structVars;
                    declaredVariables.push_back(*var);
               }// MyStruct x; - primul ID e clasa, a doilea ID e numele variabilei
               | ARRAY '[' TYPE ';' EXPR ']' ID{
                    if(searchForVariable($7,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable;
                    newVar(var, $3, $7,false, true, false, scope);
                    evalAST($5);
                    if($5->type != 0){
                         yyerror("array size must be an integer");
                         return 0;
                    }
                    var->arraySize = $5->int_val;
                    if(var->arraySize <= 0){
                         yyerror("array size must be positive");
                         return 0;
                    }
                    for(int i = 0; i < var->arraySize; i++){
                         struct Variable* temp = new Variable;
                         char name[]="";
                         newVar(temp, $3,name,false, false, false, scope);
                         var->arrayElements.push_back(*temp);
                    }
                    debugPrintVarDetailed(*var);
                    declaredVariables.push_back(*var);
                    freeAST($5);
               }// Arrays; am gandit arrays ca fiind
                // array[int,5] myArray; - asta e un exemplu
               | CONST TYPE ID ASSIGN EXPR{
                    if(searchForVariable($3,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    newVar(var, $2, $3,true, false, true, scope);
                    evalAST($5);
                    if(var->type != $5->type){
                         yyerror("variable types do not match");
                         return 0;
                    }
                    switch($2){
                         case 0:
                              var->int_val = $5->int_val;
                              break;
                         case 1:
                              var->float_val = $5->float_val;
                              break;
                         case 2:
                              var->bool_val = $5->bool_val;
                              break;
                         case 3:
                              var->char_val = $5->char_val;
                              break;
                         case 4:
                              strcpy(var->string, $5->string);
                              break;
                    }
                    debugPrintVarDetailed(*var);
                    declaredVariables.push_back(*var);
                    freeAST($5);
               }// const int x := 5
               ;

program : BGIN {char newScope[] = "main";increaseScope(newScope);} list END {decreaseScope();}  
     ;
list : statement 
     | list statement 
     ;

statement : var_access ASSIGN EXPR ';'{
               if($1->isConst){
                    yyerror("cannot assign to const variable");
                    return 0;
               }
               evalAST($3);
               if($1->type != $3->type){
                    yyerror("variable types do not match");
                    return 0;
               }
               if($1->isArray){
                    yyerror("cannot assign array to variable");
                    return 0;
               }
               switch($1->type){
                    case 0:
                         $1->int_val = $3->int_val;
                         break;
                    case 1:
                         $1->float_val = $3->float_val;
                         break;
                    case 2:
                         $1->bool_val = $3->bool_val;
                         break;
                    case 3:
                         $1->char_val = $3->char_val;
                         break;
                    case 4:
                         strcpy($1->string, $3->string);
                         break;
               }
               debugPrintVarDetailed(*$1);
               freeAST($3);
          }
          | func_call
          | '{' {char newScope[100]; sprintf(newScope,"scop %d",scope);increaseScope(newScope);} list '}' {decreaseScope();}
          | FOR '(' var_access ASSIGN EXPR ';' EXPR ';' EXPR ')' '{' {char newScope[] = "for";increaseScope(newScope);} list '}' {decreaseScope();}
          | WHILE '(' EXPR ')' '{' {char newScope[] = "while";increaseScope(newScope);} list '}' {
               decreaseScope();
               evalAST($3);
               if($3->type != 2){
                    yyerror("while condition must be a boolean");
                    return 0;}
               freeAST($3);
          }
          | IF '(' EXPR ')' statement %prec NOELSE {
               evalAST($3);
               if($3->type != 2){
                    yyerror("if condition must be a boolean");
                    return 0;}
               freeAST($3);
          }
          | IF '(' EXPR ')' statement ELSE statement {
               evalAST($3);
               if($3->type != 2){
                    yyerror("if-else condition must be a boolean");
                    return 0;}
               freeAST($3);
          }
          | DO '{' {char newScope[] = "do-while";increaseScope(newScope);} list '}' {decreaseScope();} WHILE '(' EXPR ')' ';' {
               evalAST($9);
               if($9->type != 2){
                    yyerror("while condition must be a boolean");
                    return 0;}
               freeAST($9);
          }
          | PRINT '(' EXPR ')' ';' {
               evalAST($3);
               if($3->type == 5){
                    yyerror("cannot print struct");
                    return 0;
               }
               printf("PRINT: ");
               printExpr($3);
               freeAST($3);
          }
          | EVAL '(' EXPR ')' ';'{
               evalAST($3);
               if($3->type == 5){
                    yyerror("cannot print struct");
                    return 0;
               }
               printf("EVAL: ");
               printExpr($3);
               freeAST($3);
          }
          | TYPEOF '(' EXPR ')' ';' {
               evalAST($3);
               printf("TYPEOF: %s\n",typeToString($3->type));
               freeAST($3);
          }
          | var_decl ';'
          ;

func_call : ID  { currentFuncParams = new Func_Params; }'(' func_list ')' {
               int func_location = searchForFunction($1);
               if(func_location==-1){
                    yyerror("function with this name not declared");
                    return 0;
               }
               if(declaredFunctions[func_location].params.params.size() != currentFuncParams->params.size()){
                    yyerror("function parameters do not match");
                    return 0;
               }
               for(int i = 0; i < declaredFunctions[func_location].params.params.size(); i++){
                    if(declaredFunctions[func_location].params.params[i].type != currentFuncParams->params[i].type){
                         yyerror("function parameters do not match");
                         return 0;
                    }
               }
               $$->type = declaredFunctions[func_location].type;
          }
          ;

func_list : EXPR {
               evalAST($1);
               struct Variable* var = new Variable;
               var->type = $1->type;
               strcpy(var->typeName, $1->typeName);
               currentFuncParams->params.push_back(*var);
               freeAST($1);
          }
          | func_list ',' EXPR {
               evalAST($3);
               struct Variable* var = new Variable;
               var->type = $3->type;
               strcpy(var->typeName, $3->typeName);
               currentFuncParams->params.push_back(*var);
               freeAST($3);
          } 
          | {}// Altfel nu putem apela functii fara parametrii
          ;

var_access : ID {
               int var_location = searchForVariable($1,declaredVariables);
               if(var_location==-1){
                    yyerror("variable with this name not declared");
                    return 0;
               }
               $$ = &declaredVariables[var_location];
          }
           | ID '[' EXPR ']' {
               int var_location = searchForVariable($1,declaredVariables);
               if(var_location==-1){
                    yyerror("variable with this name not declared");
                    return 0;
               }
               if(!declaredVariables[var_location].isArray){
                    yyerror("variable is not an array");
                    return 0;
               }
               $$ = new Variable;
               if($3->type != 0){
                    yyerror("array index must be an integer");
                    return 0;
               }
               evalAST($3);
               if($3->int_val >= declaredVariables[var_location].arraySize || $3->int_val < 0){
                    yyerror("array index out of bounds");
                    return 0;
               }
               $$ = &declaredVariables[var_location].arrayElements[$3->int_val];
               freeAST($3);
           }
           | var_access '.' ID {
               if($1->type != 5){
                    yyerror("variable is not a struct");
                    return 0;
               }
               int member_location = searchForVariable($3,$1->structVars);
               if(member_location==-1){
                    yyerror("member with this name not declared");
                    return 0;
               }
               if($1->structVars[member_location].isArray){
                    yyerror("cannot access array; specify index");
                    return 0;
               }
               $$ = &($1->structVars[member_location]);
           }
           | var_access '.' ID '[' EXPR ']' {
               if($1->type != 5){
                    yyerror("variable is not a struct");
                    return 0;
               }
               int member_location = searchForVariable($3,$1->structVars);
               if(member_location==-1){
                    yyerror("member with this name not declared");
                    return 0;
               }
               evalAST($5);
               if($5->type != 0){
                    yyerror("array index must be an integer");
                    return 0;
               }
               if($5->int_val >= $1->structVars[member_location].arraySize || $5->int_val < 0){
                    yyerror("array index out of bounds");
                    return 0;
               }
               $$ = &($1->structVars[member_location].arrayElements[$5->int_val]);
               freeAST($5);
           }
           ;

// PLACEHOLDER
EXPR : EXPR '+' EXPR {if(!buildAST($$, $1, $3, Add)) return 0;}
     | EXPR '-' EXPR {if(!buildAST($$, $1, $3, Sub)) return 0;}
     | EXPR '*' EXPR {if(!buildAST($$, $1, $3, Mul)) return 0;}
     | EXPR '/' EXPR {if(!buildAST($$, $1, $3, Div)) return 0;}
     | EXPR '%' EXPR {if(!buildAST($$, $1, $3, Mod)) return 0;}
     | EXPR EQ EXPR  {if(!buildAST($$, $1, $3, Equal)) return 0;}
     | EXPR NEQ EXPR {if(!buildAST($$, $1, $3, NotEqual)) return 0;}
     | EXPR LE EXPR  {if(!buildAST($$, $1, $3, Lte)) return 0;}
     | EXPR GE EXPR  {if(!buildAST($$, $1, $3, Gte)) return 0;}
     | EXPR LT EXPR  {if(!buildAST($$, $1, $3, Lt)) return 0;}
     | EXPR GT EXPR  {if(!buildAST($$, $1, $3, Gt)) return 0;}
     | EXPR AND EXPR {if(!buildAST($$, $1, $3, And)) return 0;}
     | EXPR OR EXPR  {if(!buildAST($$, $1, $3, Or)) return 0;}
     | NOT EXPR      {if(!buildAST($$, $2, NULL, Not)) return 0;}
     | '-' EXPR      {if(!buildAST($$, $2, NULL, Sub)) return 0;}
     | func_call     {   
                         newAST($$, $1->type,nullptr,nullptr, None);
                         switch($1->type){
                         case 0:
                              $$->int_val = 0;
                              break;
                         case 1:
                              $$->float_val = 0;
                              break;
                         case 2:
                              $$->bool_val = 0;
                              break;
                         case 3:
                              $$->char_val = 0;
                              break;
                         case 4:
                              strcpy($$->string, "");
                              break;
                         case 5:
                              yyerror("cannot assign struct to variable");
                              break;
                         }
                    }
     | '(' EXPR ')'  {$$ = $2;}
     | INT_NR        {newAST($$,0,nullptr,nullptr,None);$$->int_val = $1;}
     | FLOAT_NR      {newAST($$,1,nullptr,nullptr,None);$$->float_val = $1;}
     | BOOL          {newAST($$,2,nullptr,nullptr,None);$$->bool_val = $1;}
     | CHAR          {newAST($$,3,nullptr,nullptr,None);$$->char_val = $1;}
     | STRING        {newAST($$,4,nullptr,nullptr,None);strcpy($$->string, $1);}
     | var_access    {
                         $$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = $1->type; strcpy($$->typeName, $1->typeName);
                         if($1->isArray){
                              yyerror("cannot assign array to variable");
                              return 0;
                         }
                         switch($1->type){
                         case 0:
                              $$->int_val = $1->int_val;
                              break;
                         case 1:
                              $$->float_val = $1->float_val;
                              break;
                         case 2:
                              $$->bool_val = $1->bool_val;
                              break;
                         case 3:
                              $$->char_val = $1->char_val;
                              break;
                         case 4:
                              strcpy($$->string, $1->string);
                              break;
                         case 5:
                              yyerror("cannot assign struct to variable");
                              return 0;
                              break;
                         }
                         $$->operand = None;
                    }
     ;

TYPE : INT_TYPE
     | FLOAT_TYPE
     | CHAR_TYPE
     | STRING_TYPE
     | BOOL_TYPE
     ;
%%

int main(int argc, char** argv){
     scopeNames.push("global");
     yyin=fopen(argv[1],"r");
     yyparse(); 
}