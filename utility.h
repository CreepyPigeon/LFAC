#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <stack>

using namespace std;

ofstream out("output.txt");

extern struct Variable* currentVariable;
extern struct Function* currentFunction;
extern struct Func_Params* currentFuncParams;


extern vector<Variable> classDefinitions;
extern vector<Variable> declaredVariables;
extern vector<Function> declaredFunctions;

extern FILE* yyin;
extern char* yytext;
extern int yylineno;

extern int yylex();

int scope = 0;
stack<string> scopeNames;

// enum Type_Var{
//      INT = 0,
//      FLOAT = 1,
//      BOOL = 2,
//      CHAR = 3,
//      STRING = 4,
//      USER_STRUCT = 5
// };

enum Operation{
     Add,
     Sub,
     Mul,
     Div,
     Mod,
     Assign,
     Equal,
     NotEqual,
     Lt,
     Gt,
     Lte,
     Gte,
     And,
     Or,
     Not,
     None
};

struct Variable{
     int type;
     char name[30];
     char typeName[20];
     bool isConst;
     bool isArray;
     bool isInit;
     int scope;
     union {
          char string[200];
          int int_val;
          float float_val;
          bool bool_val;
          char char_val;
     };
     int arraySize;
     vector<std::string> scopeNames;
     vector<Variable> structVars;
     vector<Variable> arrayElements;
};

struct Func_Params{
     vector<Variable> params;
};

struct Function{
     char name[30];
     int type;
     char typeName[20];
     Func_Params params;
};

struct Ast{
     int type;
     char typeName[20];
     int isConst;
     Operation operand;
     union {
          char string[200];
          int int_val;
          float float_val;
          bool bool_val;
          char char_val;
     };
     Ast* left;
     Ast* right;
};

void increaseScope(char* scopeName){
     scope++;
     scopeNames.push(scopeName);
}
void decreaseScope(){
     for(int i = 0; i < declaredVariables.size(); i++){
          if(declaredVariables[i].scope == scope){
               declaredVariables.erase(declaredVariables.begin()+i);
               i--;
          }
     }
     scope--;
     scopeNames.pop();
     //REMOVE ALL VARIABLES FROM SCOPE
}

void debugPrintVar(Variable var){
     if(var.type != 5)
          out << var.typeName << ": " << var.name << " ";
     else
          out<<var.typeName;
     if(var.type == 5){
          out<<" with members: { ";
          for(auto i: var.structVars){
               debugPrintVar(i);
          }
          out<<"} ";
     }
}

void debugPrintVarDetailed(Variable var){
     out<<"Variable \""<<var.name<<"\" of type ";
     if(var.isArray){
          out<<"array["<<var.typeName<<";"<<var.arraySize<<"] ";
     }
     else{
          out<<"["<<var.typeName<<"] ";
     }
     if(var.isInit){
          out<<"initialized with: ";
          switch (var.type){
               case 0:
                    out<<var.int_val;
                    break;
               case 1:
                    out<<var.float_val;
                    break;
               case 2:
                    out<<var.bool_val;
                    break;
               case 3:
                    out<<var.char_val;
                    break;
               case 4:
                    out<<var.string;
                    break;
               default:
                    break;
          }
     }
     else{
          out<<"not initialized";
     }
     if(var.isConst){
          out<<" and is a constant";
     }
     out<<" - scope ";
     for(auto i: var.scopeNames){
          out<<i<<">";
     }
     out<<endl;
}

void debugPrintFunc(Function func){
     out<<endl;
     out<<"Function "<<func.name<<" (returns "<<func.typeName<<") with params: (";
     for(auto i: func.params.params){
          debugPrintVar(i);
     }
     out<<")\n";
}

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

bool buildAST(Ast* &root, Ast* left, Ast* right, Operation op){
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

void evalAST(Ast* &root){
     if(root->left != nullptr)
          evalAST(root->left);
     if(root->right != nullptr)
          evalAST(root->right);
     switch(root->operand){
          case None:
               break;
          case Add:
               switch(root->left->type){
                    case 0:
                         root->int_val = root->left->int_val + root->right->int_val;
                         break;
                    case 1:
                         root->float_val = root->left->float_val + root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = root->left->type;
               strcpy(root->typeName, root->left->typeName);
               break;
          case Sub:
               if(root->right != nullptr)
                    switch(root->left->type){
                         case 0:
                              root->int_val = root->left->int_val - root->right->int_val;
                              break;
                         case 1:
                              root->float_val = root->left->float_val - root->right->float_val;
                              break;
                         default:
                              yyerror("invalid operation for these types");
                              exit(1);
                              break;
                    }
               else
                    switch(root->left->type){
                         case 0:
                              root->int_val = -root->left->int_val;
                              break;
                         case 1:
                              root->float_val = -root->left->float_val;
                              break;
                         default:
                              yyerror("invalid operation for these types");
                              exit(1);
                              break;
                    }
               root->type = root->left->type;
               strcpy(root->typeName, root->left->typeName);
               break;
          case Mul:
               switch(root->left->type){
                    case 0:
                         root->int_val = root->left->int_val * root->right->int_val;
                         break;
                    case 1:
                         root->float_val = root->left->float_val * root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = root->left->type;
               strcpy(root->typeName, root->left->typeName);
               break;
          case Div:
               switch(root->left->type){
                    case 0:
                         root->int_val = root->left->int_val / root->right->int_val;
                         break;
                    case 1:
                         root->float_val = root->left->float_val / root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = root->left->type;
               strcpy(root->typeName, root->left->typeName);
               break;
          case Mod:
               switch(root->left->type){
                    case 0:
                         root->int_val = root->left->int_val % root->right->int_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = root->left->type;
               strcpy(root->typeName, root->left->typeName);
               break;
          case Equal:
               switch(root->left->type){
                    case 0:
                         root->bool_val = root->left->int_val == root->right->int_val;
                         break;
                    case 1:
                         root->bool_val = root->left->float_val == root->right->float_val;
                         break;
                    case 2:
                         root->bool_val = root->left->bool_val == root->right->bool_val;
                         break;
                    case 3:
                         root->bool_val = root->left->char_val == root->right->char_val;
                         break;
                    case 4:
                         root->bool_val = strcmp(root->left->string, root->right->string) == 0;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case NotEqual:
               switch(root->left->type){
                    case 0:
                         root->bool_val = root->left->int_val != root->right->int_val;
                         break;
                    case 1:
                         root->bool_val = root->left->float_val != root->right->float_val;
                         break;
                    case 2:
                         root->bool_val = root->left->bool_val != root->right->bool_val;
                         break;
                    case 3:
                         root->bool_val = root->left->char_val != root->right->char_val;
                         break;
                    case 4:
                         root->bool_val = strcmp(root->left->string, root->right->string) != 0;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case Lte:
               switch(root->left->type){
                    case 0:
                         root->bool_val = root->left->int_val <= root->right->int_val;
                         break;
                    case 1:
                         root->bool_val = root->left->float_val <= root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case Gte:
               switch(root->left->type){
                    case 0:
                         root->bool_val = root->left->int_val >= root->right->int_val;
                         break;
                    case 1:
                         root->bool_val = root->left->float_val >= root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case Lt:
               switch(root->left->type){
                    case 0:
                         root->bool_val = root->left->int_val < root->right->int_val;
                         break;
                    case 1:
                         root->bool_val = root->left->float_val < root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case Gt:
               switch(root->left->type){
                    case 0:
                         root->bool_val = root->left->int_val > root->right->int_val;
                         break;
                    case 1:
                         root->bool_val = root->left->float_val > root->right->float_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case And:
               switch(root->left->type){
                    case 2:
                         root->bool_val = root->left->bool_val && root->right->bool_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case Or:
               switch(root->left->type){
                    case 2:
                         root->bool_val = root->left->bool_val || root->right->bool_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          case Not:
               switch(root->left->type){
                    case 2:
                         root->bool_val = !root->left->bool_val;
                         break;
                    default:
                         yyerror("invalid operation for these types");
                         exit(1);
                         break;
               }
               root->type = 2;
               strcpy(root->typeName, typeToString(root->type));
               break;
          default:
               yyerror("unknown operand");
               exit(1);
               break;
     }
}

void newVar(Variable* &var, int type, char* name, bool isConst, bool isArray, bool isInit, bool scope){
     var = new Variable;
     var->type = type;
     strcpy(var->name, name);
     strcpy(var->typeName, typeToString(type));
     var->isConst = isConst;
     var->isArray = isArray;
     var->isInit = isInit;
     var->scope = scope;
     var->scopeNames = vector<string>(scopeNames.size());
     stack<string> tempStack = scopeNames;
     for(int i = scopeNames.size()-1; i >= 0; i--){
          var->scopeNames[i] = tempStack.top();
          tempStack.pop();
     }
}

void newAST(Ast* &ast, int type, Ast* left, Ast* right, Operation operand){
     ast = new Ast;
     ast->type = type;
     strcpy(ast->typeName, typeToString(type));
     ast->left = left;
     ast->right = right;
     ast->operand = operand;
}
void printExpr(Ast* expr){
     switch(expr->type){
          case 0:
               printf("%d\n",expr->int_val);
               break;
          case 1:
               printf("%f\n",expr->float_val);
               break;
          case 2:
               if(expr->bool_val)
                    printf("true\n");
               else
                    printf("false\n");
               break;
          case 3:
               printf("%c\n",expr->char_val);
               break;
          case 4:
               printf("%s\n",expr->string);
               break;
          default:
               printf("unknown\n");
               break;
     }
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