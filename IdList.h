#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct IdInfo {
    string type;
    string name;
};


enum Type{
     INT = 0,
     FLOAT = 1,
     BOOL = 2,
     CHAR = 3,
     STRING = 4,
     USER_STRUCT = 5
};

struct Variable{
     Type type;
     char name[255];
     bool isConst;
     bool isArray;
     bool isInit;
     union {
          char* string;
          int int_val;
          float float_val;
          bool bool_val;
          char char_val;
     }value;
     int arraySize;
     vector<Variable> structVars;
};

class IdList {
    vector<IdInfo> vars;
   
    public:
    bool existsVar(const char* s);
    void addVar(const char* type, const char* name );
    void printVars();
    ~IdList();
};





