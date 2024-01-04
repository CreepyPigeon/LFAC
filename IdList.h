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

struct Variable{
     int type;
     char name[30];
     char typeName[20];
     bool isConst;
     bool isArray;
     bool isInit;
     union {
          char* string;
          int int_val;
          float float_val;
          bool bool_val;
          char char_val;
     };
     int arraySize;
     vector<Variable> structVars;
     vector<Variable> arrayElements;
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

struct Expr{
     int type;
     union {
          char* string;
          int int_val;
          float float_val;
          bool bool_val;
          char char_val;
     };
};




