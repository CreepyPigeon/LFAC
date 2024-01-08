/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LIMBAJ_TAB_H_INCLUDED
# define YY_YY_LIMBAJ_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    ARRAY = 259,                   /* ARRAY  */
    BGIN = 260,                    /* BGIN  */
    END = 261,                     /* END  */
    WHILE = 262,                   /* WHILE  */
    FOR = 263,                     /* FOR  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    DO = 266,                      /* DO  */
    PRINT = 267,                   /* PRINT  */
    EVAL = 268,                    /* EVAL  */
    TYPEOF = 269,                  /* TYPEOF  */
    RETURN = 270,                  /* RETURN  */
    ID = 271,                      /* ID  */
    INT_TYPE = 272,                /* INT_TYPE  */
    FLOAT_TYPE = 273,              /* FLOAT_TYPE  */
    CHAR_TYPE = 274,               /* CHAR_TYPE  */
    STRING_TYPE = 275,             /* STRING_TYPE  */
    BOOL_TYPE = 276,               /* BOOL_TYPE  */
    USER_STRUCT = 277,             /* USER_STRUCT  */
    ASSIGN = 278,                  /* ASSIGN  */
    EQ = 279,                      /* EQ  */
    NEQ = 280,                     /* NEQ  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    LE = 283,                      /* LE  */
    GE = 284,                      /* GE  */
    LT = 285,                      /* LT  */
    GT = 286,                      /* GT  */
    NOT = 287,                     /* NOT  */
    NOELSE = 288,                  /* NOELSE  */
    INT_NR = 289,                  /* INT_NR  */
    FLOAT_NR = 290,                /* FLOAT_NR  */
    CHAR = 291,                    /* CHAR  */
    STRING = 292,                  /* STRING  */
    BOOL = 293                     /* BOOL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "limbaj.y"

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

#line 115 "limbaj.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LIMBAJ_TAB_H_INCLUDED  */
