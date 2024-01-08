#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

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

void debugPrint(Variable var){
     for(auto i: var.structVars){
          cout << i.name << " of type " << i.typeName << endl;
          if(i.type == 5){
               cout<<"Members: \n{\n";
               debugPrint(i);
               cout<<"}\n";
          }
     }
}

void debugPrintVar(Variable var){
     cout << var.name << " of type " << var.typeName << endl;
     cout << "isConst: " << var.isConst << endl;
     cout << "isArray: " << var.isArray << endl;
     cout << "isInit: " << var.isInit << endl;
     cout << "scope: " << var.scope << endl;
     cout << "arraySize: " << var.arraySize << endl;
}
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




