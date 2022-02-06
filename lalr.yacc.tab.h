/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_LALR_YACC_TAB_H_INCLUDED
# define YY_YY_LALR_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_MODULE = 258,
    IDENTIFIER = 259,
    KW_EXTERN = 260,
    KW_VOID = 261,
    KW_START = 262,
    ARROW = 263,
    KW_LABEL = 264,
    KW_BREAK = 265,
    KW_CONTINUE = 266,
    KW_IF = 267,
    KW_GOTO = 268,
    KW_WHILE = 269,
    KW_SWITCH = 270,
    KW_DEFAULT = 271,
    KW_RETURN = 272,
    KW_ELSE = 273,
    KW_CASE = 274,
    KW_BOOL = 275,
    KW_CHAR = 276,
    KW_DO = 277,
    KW_FLOAT = 278,
    KW_INT = 279,
    KW_TRUE = 280,
    KW_FALSE = 281,
    INT = 282,
    FLOAT = 283,
    CHAR = 284,
    OP_LOGICAL_OR = 285,
    OP_LOGICAL_AND = 286,
    OP_BITWISE_RSHIFT = 287,
    OP_BITWISE_LSHIFT = 288,
    OP_EQUAL = 289,
    OP_NOTEQUAL = 290,
    OP_GREATEREQUAL = 291,
    OP_LESSEQUAL = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "lalr.yacc.y"

       int itype;
       double dtype;
       char ctype;
       char* string;

#line 102 "lalr.yacc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LALR_YACC_TAB_H_INCLUDED  */
