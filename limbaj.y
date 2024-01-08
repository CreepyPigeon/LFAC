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
int searchForVariable(char* varName,vector<Variable> searchLocation);
const char* typeToString(int type);
int searchForFunction(char* funcName);
bool buildAST(Ast* root, Ast* left, Ast* right, Operation op);

struct Variable* currentVariable;
struct Function* currentFunction;
struct Func_Params* currentFuncParams;

int scope = 0;
vector<Variable> classDefinitions;
vector<Variable> declaredVariables;
vector<Function> declaredFunctions;

void increaseScope(){
     scope++;
}
void decreaseScope(){
     scope--;
     for(int i = 0; i < declaredVariables.size(); i++){
          if(declaredVariables[i].scope == scope){
               declaredVariables.erase(declaredVariables.begin()+i);
               i--;
          }
     }
     //REMOVE ALL VARIABLES FROM SCOPE
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
%left '+' '-'
%left '*' '/' '%'
%nonassoc NOT
%left '(' ')' '[' ']'

%nonassoc NOELSE

%token<int_val> INT_NR
%token<float_val> FLOAT_NR
%token<char_val> CHAR
%token<string> STRING
%token<bool_val> BOOL

%type <type> TYPE;
%type <ast> EXPR;
%type <variable> struct_var;
%type <func_param> func_decl_list;
%type <func_param> FUNC_LIST;
%type <variable> func_param;
%type <variable> var_access;
%type <function> FUNC_CALL;

%start progr

%%
progr: user_structs functions global_vars program {
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
                    //debugPrint(*currentVariable);
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
                         $$ = new Variable; $$->type = $1; strcpy($$->name, $2);
                         strcpy($$->typeName, typeToString($1));
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
                    strcpy($$->typeName, typeToString($3));
                    $$->arraySize = $5->int_val;
                    for(int i = 0; i < $$->arraySize; i++){
                         struct Variable* temp = new Variable;
                         temp->type = $3;
                         strcpy(temp->typeName, typeToString($3));
                         $$->arrayElements.push_back(*temp);
                    }
                    strcpy($$->name, $7);
               }// Arrays 
               ;


// FUNCTION DECLARATIONS
functions: func_decl {declaredFunctions.push_back(*currentFunction);currentFunction = NULL;}
         | functions func_decl {declaredFunctions.push_back(*currentFunction);currentFunction = NULL;}
         ;

func_decl : TYPE ID '(' {currentFuncParams = new Func_Params;} {increaseScope();} func_decl_list ')' '{' list RETURN EXPR ';' '}' {
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
          | TYPE ID '(' ')' '{' {increaseScope();} list RETURN EXPR ';' '}' {
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
                    if(searchForVariable($1->name,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    currentFuncParams->params.push_back(*$1);declaredVariables.push_back(*$1);
               }
               | func_decl_list ',' func_param {
                    if(searchForVariable($3->name,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    currentFuncParams->params.push_back(*$3);declaredVariables.push_back(*$3);
               }
               ;

func_param : TYPE ID {$$ = new Variable; $$->type = $1; strcpy($$->name, $2); strcpy($$->typeName, typeToString($1));}
           | ID ID {$$ = new Variable; if(!searchClasses($1)){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    struct Variable temp = searchForClass($1);
                    $$->structVars = temp.structVars;
                    $$->type = 5;
                    $$->scope = scope;
                    //debugPrint(*$$);
                    strcpy($$->typeName, $1);
                    strcpy($$->name, $2);
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
                    strcpy(var->name, $2);
                    var->type = $1; 
                    strcpy(var->typeName, typeToString($1));
                    var->scope = scope;
                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }// int x
               | TYPE ID ASSIGN EXPR{
                    if(searchForVariable($2,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, $2);
                    var->type = $1; 
                    strcpy(var->typeName, typeToString($1));
                    var->scope = scope;

                    //TO-DO: ASSIGN EXPR

                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }// int x := 5
               | TYPE ID ASSIGN ID{
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
               }// int x := y
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
                    struct Variable temp = searchForClass($1);
                    var->structVars = temp.structVars;
                    var->type = 5;
                    strcpy(var->typeName, $1);
                    strcpy(var->name, $2);
                    var->scope = scope;
                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }// MyStruct x; - primul ID e clasa, a doilea ID e numele variabilei
               | ARRAY '[' TYPE ',' EXPR ']' ID{
                    if(searchForVariable($7,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable;
                    var->isArray = true;
                    var->type = $3;
                    strcpy(var->typeName, typeToString($3));
                    var->arraySize = $5->int_val;
                    strcpy(var->name, $7);
                    var->scope = scope;
                    for(int i = 0; i < var->arraySize; i++){
                         struct Variable* temp = new Variable;
                         temp->type = $3;
                         strcpy(temp->typeName, typeToString($3));
                         var->arrayElements.push_back(*temp);
                    }
                    declaredVariables.push_back(*var);
               }// Arrays; am gandit arrays ca fiind
                // array[int,5] myArray; - asta e un exemplu
               | CONST TYPE ID ASSIGN EXPR{
                    if(searchForVariable($3,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, $3);
                    var->type = $2; 
                    strcpy(var->typeName, typeToString($2));
                    var->scope = scope;
                    var->isConst = true;
                    var->isInit = true;

                    //TO-DO: ASSIGN EXPR

                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }// const int x := 5
               ;

program : BGIN {increaseScope();} list END {decreaseScope();}  
     ;
list : statement ';' 
     | list statement ';'
     |
     ;

statement : var_access ASSIGN EXPR {
               if($1->isConst){
                    yyerror("cannot assign to const variable");
                    return 0;
               }
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
          }
          | FUNC_CALL
          | FOR '(' var_access ASSIGN EXPR ';' EXPR ';' EXPR ')' '{' {increaseScope();} list '}' {decreaseScope();}
          | WHILE '(' EXPR ')' '{' {increaseScope();} list '}' {decreaseScope();}
          | IF '(' EXPR ')' '{' {increaseScope();} list '}' {decreaseScope();} %prec NOELSE
          | IF '(' EXPR ')' '{' {increaseScope();} list '}' {decreaseScope();} ELSE '{'  {increaseScope();} list '}' {decreaseScope();}
          | DO '{' {increaseScope();} list '}' {decreaseScope();} WHILE '(' EXPR ')' ';'
          | PRINT '(' EXPR ')'
          | EVAL '(' EXPR ')'
          | TYPEOF '(' EXPR ')'
          | var_decl
          ;

FUNC_CALL : ID  { currentFuncParams = new Func_Params; }'(' FUNC_LIST ')' {
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

FUNC_LIST : EXPR {
               struct Variable* var = new Variable;
               var->type = $1->type;
               strcpy(var->typeName, $1->typeName);
               currentFuncParams->params.push_back(*var);
          }
          | FUNC_LIST ',' EXPR {
               struct Variable* var = new Variable;
               var->type = $3->type;
               strcpy(var->typeName, $3->typeName);
               currentFuncParams->params.push_back(*var);
          }
          | 
          ;

var_access : ID {
               int var_location = searchForVariable($1,declaredVariables);
               if(var_location==-1){
                    yyerror("variable with this name not declared");
                    return 0;
               }
               $$ = new Variable;
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
               if($3->int_val >= declaredVariables[var_location].arraySize || $3->int_val < 0){
                    yyerror("array index out of bounds");
                    return 0;
               }
               $$ = &declaredVariables[var_location].arrayElements[$3->int_val];

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
               if($5->type != 0){
                    yyerror("array index must be an integer");
                    return 0;
               }
               if($5->int_val >= $1->structVars[member_location].arraySize || $5->int_val < 0){
                    yyerror("array index out of bounds");
                    return 0;
               }
               $$ = &($1->structVars[member_location].arrayElements[$5->int_val]);
           }

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
     | FUNC_CALL     {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = $1->type; strcpy($$->typeName, $1->typeName);
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
                    }}
     | '(' EXPR ')'  {$$ = $2;}
     | INT_NR        {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = 0; strcpy($$->typeName, typeToString($$->type)) ;$$->int_val = $1;}
     | FLOAT_NR      {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = 1; strcpy($$->typeName, typeToString($$->type)) ;$$->float_val = $1;}
     | BOOL          {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = 2; strcpy($$->typeName, typeToString($$->type)) ;$$->bool_val = $1;}
     | CHAR          {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = 3; strcpy($$->typeName, typeToString($$->type)) ;$$->char_val = $1;}
     | STRING        {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = 4; strcpy($$->typeName, typeToString($$->type)) ;strcpy($$->string, $1);}
     | var_access    {$$ = new Ast; $$->left = nullptr; $$->right = nullptr; $$->type = $1->type; strcpy($$->typeName, $1->typeName);
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
                              break;
                    }}
     ;

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

int searchForVariable(char* varName,vector<Variable> searchLocation){
     string varNameStr = varName;
     for(int i = 0; i < searchLocation.size(); i++){
          string toCompareStr = searchLocation[i].name;
          if(varNameStr == toCompareStr && searchLocation[i].scope <= scope)
               return i;
     }
     return -1;
}

bool buildAST(Ast* root, Ast* left, Ast* right, Operation op){
     root = new Ast;
     root->left = left; 
     root->right = right;
     if(left != nullptr && right != nullptr){
          if(left->type != right->type){
               yyerror("types do not match");
               return false;
          }
          if(left->type == 5){
               if(strcmp(left->typeName, right->typeName) != 0){
                    yyerror("types do not match");
                    return false;
               }
          }
     }
     root->operand = op; 
     return true;
}

int searchForFunction(char* funcName){
     string funcNameStr = funcName;
     for(int i = 0; i < declaredFunctions.size(); i++){
          string toCompareStr = declaredFunctions[i].name;
          if(funcNameStr == toCompareStr)
               return i;
     }
     return -1;
}
int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse(); 
}