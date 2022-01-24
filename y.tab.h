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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    KW_LABEL = 263,
    KW_BREAK = 264,
    KW_CONTINUE = 265,
    KW_IF = 266,
    KW_GOTO = 267,
    KW_WHILE = 268,
    KW_SWITCH = 269,
    KW_DEFAULT = 270,
    KW_RETURN = 271,
    KW_ELSE = 272,
    KW_CASE = 273,
    KW_BOOL = 274,
    KW_CHAR = 275,
    KW_DO = 276,
    KW_FLOAT = 277,
    KW_INT = 278,
    KW_TRUE = 279,
    KW_FALSE = 280,
    INT = 281,
    FLOAT = 282,
    CHAR = 283,
    OP_LOGICAL_OR = 284,
    OP_LOGICAL_AND = 285,
    OP_BITWISE_RSHIFT = 286,
    OP_BITWISE_LSHIFT = 287,
    OP_EQUAL = 288
  };
#endif
/* Tokens.  */
#define KW_MODULE 258
#define IDENTIFIER 259
#define KW_EXTERN 260
#define KW_VOID 261
#define KW_START 262
#define KW_LABEL 263
#define KW_BREAK 264
#define KW_CONTINUE 265
#define KW_IF 266
#define KW_GOTO 267
#define KW_WHILE 268
#define KW_SWITCH 269
#define KW_DEFAULT 270
#define KW_RETURN 271
#define KW_ELSE 272
#define KW_CASE 273
#define KW_BOOL 274
#define KW_CHAR 275
#define KW_DO 276
#define KW_FLOAT 277
#define KW_INT 278
#define KW_TRUE 279
#define KW_FALSE 280
#define INT 281
#define FLOAT 282
#define CHAR 283
#define OP_LOGICAL_OR 284
#define OP_LOGICAL_AND 285
#define OP_BITWISE_RSHIFT 286
#define OP_BITWISE_LSHIFT 287
#define OP_EQUAL 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
