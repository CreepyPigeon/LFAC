/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "limbaj.y"

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


#line 119 "limbaj.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "limbaj.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_ARRAY = 4,                      /* ARRAY  */
  YYSYMBOL_BGIN = 5,                       /* BGIN  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_DO = 11,                        /* DO  */
  YYSYMBOL_PRINT = 12,                     /* PRINT  */
  YYSYMBOL_EVAL = 13,                      /* EVAL  */
  YYSYMBOL_TYPEOF = 14,                    /* TYPEOF  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_ID = 16,                        /* ID  */
  YYSYMBOL_INT_TYPE = 17,                  /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 18,                /* FLOAT_TYPE  */
  YYSYMBOL_CHAR_TYPE = 19,                 /* CHAR_TYPE  */
  YYSYMBOL_STRING_TYPE = 20,               /* STRING_TYPE  */
  YYSYMBOL_BOOL_TYPE = 21,                 /* BOOL_TYPE  */
  YYSYMBOL_USER_STRUCT = 22,               /* USER_STRUCT  */
  YYSYMBOL_ASSIGN = 23,                    /* ASSIGN  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_LE = 28,                        /* LE  */
  YYSYMBOL_GE = 29,                        /* GE  */
  YYSYMBOL_LT = 30,                        /* LT  */
  YYSYMBOL_GT = 31,                        /* GT  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_NOT = 37,                       /* NOT  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* '['  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_NOELSE = 42,                    /* NOELSE  */
  YYSYMBOL_INT_NR = 43,                    /* INT_NR  */
  YYSYMBOL_FLOAT_NR = 44,                  /* FLOAT_NR  */
  YYSYMBOL_CHAR = 45,                      /* CHAR  */
  YYSYMBOL_STRING = 46,                    /* STRING  */
  YYSYMBOL_BOOL = 47,                      /* BOOL  */
  YYSYMBOL_48_ = 48,                       /* ';'  */
  YYSYMBOL_49_ = 49,                       /* '{'  */
  YYSYMBOL_50_ = 50,                       /* '}'  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_progr = 54,                     /* progr  */
  YYSYMBOL_user_structs = 55,              /* user_structs  */
  YYSYMBOL_struct_decl = 56,               /* struct_decl  */
  YYSYMBOL_57_1 = 57,                      /* $@1  */
  YYSYMBOL_struct_vars_block = 58,         /* struct_vars_block  */
  YYSYMBOL_struct_vars = 59,               /* struct_vars  */
  YYSYMBOL_struct_var = 60,                /* struct_var  */
  YYSYMBOL_functions = 61,                 /* functions  */
  YYSYMBOL_func_decl = 62,                 /* func_decl  */
  YYSYMBOL_63_2 = 63,                      /* $@2  */
  YYSYMBOL_64_3 = 64,                      /* $@3  */
  YYSYMBOL_65_4 = 65,                      /* $@4  */
  YYSYMBOL_func_decl_list = 66,            /* func_decl_list  */
  YYSYMBOL_func_param = 67,                /* func_param  */
  YYSYMBOL_global_vars = 68,               /* global_vars  */
  YYSYMBOL_var_decl = 69,                  /* var_decl  */
  YYSYMBOL_program = 70,                   /* program  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_list = 72,                      /* list  */
  YYSYMBOL_statement = 73,                 /* statement  */
  YYSYMBOL_74_6 = 74,                      /* $@6  */
  YYSYMBOL_75_7 = 75,                      /* $@7  */
  YYSYMBOL_76_8 = 76,                      /* $@8  */
  YYSYMBOL_77_9 = 77,                      /* $@9  */
  YYSYMBOL_78_10 = 78,                     /* $@10  */
  YYSYMBOL_79_11 = 79,                     /* $@11  */
  YYSYMBOL_80_12 = 80,                     /* $@12  */
  YYSYMBOL_81_13 = 81,                     /* $@13  */
  YYSYMBOL_FUNC_CALL = 82,                 /* FUNC_CALL  */
  YYSYMBOL_83_14 = 83,                     /* $@14  */
  YYSYMBOL_FUNC_LIST = 84,                 /* FUNC_LIST  */
  YYSYMBOL_var_access = 85,                /* var_access  */
  YYSYMBOL_EXPR = 86,                      /* EXPR  */
  YYSYMBOL_TYPE = 87                       /* TYPE  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   797

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      38,    39,    34,    32,    51,    33,    52,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    37,    42,    43,
      44,    45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,   100,   101,   102,   104,   104,   118,   120,
     121,   123,   131,   149,   167,   168,   171,   171,   171,   187,
     187,   204,   211,   220,   221,   237,   238,   240,   253,   269,
     316,   335,   356,   376,   376,   378,   379,   380,   383,   414,
     415,   415,   416,   416,   417,   417,   418,   418,   418,   418,
     419,   419,   419,   420,   421,   422,   423,   426,   426,   446,
     452,   458,   461,   470,   492,   508,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   566,   567,   568,   569,   570,   571,   572,   595,
     596,   597,   598,   599
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "ARRAY",
  "BGIN", "END", "WHILE", "FOR", "IF", "ELSE", "DO", "PRINT", "EVAL",
  "TYPEOF", "RETURN", "ID", "INT_TYPE", "FLOAT_TYPE", "CHAR_TYPE",
  "STRING_TYPE", "BOOL_TYPE", "USER_STRUCT", "ASSIGN", "EQ", "NEQ", "AND",
  "OR", "LE", "GE", "LT", "GT", "'+'", "'-'", "'*'", "'/'", "'%'", "NOT",
  "'('", "')'", "'['", "']'", "NOELSE", "INT_NR", "FLOAT_NR", "CHAR",
  "STRING", "BOOL", "';'", "'{'", "'}'", "','", "'.'", "$accept", "progr",
  "user_structs", "struct_decl", "$@1", "struct_vars_block", "struct_vars",
  "struct_var", "functions", "func_decl", "$@2", "$@3", "$@4",
  "func_decl_list", "func_param", "global_vars", "var_decl", "program",
  "$@5", "list", "statement", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11",
  "$@12", "$@13", "FUNC_CALL", "$@14", "FUNC_LIST", "var_access", "EXPR",
  "TYPE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-120)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -16,    -5,    15,   264,   -11,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,   -10,   550,  -120,    26,  -120,    -4,  -120,    77,
       8,    38,  -120,    61,     7,    51,    35,   105,  -120,    58,
      77,  -120,  -120,    36,  -120,    59,  -120,   -22,    44,    45,
      72,     9,    42,    76,    82,    49,   531,  -120,    83,     6,
      62,  -120,    77,  -120,  -120,    64,  -120,  -120,    70,    70,
      80,    90,    93,    85,    97,    98,   100,    20,  -120,   474,
      95,  -120,   -19,   -28,    70,    70,    70,  -120,  -120,  -120,
    -120,  -120,  -120,    87,   748,  -120,   407,    96,  -120,    30,
     748,   548,    70,   125,    70,  -120,    70,    70,    70,    70,
     110,  -120,   104,  -120,    70,   142,    27,  -120,   620,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,   531,   144,   -32,  -120,   147,    70,   153,   636,
     132,   -18,   652,   531,   668,   684,   700,   566,    70,  -120,
     748,   133,  -120,   761,   761,   347,   347,   146,   146,   146,
     146,    27,    27,  -120,  -120,  -120,   493,  -120,   135,   407,
    -120,   584,  -120,   137,    70,   148,   219,  -120,  -120,  -120,
    -120,   -30,   748,    70,    70,   531,  -120,   180,  -120,   361,
    -120,  -120,  -120,    70,   602,   386,   512,  -120,   531,    70,
     531,   531,   191,   748,  -120,   149,    70,   240,   411,   294,
     313,   175,  -120,   436,  -120,    70,  -120,  -120,    70,   164,
     716,   205,   732,  -120,   167,   168,   171,  -120,  -120,  -120,
     531,   531,   334,   353,  -120,  -120
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     0,     0,     6,     1,    89,    90,    91,
      92,    93,     0,     0,    14,     0,     3,     0,     4,     0,
       0,     0,    15,     0,     0,     0,     0,     0,     7,     0,
       0,    30,    33,     0,     2,     0,    25,    27,    16,     0,
       0,     0,     0,     0,     0,     0,    37,    26,    27,     0,
       0,    17,     0,    12,     8,     0,     9,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    56,     0,
       0,    39,     0,    62,     0,     0,     0,    83,    84,    86,
      87,    85,    81,    88,    28,    19,     0,     0,    10,    62,
      32,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,    34,     0,    35,     0,     0,    80,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,    21,     0,     0,     0,     0,
      62,     0,     0,    37,     0,     0,     0,     0,    61,    36,
      38,    64,    82,    71,    72,    77,    78,    73,    74,    75,
      76,    66,    67,    68,    69,    70,     0,    24,     0,     0,
      23,     0,    31,     0,     0,     0,     0,    53,    54,    55,
      63,     0,    59,     0,     0,    37,    22,     0,    42,     0,
      44,    51,    58,     0,     0,     0,     0,    13,    37,     0,
      37,    37,     0,    60,    65,     0,     0,     0,     0,     0,
       0,     0,    20,     0,    43,     0,    45,    47,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    40,    48,    52,
      37,    37,     0,     0,    41,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,  -120,   217,  -120,  -120,  -120,   183,  -120,   208,
    -120,  -120,  -120,  -120,    66,  -120,    18,  -120,  -120,  -119,
     -67,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,   -29,
    -120,  -120,   -46,    91,     5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    17,    28,    41,    42,    13,    14,
      51,    86,   122,   124,   125,    23,    68,    34,    46,    69,
      70,   220,   188,   190,   191,   211,   221,   133,   192,    82,
     100,   171,    83,    84,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    49,   102,   156,   104,   164,     1,   158,    15,   182,
     -57,     5,    99,    39,   166,     6,    38,    71,    25,   159,
     -29,   183,    73,    72,    29,    40,     7,     8,     9,    10,
      11,    24,    43,   105,   105,    45,    31,    16,    18,    74,
      71,    33,    26,    75,    76,    27,    43,   131,    30,    77,
      78,    79,    80,    81,    31,    36,   186,    87,   -57,    54,
      99,   119,   120,   121,    19,    20,    32,    37,   -57,   197,
      99,   199,   200,    38,    44,    48,    72,    21,     7,     8,
       9,    10,    11,    50,    47,    52,    89,    72,    53,   102,
      56,   126,    57,    71,     7,     8,     9,    10,    11,   102,
      59,   222,   223,    74,    71,    58,    49,    75,    76,    39,
      72,    85,    88,    77,    78,    79,    80,    81,    92,   102,
      72,    40,     7,     8,     9,    10,    11,    71,    93,    72,
     102,    94,   102,   102,    95,    96,    97,    71,    98,   105,
      72,   130,    72,   103,    72,    72,    71,   127,   138,    90,
      91,    72,   139,    72,    72,   102,   102,    71,   141,    71,
     157,    71,    71,   160,   126,   106,   107,   108,    71,   162,
      71,    71,    99,   173,    72,    72,    72,    72,   117,   118,
     119,   120,   121,   129,   175,   132,   178,   134,   135,   136,
     137,    71,    71,    71,    71,   140,   187,   180,   201,   202,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   208,   213,   215,   217,   218,   161,   219,
      12,    22,    19,    20,    55,   176,    60,    61,    62,   172,
      63,    64,    65,    66,     0,    67,     7,     8,     9,    10,
      11,     0,     0,    19,    20,     0,     0,    60,    61,    62,
       0,    63,    64,    65,    66,   179,    67,     7,     8,     9,
      10,    11,     0,     0,   184,   185,     0,     0,     0,   181,
       0,     0,     0,     0,   193,     0,     0,     0,     0,     0,
     198,     7,     8,     9,    10,    11,     1,   203,     0,     0,
     204,     0,     0,     0,     0,     0,   210,    19,    20,   212,
       0,    60,    61,    62,     0,    63,    64,    65,    66,     0,
      67,     7,     8,     9,    10,    11,    19,    20,     0,     0,
      60,    61,    62,     0,    63,    64,    65,    66,     0,    67,
       7,     8,     9,    10,    11,     0,     0,    19,    20,     0,
       0,    60,    61,    62,   206,    63,    64,    65,    66,     0,
      67,     7,     8,     9,    10,    11,    19,    20,     0,     0,
      60,    61,    62,   207,    63,    64,    65,    66,     0,    67,
       7,     8,     9,    10,    11,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   224,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,     0,     0,
       0,     0,     0,   225,     0,     0,     0,     0,     0,   189,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   123,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,   195,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,    19,    20,     0,
     101,    60,    61,    62,   209,    63,    64,    65,    66,     0,
      67,     7,     8,     9,    10,    11,    19,    20,     0,     0,
      60,    61,    62,     0,    63,    64,    65,    66,   174,    67,
       7,     8,     9,    10,    11,    19,    20,     0,     0,    60,
      61,    62,     0,    63,    64,    65,    66,   196,    67,     7,
       8,     9,    10,    11,    19,    20,     0,     0,    60,    61,
      62,     0,    63,    64,    65,    66,     0,    67,     7,     8,
       9,    10,    11,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     7,     8,     9,
      10,    11,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,     0,     0,     0,   128,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,   170,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,   177,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   194,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   142,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,   163,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,   165,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,     0,   167,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,   168,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   169,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,   214,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,   216,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   -58,   -58,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121
};

static const yytype_int16 yycheck[] =
{
      46,    23,    69,   122,    23,    23,    22,    39,     3,    39,
      38,    16,    40,     4,   133,     0,    38,    46,    13,    51,
      48,    51,    16,    69,    19,    16,    17,    18,    19,    20,
      21,    13,    27,    52,    52,    30,    16,    48,    48,    33,
      69,    23,    16,    37,    38,    49,    41,    93,    40,    43,
      44,    45,    46,    47,    16,    48,   175,    52,    38,    50,
      40,    34,    35,    36,     3,     4,     5,    16,    38,   188,
      40,   190,   191,    38,    16,    16,   122,    16,    17,    18,
      19,    20,    21,    39,    48,    40,    16,   133,    16,   156,
      48,    86,    16,   122,    17,    18,    19,    20,    21,   166,
      51,   220,   221,    33,   133,    23,    23,    37,    38,     4,
     156,    49,    48,    43,    44,    45,    46,    47,    38,   186,
     166,    16,    17,    18,    19,    20,    21,   156,    38,   175,
     197,    38,   199,   200,    49,    38,    38,   166,    38,    52,
     186,    16,   188,    48,   190,   191,   175,    51,    38,    58,
      59,   197,    48,   199,   200,   222,   223,   186,    16,   188,
      16,   190,   191,    16,   159,    74,    75,    76,   197,    16,
     199,   200,    40,    40,   220,   221,   222,   223,    32,    33,
      34,    35,    36,    92,    49,    94,    49,    96,    97,    98,
      99,   220,   221,   222,   223,   104,    16,    49,     7,    50,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    38,    50,    10,    49,    49,   127,    48,
       3,    13,     3,     4,    41,   159,     7,     8,     9,   138,
      11,    12,    13,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    -1,     3,     4,    -1,    -1,     7,     8,     9,
      -1,    11,    12,    13,    14,   164,    16,    17,    18,    19,
      20,    21,    -1,    -1,   173,   174,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,
     189,    17,    18,    19,    20,    21,    22,   196,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,   205,     3,     4,   208,
      -1,     7,     8,     9,    -1,    11,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,     3,     4,    -1,    -1,
       7,     8,     9,    -1,    11,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    -1,     3,     4,    -1,
      -1,     7,     8,     9,    50,    11,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,     3,     4,    -1,    -1,
       7,     8,     9,    50,    11,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    50,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    48,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    48,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,     3,     4,    -1,
       6,     7,     8,     9,    48,    11,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,     3,     4,    -1,    -1,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     3,     4,    -1,    -1,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     3,     4,    -1,    -1,     7,     8,
       9,    -1,    11,    12,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,     3,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,    54,    55,    56,    16,     0,    17,    18,    19,
      20,    21,    56,    61,    62,    87,    48,    57,    48,     3,
       4,    16,    62,    68,    69,    87,    16,    49,    58,    87,
      40,    16,     5,    69,    70,    87,    48,    16,    38,     4,
      16,    59,    60,    87,    16,    87,    71,    48,    16,    23,
      39,    63,    40,    16,    50,    60,    48,    16,    23,    51,
       7,     8,     9,    11,    12,    13,    14,    16,    69,    72,
      73,    82,    85,    16,    33,    37,    38,    43,    44,    45,
      46,    47,    82,    85,    86,    49,    64,    87,    48,    16,
      86,    86,    38,    38,    38,    49,    38,    38,    38,    40,
      83,     6,    73,    48,    23,    52,    86,    86,    86,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    65,    16,    66,    67,    87,    51,    41,    86,
      16,    85,    86,    80,    86,    86,    86,    86,    38,    48,
      86,    16,    39,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    72,    16,    39,    51,
      16,    86,    16,    39,    23,    39,    72,    39,    39,    39,
      41,    84,    86,    40,    15,    49,    67,    41,    49,    86,
      49,    50,    39,    51,    86,    86,    72,    16,    75,    48,
      76,    77,    81,    86,    41,    48,    15,    72,    86,    72,
      72,     7,    50,    86,    50,    48,    50,    50,    38,    48,
      86,    78,    86,    50,    39,    10,    39,    49,    49,    48,
      74,    79,    72,    72,    50,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    57,    56,    58,    59,
      59,    60,    60,    60,    61,    61,    63,    64,    62,    65,
      62,    66,    66,    67,    67,    68,    68,    69,    69,    69,
      69,    69,    69,    71,    70,    72,    72,    72,    73,    73,
      74,    73,    75,    73,    76,    73,    77,    78,    79,    73,
      80,    81,    73,    73,    73,    73,    73,    83,    82,    84,
      84,    84,    85,    85,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    87,
      87,    87,    87,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     3,     0,     0,     4,     3,     2,
       3,     2,     2,     7,     1,     2,     0,     0,    13,     0,
      11,     1,     3,     2,     2,     2,     3,     2,     4,     4,
       2,     7,     5,     0,     4,     2,     3,     0,     3,     1,
       0,    14,     0,     8,     0,     8,     0,     0,     0,    14,
       0,     0,    11,     4,     4,     4,     1,     0,     5,     1,
       3,     0,     1,     4,     3,     6,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* progr: user_structs functions global_vars program  */
#line 95 "limbaj.y"
                                                  {
          printf("The programme is correct!\n");
     }
#line 1453 "limbaj.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 104 "limbaj.y"
                             {
                    if(searchClasses((yyvsp[0].string))){
                         yyerror("struct with this name already declared");
                         return 0;
                    }
                    currentVariable = new Variable;
                    currentVariable->type = (yyvsp[-1].type);
                    strcpy(currentVariable->typeName, (yyvsp[0].string));
               }
#line 1467 "limbaj.tab.c"
    break;

  case 7: /* struct_decl: USER_STRUCT ID $@1 struct_vars_block  */
#line 112 "limbaj.y"
                                   {
                    classDefinitions.push_back(*currentVariable);
                    //debugPrint(*currentVariable);
                    currentVariable = NULL;
               }
#line 1477 "limbaj.tab.c"
    break;

  case 9: /* struct_vars: struct_var ';'  */
#line 120 "limbaj.y"
                             {currentVariable->structVars.push_back(*(yyvsp[-1].variable));}
#line 1483 "limbaj.tab.c"
    break;

  case 10: /* struct_vars: struct_vars struct_var ';'  */
#line 121 "limbaj.y"
                                            {currentVariable->structVars.push_back(*(yyvsp[-1].variable));}
#line 1489 "limbaj.tab.c"
    break;

  case 11: /* struct_var: TYPE ID  */
#line 123 "limbaj.y"
                     {
                         if(searchForVariable((yyvsp[0].string),currentVariable->structVars)>-1){
                              yyerror("member with this name already declared");
                              return 0;
                         }
                         (yyval.variable) = new Variable; (yyval.variable)->type = (yyvsp[-1].type); strcpy((yyval.variable)->name, (yyvsp[0].string));
                         strcpy((yyval.variable)->typeName, typeToString((yyvsp[-1].type)));
                    }
#line 1502 "limbaj.tab.c"
    break;

  case 12: /* struct_var: ID ID  */
#line 131 "limbaj.y"
                       {
                    if(searchForVariable((yyvsp[0].string),currentVariable->structVars)>-1){
                         yyerror("member with this name already declared");
                         return 0;
                    }
                    if(!searchClasses((yyvsp[-1].string))){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    (yyval.variable) = new Variable;
                    // Stim sigur ca o sa gasim clasa, deoarece am verificat daca exista
                    struct Variable temp = searchForClass((yyvsp[-1].string));
                    (yyval.variable)->structVars = temp.structVars;
                    (yyval.variable)->type = 5;
                    //debugPrint(*$$);
                    strcpy((yyval.variable)->typeName, (yyvsp[-1].string));
                    strcpy((yyval.variable)->name, (yyvsp[0].string));
               }
#line 1525 "limbaj.tab.c"
    break;

  case 13: /* struct_var: ARRAY '[' TYPE ',' EXPR ']' ID  */
#line 149 "limbaj.y"
                                                {
                    (yyval.variable) = new Variable;
                    (yyval.variable)->isArray = true;
                    (yyval.variable)->type = (yyvsp[-4].type);
                    strcpy((yyval.variable)->typeName, typeToString((yyvsp[-4].type)));
                    (yyval.variable)->arraySize = (yyvsp[-2].ast)->int_val;
                    for(int i = 0; i < (yyval.variable)->arraySize; i++){
                         struct Variable* temp = new Variable;
                         temp->type = (yyvsp[-4].type);
                         strcpy(temp->typeName, typeToString((yyvsp[-4].type)));
                         (yyval.variable)->arrayElements.push_back(*temp);
                    }
                    strcpy((yyval.variable)->name, (yyvsp[0].string));
               }
#line 1544 "limbaj.tab.c"
    break;

  case 14: /* functions: func_decl  */
#line 167 "limbaj.y"
                     {declaredFunctions.push_back(*currentFunction);currentFunction = NULL;}
#line 1550 "limbaj.tab.c"
    break;

  case 15: /* functions: functions func_decl  */
#line 168 "limbaj.y"
                               {declaredFunctions.push_back(*currentFunction);currentFunction = NULL;}
#line 1556 "limbaj.tab.c"
    break;

  case 16: /* $@2: %empty  */
#line 171 "limbaj.y"
                        {currentFuncParams = new Func_Params;}
#line 1562 "limbaj.tab.c"
    break;

  case 17: /* $@3: %empty  */
#line 171 "limbaj.y"
                                                               {increaseScope();}
#line 1568 "limbaj.tab.c"
    break;

  case 18: /* func_decl: TYPE ID '(' $@2 $@3 func_decl_list ')' '{' list RETURN EXPR ';' '}'  */
#line 171 "limbaj.y"
                                                                                                                                  {
               decreaseScope();
               if(searchForFunction((yyvsp[-11].string))>-1){
                    yyerror("function with this name already declared");
                    return 0;
               }
               currentFunction = new Function;
               currentFunction->type = (yyvsp[-12].type);
               strcpy(currentFunction->typeName, typeToString((yyvsp[-12].type)));
               strcpy(currentFunction->name, (yyvsp[-11].string));
               currentFunction->params = *currentFuncParams;
               if((yyvsp[-2].ast)->type != currentFunction->type){
                    yyerror("function return type does not match");
                    return 0;
               }
          }
#line 1589 "limbaj.tab.c"
    break;

  case 19: /* $@4: %empty  */
#line 187 "limbaj.y"
                                {increaseScope();}
#line 1595 "limbaj.tab.c"
    break;

  case 20: /* func_decl: TYPE ID '(' ')' '{' $@4 list RETURN EXPR ';' '}'  */
#line 187 "limbaj.y"
                                                                            {
               decreaseScope();
               if(searchForFunction((yyvsp[-9].string))>-1){
                    yyerror("function with this name already declared");
                    return 0;
               }
               currentFunction = new Function;
               currentFunction->type = (yyvsp[-10].type);
               strcpy(currentFunction->typeName, typeToString((yyvsp[-10].type)));
               strcpy(currentFunction->name, (yyvsp[-9].string));
               if((yyvsp[-2].ast)->type != currentFunction->type){
                    yyerror("function return type does not match");
                    return 0;
               }
          }
#line 1615 "limbaj.tab.c"
    break;

  case 21: /* func_decl_list: func_param  */
#line 204 "limbaj.y"
                            {
                    if(searchForVariable((yyvsp[0].variable)->name,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    currentFuncParams->params.push_back(*(yyvsp[0].variable));declaredVariables.push_back(*(yyvsp[0].variable));
               }
#line 1627 "limbaj.tab.c"
    break;

  case 22: /* func_decl_list: func_decl_list ',' func_param  */
#line 211 "limbaj.y"
                                               {
                    if(searchForVariable((yyvsp[0].variable)->name,declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    currentFuncParams->params.push_back(*(yyvsp[0].variable));declaredVariables.push_back(*(yyvsp[0].variable));
               }
#line 1639 "limbaj.tab.c"
    break;

  case 23: /* func_param: TYPE ID  */
#line 220 "limbaj.y"
                     {(yyval.variable) = new Variable; (yyval.variable)->type = (yyvsp[-1].type); strcpy((yyval.variable)->name, (yyvsp[0].string)); strcpy((yyval.variable)->typeName, typeToString((yyvsp[-1].type)));}
#line 1645 "limbaj.tab.c"
    break;

  case 24: /* func_param: ID ID  */
#line 221 "limbaj.y"
                   {(yyval.variable) = new Variable; if(!searchClasses((yyvsp[-1].string))){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    struct Variable temp = searchForClass((yyvsp[-1].string));
                    (yyval.variable)->structVars = temp.structVars;
                    (yyval.variable)->type = 5;
                    (yyval.variable)->scope = scope;
                    //debugPrint(*$$);
                    strcpy((yyval.variable)->typeName, (yyvsp[-1].string));
                    strcpy((yyval.variable)->name, (yyvsp[0].string));
               }
#line 1662 "limbaj.tab.c"
    break;

  case 27: /* var_decl: TYPE ID  */
#line 240 "limbaj.y"
                  {
                    if(searchForVariable((yyvsp[0].string),declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, (yyvsp[0].string));
                    var->type = (yyvsp[-1].type); 
                    strcpy(var->typeName, typeToString((yyvsp[-1].type)));
                    var->scope = scope;
                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }
#line 1680 "limbaj.tab.c"
    break;

  case 28: /* var_decl: TYPE ID ASSIGN EXPR  */
#line 253 "limbaj.y"
                                    {
                    if(searchForVariable((yyvsp[-2].string),declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, (yyvsp[-2].string));
                    var->type = (yyvsp[-3].type); 
                    strcpy(var->typeName, typeToString((yyvsp[-3].type)));
                    var->scope = scope;

                    //TO-DO: ASSIGN EXPR

                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }
#line 1701 "limbaj.tab.c"
    break;

  case 29: /* var_decl: TYPE ID ASSIGN ID  */
#line 269 "limbaj.y"
                                  {
                    if(searchForVariable((yyvsp[-2].string),declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    int other_var = searchForVariable((yyvsp[0].string),declaredVariables);
                    if(other_var==-1){
                         yyerror("variable with this name not declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, (yyvsp[-2].string));
                    var->type = (yyvsp[-3].type); 
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
                    strcpy(var->typeName, typeToString((yyvsp[-3].type)));
                    var->scope = scope;
                    switch((yyvsp[-3].type)){
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
               }
#line 1753 "limbaj.tab.c"
    break;

  case 30: /* var_decl: ID ID  */
#line 316 "limbaj.y"
                      {
                    if(searchForVariable((yyvsp[0].string),declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    if(!searchClasses((yyvsp[-1].string))){
                         yyerror("type with this name does not exist");
                         return 0;
                    }
                    struct Variable* var = new Variable;
                    struct Variable temp = searchForClass((yyvsp[-1].string));
                    var->structVars = temp.structVars;
                    var->type = 5;
                    strcpy(var->typeName, (yyvsp[-1].string));
                    strcpy(var->name, (yyvsp[0].string));
                    var->scope = scope;
                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }
#line 1777 "limbaj.tab.c"
    break;

  case 31: /* var_decl: ARRAY '[' TYPE ',' EXPR ']' ID  */
#line 335 "limbaj.y"
                                               {
                    if(searchForVariable((yyvsp[0].string),declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable;
                    var->isArray = true;
                    var->type = (yyvsp[-4].type);
                    strcpy(var->typeName, typeToString((yyvsp[-4].type)));
                    var->arraySize = (yyvsp[-2].ast)->int_val;
                    strcpy(var->name, (yyvsp[0].string));
                    var->scope = scope;
                    for(int i = 0; i < var->arraySize; i++){
                         struct Variable* temp = new Variable;
                         temp->type = (yyvsp[-4].type);
                         strcpy(temp->typeName, typeToString((yyvsp[-4].type)));
                         var->arrayElements.push_back(*temp);
                    }
                    declaredVariables.push_back(*var);
               }
#line 1802 "limbaj.tab.c"
    break;

  case 32: /* var_decl: CONST TYPE ID ASSIGN EXPR  */
#line 356 "limbaj.y"
                                          {
                    if(searchForVariable((yyvsp[-2].string),declaredVariables)>-1){
                         yyerror("variable with this name already declared");
                         return 0;
                    }
                    struct Variable* var = new Variable; 
                    strcpy(var->name, (yyvsp[-2].string));
                    var->type = (yyvsp[-3].type); 
                    strcpy(var->typeName, typeToString((yyvsp[-3].type)));
                    var->scope = scope;
                    var->isConst = true;
                    var->isInit = true;

                    //TO-DO: ASSIGN EXPR

                    //debugPrintVar(*var);
                    declaredVariables.push_back(*var);
               }
#line 1825 "limbaj.tab.c"
    break;

  case 33: /* $@5: %empty  */
#line 376 "limbaj.y"
               {increaseScope();}
#line 1831 "limbaj.tab.c"
    break;

  case 34: /* program: BGIN $@5 list END  */
#line 376 "limbaj.y"
                                           {decreaseScope();}
#line 1837 "limbaj.tab.c"
    break;

  case 38: /* statement: var_access ASSIGN EXPR  */
#line 383 "limbaj.y"
                                   {
               if((yyvsp[-2].variable)->isConst){
                    yyerror("cannot assign to const variable");
                    return 0;
               }
               if((yyvsp[-2].variable)->type != (yyvsp[0].ast)->type){
                    yyerror("variable types do not match");
                    return 0;
               }
               if((yyvsp[-2].variable)->isArray){
                    yyerror("cannot assign array to variable");
                    return 0;
               }
               switch((yyvsp[-2].variable)->type){
                    case 0:
                         (yyvsp[-2].variable)->int_val = (yyvsp[0].ast)->int_val;
                         break;
                    case 1:
                         (yyvsp[-2].variable)->float_val = (yyvsp[0].ast)->float_val;
                         break;
                    case 2:
                         (yyvsp[-2].variable)->bool_val = (yyvsp[0].ast)->bool_val;
                         break;
                    case 3:
                         (yyvsp[-2].variable)->char_val = (yyvsp[0].ast)->char_val;
                         break;
                    case 4:
                         strcpy((yyvsp[-2].variable)->string, (yyvsp[0].ast)->string);
                         break;
               }
          }
#line 1873 "limbaj.tab.c"
    break;

  case 40: /* $@6: %empty  */
#line 415 "limbaj.y"
                                                                     {increaseScope();}
#line 1879 "limbaj.tab.c"
    break;

  case 41: /* statement: FOR '(' var_access ASSIGN EXPR ';' EXPR ';' EXPR ')' '{' $@6 list '}'  */
#line 415 "limbaj.y"
                                                                                                 {decreaseScope();}
#line 1885 "limbaj.tab.c"
    break;

  case 42: /* $@7: %empty  */
#line 416 "limbaj.y"
                                   {increaseScope();}
#line 1891 "limbaj.tab.c"
    break;

  case 43: /* statement: WHILE '(' EXPR ')' '{' $@7 list '}'  */
#line 416 "limbaj.y"
                                                               {decreaseScope();}
#line 1897 "limbaj.tab.c"
    break;

  case 44: /* $@8: %empty  */
#line 417 "limbaj.y"
                                {increaseScope();}
#line 1903 "limbaj.tab.c"
    break;

  case 45: /* statement: IF '(' EXPR ')' '{' $@8 list '}'  */
#line 417 "limbaj.y"
                                                            {decreaseScope();}
#line 1909 "limbaj.tab.c"
    break;

  case 46: /* $@9: %empty  */
#line 418 "limbaj.y"
                                {increaseScope();}
#line 1915 "limbaj.tab.c"
    break;

  case 47: /* $@10: %empty  */
#line 418 "limbaj.y"
                                                            {decreaseScope();}
#line 1921 "limbaj.tab.c"
    break;

  case 48: /* $@11: %empty  */
#line 418 "limbaj.y"
                                                                                         {increaseScope();}
#line 1927 "limbaj.tab.c"
    break;

  case 49: /* statement: IF '(' EXPR ')' '{' $@9 list '}' $@10 ELSE '{' $@11 list '}'  */
#line 418 "limbaj.y"
                                                                                                                     {decreaseScope();}
#line 1933 "limbaj.tab.c"
    break;

  case 50: /* $@12: %empty  */
#line 419 "limbaj.y"
                   {increaseScope();}
#line 1939 "limbaj.tab.c"
    break;

  case 51: /* $@13: %empty  */
#line 419 "limbaj.y"
                                               {decreaseScope();}
#line 1945 "limbaj.tab.c"
    break;

  case 57: /* $@14: %empty  */
#line 426 "limbaj.y"
                { currentFuncParams = new Func_Params; }
#line 1951 "limbaj.tab.c"
    break;

  case 58: /* FUNC_CALL: ID $@14 '(' FUNC_LIST ')'  */
#line 426 "limbaj.y"
                                                                          {
               int func_location = searchForFunction((yyvsp[-4].string));
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
               (yyval.function)->type = declaredFunctions[func_location].type;
          }
#line 1974 "limbaj.tab.c"
    break;

  case 59: /* FUNC_LIST: EXPR  */
#line 446 "limbaj.y"
                 {
               struct Variable* var = new Variable;
               var->type = (yyvsp[0].ast)->type;
               strcpy(var->typeName, (yyvsp[0].ast)->typeName);
               currentFuncParams->params.push_back(*var);
          }
#line 1985 "limbaj.tab.c"
    break;

  case 60: /* FUNC_LIST: FUNC_LIST ',' EXPR  */
#line 452 "limbaj.y"
                               {
               struct Variable* var = new Variable;
               var->type = (yyvsp[0].ast)->type;
               strcpy(var->typeName, (yyvsp[0].ast)->typeName);
               currentFuncParams->params.push_back(*var);
          }
#line 1996 "limbaj.tab.c"
    break;

  case 62: /* var_access: ID  */
#line 461 "limbaj.y"
                {
               int var_location = searchForVariable((yyvsp[0].string),declaredVariables);
               if(var_location==-1){
                    yyerror("variable with this name not declared");
                    return 0;
               }
               (yyval.variable) = new Variable;
               (yyval.variable) = &declaredVariables[var_location];
          }
#line 2010 "limbaj.tab.c"
    break;

  case 63: /* var_access: ID '[' EXPR ']'  */
#line 470 "limbaj.y"
                             {
               int var_location = searchForVariable((yyvsp[-3].string),declaredVariables);
               if(var_location==-1){
                    yyerror("variable with this name not declared");
                    return 0;
               }
               if(!declaredVariables[var_location].isArray){
                    yyerror("variable is not an array");
                    return 0;
               }
               (yyval.variable) = new Variable;
               if((yyvsp[-1].ast)->type != 0){
                    yyerror("array index must be an integer");
                    return 0;
               }
               if((yyvsp[-1].ast)->int_val >= declaredVariables[var_location].arraySize || (yyvsp[-1].ast)->int_val < 0){
                    yyerror("array index out of bounds");
                    return 0;
               }
               (yyval.variable) = &declaredVariables[var_location].arrayElements[(yyvsp[-1].ast)->int_val];

           }
#line 2037 "limbaj.tab.c"
    break;

  case 64: /* var_access: var_access '.' ID  */
#line 492 "limbaj.y"
                               {
               if((yyvsp[-2].variable)->type != 5){
                    yyerror("variable is not a struct");
                    return 0;
               }
               int member_location = searchForVariable((yyvsp[0].string),(yyvsp[-2].variable)->structVars);
               if(member_location==-1){
                    yyerror("member with this name not declared");
                    return 0;
               }
               if((yyvsp[-2].variable)->structVars[member_location].isArray){
                    yyerror("cannot access array; specify index");
                    return 0;
               }
               (yyval.variable) = &((yyvsp[-2].variable)->structVars[member_location]);
           }
#line 2058 "limbaj.tab.c"
    break;

  case 65: /* var_access: var_access '.' ID '[' EXPR ']'  */
#line 508 "limbaj.y"
                                            {
               if((yyvsp[-5].variable)->type != 5){
                    yyerror("variable is not a struct");
                    return 0;
               }
               int member_location = searchForVariable((yyvsp[-3].string),(yyvsp[-5].variable)->structVars);
               if(member_location==-1){
                    yyerror("member with this name not declared");
                    return 0;
               }
               if((yyvsp[-1].ast)->type != 0){
                    yyerror("array index must be an integer");
                    return 0;
               }
               if((yyvsp[-1].ast)->int_val >= (yyvsp[-5].variable)->structVars[member_location].arraySize || (yyvsp[-1].ast)->int_val < 0){
                    yyerror("array index out of bounds");
                    return 0;
               }
               (yyval.variable) = &((yyvsp[-5].variable)->structVars[member_location].arrayElements[(yyvsp[-1].ast)->int_val]);
           }
#line 2083 "limbaj.tab.c"
    break;

  case 66: /* EXPR: EXPR '+' EXPR  */
#line 530 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Add)) return 0;}
#line 2089 "limbaj.tab.c"
    break;

  case 67: /* EXPR: EXPR '-' EXPR  */
#line 531 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Sub)) return 0;}
#line 2095 "limbaj.tab.c"
    break;

  case 68: /* EXPR: EXPR '*' EXPR  */
#line 532 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Mul)) return 0;}
#line 2101 "limbaj.tab.c"
    break;

  case 69: /* EXPR: EXPR '/' EXPR  */
#line 533 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Div)) return 0;}
#line 2107 "limbaj.tab.c"
    break;

  case 70: /* EXPR: EXPR '%' EXPR  */
#line 534 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Mod)) return 0;}
#line 2113 "limbaj.tab.c"
    break;

  case 71: /* EXPR: EXPR EQ EXPR  */
#line 535 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Equal)) return 0;}
#line 2119 "limbaj.tab.c"
    break;

  case 72: /* EXPR: EXPR NEQ EXPR  */
#line 536 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), NotEqual)) return 0;}
#line 2125 "limbaj.tab.c"
    break;

  case 73: /* EXPR: EXPR LE EXPR  */
#line 537 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Lte)) return 0;}
#line 2131 "limbaj.tab.c"
    break;

  case 74: /* EXPR: EXPR GE EXPR  */
#line 538 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Gte)) return 0;}
#line 2137 "limbaj.tab.c"
    break;

  case 75: /* EXPR: EXPR LT EXPR  */
#line 539 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Lt)) return 0;}
#line 2143 "limbaj.tab.c"
    break;

  case 76: /* EXPR: EXPR GT EXPR  */
#line 540 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Gt)) return 0;}
#line 2149 "limbaj.tab.c"
    break;

  case 77: /* EXPR: EXPR AND EXPR  */
#line 541 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), And)) return 0;}
#line 2155 "limbaj.tab.c"
    break;

  case 78: /* EXPR: EXPR OR EXPR  */
#line 542 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast), Or)) return 0;}
#line 2161 "limbaj.tab.c"
    break;

  case 79: /* EXPR: NOT EXPR  */
#line 543 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[0].ast), NULL, Not)) return 0;}
#line 2167 "limbaj.tab.c"
    break;

  case 80: /* EXPR: '-' EXPR  */
#line 544 "limbaj.y"
                     {if(!buildAST((yyval.ast), (yyvsp[0].ast), NULL, Sub)) return 0;}
#line 2173 "limbaj.tab.c"
    break;

  case 81: /* EXPR: FUNC_CALL  */
#line 545 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = (yyvsp[0].function)->type; strcpy((yyval.ast)->typeName, (yyvsp[0].function)->typeName);
                         switch((yyvsp[0].function)->type){
                         case 0:
                              (yyval.ast)->int_val = 0;
                              break;
                         case 1:
                              (yyval.ast)->float_val = 0;
                              break;
                         case 2:
                              (yyval.ast)->bool_val = 0;
                              break;
                         case 3:
                              (yyval.ast)->char_val = 0;
                              break;
                         case 4:
                              strcpy((yyval.ast)->string, "");
                              break;
                         case 5:
                              yyerror("cannot assign struct to variable");
                              break;
                    }}
#line 2199 "limbaj.tab.c"
    break;

  case 82: /* EXPR: '(' EXPR ')'  */
#line 566 "limbaj.y"
                     {(yyval.ast) = (yyvsp[-1].ast);}
#line 2205 "limbaj.tab.c"
    break;

  case 83: /* EXPR: INT_NR  */
#line 567 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = 0; strcpy((yyval.ast)->typeName, typeToString((yyval.ast)->type)) ;(yyval.ast)->int_val = (yyvsp[0].int_val);}
#line 2211 "limbaj.tab.c"
    break;

  case 84: /* EXPR: FLOAT_NR  */
#line 568 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = 1; strcpy((yyval.ast)->typeName, typeToString((yyval.ast)->type)) ;(yyval.ast)->float_val = (yyvsp[0].float_val);}
#line 2217 "limbaj.tab.c"
    break;

  case 85: /* EXPR: BOOL  */
#line 569 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = 2; strcpy((yyval.ast)->typeName, typeToString((yyval.ast)->type)) ;(yyval.ast)->bool_val = (yyvsp[0].bool_val);}
#line 2223 "limbaj.tab.c"
    break;

  case 86: /* EXPR: CHAR  */
#line 570 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = 3; strcpy((yyval.ast)->typeName, typeToString((yyval.ast)->type)) ;(yyval.ast)->char_val = (yyvsp[0].char_val);}
#line 2229 "limbaj.tab.c"
    break;

  case 87: /* EXPR: STRING  */
#line 571 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = 4; strcpy((yyval.ast)->typeName, typeToString((yyval.ast)->type)) ;strcpy((yyval.ast)->string, (yyvsp[0].string));}
#line 2235 "limbaj.tab.c"
    break;

  case 88: /* EXPR: var_access  */
#line 572 "limbaj.y"
                     {(yyval.ast) = new Ast; (yyval.ast)->left = nullptr; (yyval.ast)->right = nullptr; (yyval.ast)->type = (yyvsp[0].variable)->type; strcpy((yyval.ast)->typeName, (yyvsp[0].variable)->typeName);
                         switch((yyvsp[0].variable)->type){
                         case 0:
                              (yyval.ast)->int_val = (yyvsp[0].variable)->int_val;
                              break;
                         case 1:
                              (yyval.ast)->float_val = (yyvsp[0].variable)->float_val;
                              break;
                         case 2:
                              (yyval.ast)->bool_val = (yyvsp[0].variable)->bool_val;
                              break;
                         case 3:
                              (yyval.ast)->char_val = (yyvsp[0].variable)->char_val;
                              break;
                         case 4:
                              strcpy((yyval.ast)->string, (yyvsp[0].variable)->string);
                              break;
                         case 5:
                              yyerror("cannot assign struct to variable");
                              break;
                    }}
#line 2261 "limbaj.tab.c"
    break;


#line 2265 "limbaj.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 601 "limbaj.y"

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
