/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lalr.yacc.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TREE.c"
//#define YYDEBUG 1
void yyerror(char *s);
int yylex();


Symbol * sym_table;
TreeScope * tree_table;
Symbol * addSymbol(char* nome, int param, int type, int isOperand);
Symbol * findSymbol(char * nome);
void installScope(char * nome);
void install(char *nome, int paramfunc, int type, int isOperand);
void context_check(char *nome);
void criarNovoSimbolo(TreeScope * ts, char * name, int type);

void check_type();
TreeScope * newScopeSibling(char* nome);
TreeScope * newScopeChild(char* nome);

#line 94 "lalr.yacc.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 27 "lalr.yacc.y"

       int itype;
       double dtype;
       char ctype;
       char* string;
       int type;

#line 192 "lalr.yacc.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LALR_YACC_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  239

#define YYUNDEFTOK  2
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,     2,     2,     2,    51,     2,
      46,    47,    41,    54,    40,    55,     2,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    38,
      52,    48,    53,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,    49,    45,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    36,    36,    37,    40,    41,    42,    45,    46,    49,
      52,    55,    56,    59,    60,    63,    64,    67,    70,    71,
      74,    75,    78,    81,    82,    85,    86,    89,    90,    93,
      96,    97,    98,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   115,   116,   119,   120,   123,
     126,   129,   130,   133,   134,   135,   138,   139,   142,   145,
     146,   149,   152,   153,   156,   159,   160,   163,   166,   167,
     170,   173,   174,   177,   180,   181,   184,   187,   188,   191,
     192,   195,   198,   199,   202,   203,   204,   205,   208,   211,
     212,   215,   216,   219,   222,   223,   226,   229,   230,   234,
     237,   238,   242,   245,   246,   249,   250,   251,   254,   255,
     256,   257,   260,   261,   262,   265,   266,   267,   270,   271,
     274,   275,   276,   277,   280,   281,   282,   283,   284
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_MODULE", "IDENTIFIER", "KW_EXTERN",
  "KW_VOID", "KW_START", "ARROW", "KW_LABEL", "KW_BREAK", "KW_CONTINUE",
  "KW_IF", "KW_GOTO", "KW_WHILE", "KW_SWITCH", "KW_DEFAULT", "KW_RETURN",
  "KW_ELSE", "KW_CASE", "KW_BOOL", "KW_CHAR", "KW_DO", "KW_FLOAT",
  "KW_INT", "KW_TRUE", "KW_FALSE", "INT", "FLOAT", "CHAR", "OP_LOGICAL_OR",
  "OP_LOGICAL_AND", "OP_BITWISE_RSHIFT", "OP_BITWISE_LSHIFT", "OP_EQUAL",
  "OP_NOTEQUAL", "OP_GREATEREQUAL", "OP_LESSEQUAL", "';'", "':'", "','",
  "'*'", "'['", "']'", "'{'", "'}'", "'('", "')'", "'='", "'|'", "'^'",
  "'&'", "'<'", "'>'", "'+'", "'-'", "'/'", "'!'", "$accept", "PROG",
  "GLOBALS", "GLOBAL", "FUNCTION", "FUNCTIONHEADER", "FUNCTIONREST",
  "MODIFIERS", "PARAMLIST", "PARAMBLOCK", "MOREPARAMBLOCK", "MOREPARAM",
  "PARAM", "RETURNTYPE", "REFERENCE", "DIMENSIONBLOCK", "BLOCK", "CODE",
  "STATEMENT", "elseBLOCK", "SWITCHCASES", "DECLARATIONBLOCK",
  "DECLARATION", "RESTDECLARATION", "INDEXBLOCK", "INITIALIZER",
  "EXPRESSION", "RESTEXPRESSION", "LOGICALOR", "RESTLOGICALOR",
  "LOGICALAND", "RESTLOGICALAND", "BITWISEOR", "RESTBITWISEOR",
  "BITWISEXOR", "RESTBITWISEXOR", "BITWISEAND", "RESTBITWISEAND",
  "EQUALITY", "RESTEQUALITY", "EQUALITYOPERATOR", "RELATION",
  "RESTRELATION", "RELATIONOPERATOR", "SHIFT", "RESTSHIFT",
  "SHIFTOPERATOR", "ADDITION", "RESTADDITION", "SUBTRACTION",
  "RESTSUBTRACTION", "MULTIPLICATION", "RESTMULTIPLICATION", "DIVIDE",
  "RESTDIVIDE", "UNARY3", "UNARY2", "FACTOR", "APPLICATION",
  "MOREEXPRESSION", "TYPE", "IMMEDIATE", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    59,    58,
      44,    42,    91,    93,   123,   125,    40,    41,    61,   124,
      94,    38,    60,    62,    43,    45,    47,    33
};
# endif

#define YYPACT_NINF (-195)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      15,    23,    38,    37,  -195,    86,   114,  -195,  -195,  -195,
    -195,  -195,  -195,    86,  -195,   -32,    40,    48,    41,    86,
    -195,  -195,    43,  -195,  -195,    49,  -195,    41,    88,    59,
    -195,    -6,   104,    82,    85,    78,   122,    83,    93,    76,
      84,  -195,  -195,  -195,  -195,  -195,  -195,   121,    76,   121,
       3,     3,     3,    43,    87,    43,   103,   105,    94,   123,
     113,   102,   106,   101,    44,     9,    79,   100,   107,   116,
      99,  -195,  -195,  -195,    -1,  -195,   117,    41,  -195,    76,
      76,  -195,   120,  -195,  -195,    76,   125,    76,    76,   127,
     146,  -195,   119,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,    76,  -195,    76,  -195,    76,  -195,    76,  -195,
      76,  -195,    76,  -195,  -195,  -195,  -195,    76,  -195,  -195,
    -195,  -195,  -195,    76,  -195,  -195,  -195,    76,    76,  -195,
      76,  -195,    76,  -195,    76,  -195,  -195,   153,   130,    41,
       6,   129,    59,   126,   131,  -195,   132,  -195,   133,   134,
    -195,   124,  -195,    94,   123,   113,   102,   106,   101,    44,
       9,    79,   100,   107,   116,    99,    53,    -7,  -195,   142,
     169,   140,   141,    76,  -195,  -195,    -6,    76,   138,    84,
     164,   143,    76,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -195,   147,  -195,    41,   130,
      41,  -195,   147,   117,   117,  -195,  -195,   131,  -195,   170,
      84,   171,   144,   149,  -195,   147,  -195,   142,  -195,  -195,
    -195,  -195,    84,  -195,  -195,   166,   178,  -195,   147,  -195,
    -195,  -195,    84,    84,  -195,   171,   151,  -195,  -195
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     1,     4,    13,    14,   120,   121,
     122,   123,     3,     4,     7,     0,     0,     0,    25,     4,
       5,    11,    30,     9,    12,     0,     8,    25,     0,    51,
       6,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   124,   125,   128,   127,   126,    34,     0,     0,     0,
       0,     0,     0,    30,     0,    30,     0,     0,    59,    62,
      65,    68,    71,    74,    77,    82,    89,    94,    97,   100,
     103,   105,   108,   113,     0,    26,    53,    25,    49,     0,
       0,   112,     0,    35,    36,     0,     0,     0,     0,     0,
       0,   107,     0,   106,   109,   110,   111,    31,    29,    32,
      44,    43,     0,    58,     0,    61,     0,    64,     0,    67,
       0,    70,     0,    73,    79,    80,    76,     0,    87,    85,
      84,    86,    81,     0,    92,    91,    88,     0,     0,    93,
       0,    96,     0,    99,     0,   102,    15,     0,    18,    25,
       0,    56,    51,     0,   118,    33,     0,    38,     0,     0,
      42,     0,   114,    59,    62,    65,    68,    71,    74,    77,
      82,    89,    94,    97,   100,   103,     0,     0,    16,    20,
       0,     0,     0,     0,    50,    52,   115,     0,     0,     0,
       0,     0,     0,    60,    63,    66,    69,    72,    75,    78,
      83,    90,    95,    98,   101,   104,    27,    10,    25,    18,
      25,    17,    27,    53,    53,    57,   116,   118,   117,    45,
       0,    47,     0,     0,    23,    27,    19,    20,    22,    55,
      54,   119,     0,    37,    39,     0,     0,    40,    27,    24,
      21,    46,     0,     0,    28,    47,     0,    48,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -195,  -195,    -4,   191,  -195,  -195,  -195,  -195,  -195,    31,
       0,   -17,     1,  -195,   -26,  -194,   -15,   -29,  -195,  -195,
     -33,   -18,   128,    61,   -85,  -195,   -37,    51,   108,    52,
     109,    54,   110,    55,   111,    57,    98,    62,   112,    56,
    -195,    95,    63,  -195,   115,    60,  -195,   118,    65,    97,
      66,    92,    67,  -195,    68,   -93,    36,    64,    50,    21,
     -71,  -195
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    12,    13,    14,    15,    23,    16,   137,   138,
     168,   201,   169,   197,    28,   214,    53,    54,    55,   223,
     226,    17,    29,    78,   141,   174,    57,   103,    58,   105,
      59,   107,    60,   109,    61,   111,    62,   113,    63,   116,
     117,    64,   122,   123,    65,   126,   127,    66,   129,    67,
     131,    68,   133,    69,   135,    70,    71,    72,    81,   178,
      18,    73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,    75,    89,   139,    56,   136,    21,    31,   218,    20,
     171,    92,    22,     8,     9,    30,    10,    11,     1,     8,
       9,   229,    10,    11,    97,    90,    99,     3,    41,    42,
      43,    44,    45,   172,   234,    56,    79,    56,     4,   164,
      80,   165,   143,   144,    25,   118,   119,    31,   146,    48,
     148,   149,    32,    33,    34,    35,    36,    37,    38,   196,
      39,   120,   121,     8,     9,    40,    10,    11,    41,    42,
      43,    44,    45,     8,     9,     5,    10,    11,   114,   115,
      31,    46,    27,    91,    47,    93,    26,    22,    74,    48,
     -13,     6,    76,     7,    49,   198,   139,    50,    51,    77,
      52,    41,    42,    43,    44,    45,     8,     9,    82,    10,
      11,   124,   125,   170,    94,    95,    96,    47,   219,   220,
      83,     7,    48,    84,    85,    31,    86,    49,    22,    87,
      50,    51,    98,    52,     8,     9,   205,    10,    11,    88,
     207,   100,   102,   101,   106,   212,    41,    42,    43,    44,
      45,   108,   112,   104,   128,   134,   110,   132,   145,   140,
     151,   166,   130,   147,   209,   150,   152,    48,   167,   176,
     182,   177,   215,   202,   170,    50,    51,   173,    52,   179,
     180,   181,   200,   203,   204,   208,   210,   211,   222,   213,
     225,   227,   228,   232,   233,   224,   238,    19,   199,   216,
     230,   217,   237,   175,   183,   142,   184,   231,   157,   185,
     153,   186,   159,   154,   187,   189,   155,   235,   236,   156,
     188,   191,   163,   190,   158,   162,   206,   192,   221,   193,
       0,   194,     0,   195,     0,     0,     0,     0,   160,     0,
       0,     0,     0,     0,     0,   161
};

static const yytype_int16 yycheck[] =
{
      15,    27,    39,    74,    22,     6,    38,     4,   202,    13,
       4,    48,    44,    20,    21,    19,    23,    24,     3,    20,
      21,   215,    23,    24,    53,    40,    55,     4,    25,    26,
      27,    28,    29,    27,   228,    53,    42,    55,     0,   132,
      46,   134,    79,    80,     4,    36,    37,     4,    85,    46,
      87,    88,     9,    10,    11,    12,    13,    14,    15,     6,
      17,    52,    53,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    20,    21,    38,    23,    24,    34,    35,
       4,    38,    41,    47,    41,    49,    38,    44,    39,    46,
       4,     5,     4,     7,    51,   166,   167,    54,    55,    40,
      57,    25,    26,    27,    28,    29,    20,    21,     4,    23,
      24,    32,    33,   139,    50,    51,    52,    41,   203,   204,
      38,     7,    46,    38,    46,     4,     4,    51,    44,    46,
      54,    55,    45,    57,    20,    21,   173,    23,    24,    46,
     177,    38,    48,    38,    31,   182,    25,    26,    27,    28,
      29,    49,    51,    30,    54,    56,    50,    41,    38,    42,
      14,     8,    55,    38,   179,    38,    47,    46,    38,    43,
      46,    40,   198,     4,   200,    54,    55,    48,    57,    47,
      47,    47,    40,    43,    43,    47,    22,    44,    18,    42,
      19,    47,    43,    27,    16,   210,    45,     6,   167,   199,
     217,   200,   235,   142,   153,    77,   154,   222,   110,   155,
     102,   156,   117,   104,   157,   159,   106,   232,   233,   108,
     158,   161,   130,   160,   112,   128,   176,   162,   207,   163,
      -1,   164,    -1,   165,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,    -1,    -1,    -1,   127
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    59,     4,     0,    38,     5,     7,    20,    21,
      23,    24,    60,    61,    62,    63,    65,    79,   118,    61,
      60,    38,    44,    64,    74,     4,    38,    41,    72,    80,
      60,     4,     9,    10,    11,    12,    13,    14,    15,    17,
      22,    25,    26,    27,    28,    29,    38,    41,    46,    51,
      54,    55,    57,    74,    75,    76,    79,    84,    86,    88,
      90,    92,    94,    96,    99,   102,   105,   107,   109,   111,
     113,   114,   115,   119,    39,    72,     4,    40,    81,    42,
      46,   116,     4,    38,    38,    46,     4,    46,    46,    84,
      74,   114,    84,   114,   115,   115,   115,    75,    45,    75,
      38,    38,    48,    85,    30,    87,    31,    89,    49,    91,
      50,    93,    51,    95,    34,    35,    97,    98,    36,    37,
      52,    53,   100,   101,    32,    33,   103,   104,    54,   106,
      55,   108,    41,   110,    56,   112,     6,    66,    67,   118,
      42,    82,    80,    84,    84,    38,    84,    38,    84,    84,
      38,    14,    47,    86,    88,    90,    92,    94,    96,    99,
     102,   105,   107,   109,   113,   113,     8,    38,    68,    70,
      72,     4,    27,    48,    83,    81,    43,    40,   117,    47,
      47,    47,    46,    85,    87,    89,    91,    93,    95,    97,
     100,   103,   106,   108,   110,   112,     6,    71,   118,    67,
      40,    69,     4,    43,    43,    84,   116,    84,    47,    74,
      22,    44,    84,    42,    73,    72,    68,    70,    73,    82,
      82,   117,    18,    77,    74,    19,    78,    47,    43,    73,
      69,    74,    27,    16,    73,    74,    74,    78,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    64,    64,    65,    65,    66,    66,    67,    68,    68,
      69,    69,    70,    71,    71,    72,    72,    73,    73,    74,
      75,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    78,    78,    79,
      80,    81,    81,    82,    82,    82,    83,    83,    84,    85,
      85,    86,    87,    87,    88,    89,    89,    90,    91,    91,
      92,    93,    93,    94,    95,    95,    96,    97,    97,    98,
      98,    99,   100,   100,   101,   101,   101,   101,   102,   103,
     103,   104,   104,   105,   106,   106,   107,   108,   108,   109,
     110,   110,   111,   112,   112,   113,   113,   113,   114,   114,
     114,   114,   115,   115,   115,   116,   116,   116,   117,   117,
     118,   118,   118,   118,   119,   119,   119,   119,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     2,     3,     1,     2,     2,
       6,     1,     1,     0,     1,     1,     2,     3,     0,     3,
       0,     3,     3,     2,     3,     0,     2,     0,     3,     3,
       0,     2,     2,     3,     1,     2,     2,     6,     3,     6,
       6,     9,     3,     2,     2,     0,     2,     0,     4,     3,
       4,     0,     3,     0,     4,     4,     0,     2,     2,     0,
       3,     2,     0,     3,     2,     0,     3,     2,     0,     3,
       2,     0,     3,     2,     0,     3,     2,     0,     3,     1,
       1,     2,     0,     3,     1,     1,     1,     1,     2,     0,
       3,     1,     1,     2,     0,     3,     2,     0,     3,     2,
       0,     3,     2,     0,     3,     1,     2,     2,     1,     2,
       2,     2,     2,     1,     3,     0,     4,     4,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 3:
#line 37 "lalr.yacc.y"
                                          { installScope( (yyvsp[-2].string) ); }
#line 1549 "lalr.yacc.tab.c"
    break;

  case 10:
#line 52 "lalr.yacc.y"
                                                                     { installScope((yyvsp[-4].string)); }
#line 1555 "lalr.yacc.tab.c"
    break;

  case 22:
#line 78 "lalr.yacc.y"
                                             { install( (yyvsp[-1].string), 1, (yyvsp[-2].itype), 0 ); }
#line 1561 "lalr.yacc.tab.c"
    break;

  case 33:
#line 101 "lalr.yacc.y"
                                    { install((yyvsp[-1].string), 0, 0, 0); }
#line 1567 "lalr.yacc.tab.c"
    break;

  case 38:
#line 106 "lalr.yacc.y"
                                   { install((yyvsp[-1].string),0, 0, 0); }
#line 1573 "lalr.yacc.tab.c"
    break;

  case 49:
#line 123 "lalr.yacc.y"
                                                    {install((yyvsp[-1].string), 0, (yyvsp[-2].type), 0); }
#line 1579 "lalr.yacc.tab.c"
    break;

  case 50:
#line 126 "lalr.yacc.y"
                                                          { (yyval.string) = (yyvsp[-2].string);  }
#line 1585 "lalr.yacc.tab.c"
    break;

  case 56:
#line 138 "lalr.yacc.y"
              { (yyval.itype) = 0; }
#line 1591 "lalr.yacc.tab.c"
    break;

  case 57:
#line 139 "lalr.yacc.y"
                             { (yyval.type) = (yyvsp[0].type); (yyval.itype) = (yyvsp[0].itype); }
#line 1597 "lalr.yacc.tab.c"
    break;

  case 93:
#line 219 "lalr.yacc.y"
                                    { (yyval.itype) = (yyvsp[-1].itype) + (yyvsp[0].itype); }
#line 1603 "lalr.yacc.tab.c"
    break;

  case 94:
#line 222 "lalr.yacc.y"
               { (yyval.itype) = 0; }
#line 1609 "lalr.yacc.tab.c"
    break;

  case 95:
#line 223 "lalr.yacc.y"
                                            { (yyval.itype) = (yyvsp[-1].itype) + (yyvsp[0].itype); install("+", 0, 0, 1); }
#line 1615 "lalr.yacc.tab.c"
    break;

  case 96:
#line 226 "lalr.yacc.y"
                                             { (yyval.itype) = (yyvsp[-1].itype) - (yyvsp[0].itype); }
#line 1621 "lalr.yacc.tab.c"
    break;

  case 97:
#line 229 "lalr.yacc.y"
                  { (yyval.itype) = 0; }
#line 1627 "lalr.yacc.tab.c"
    break;

  case 98:
#line 230 "lalr.yacc.y"
                                                     { (yyval.itype) = (yyvsp[-1].itype) - (yyvsp[0].itype); install("-", 0, 0, 1); }
#line 1633 "lalr.yacc.tab.c"
    break;

  case 99:
#line 234 "lalr.yacc.y"
                                           { (yyval.itype) = (yyvsp[-1].itype) * (yyvsp[0].itype); }
#line 1639 "lalr.yacc.tab.c"
    break;

  case 100:
#line 237 "lalr.yacc.y"
                     { (yyval.itype) = 1; }
#line 1645 "lalr.yacc.tab.c"
    break;

  case 101:
#line 238 "lalr.yacc.y"
                                                   { (yyval.itype) = (yyvsp[-1].itype) * (yyvsp[0].itype); install("*", 0, 0, 1);}
#line 1651 "lalr.yacc.tab.c"
    break;

  case 102:
#line 242 "lalr.yacc.y"
                           { (yyval.itype) = (yyvsp[-1].itype) / (yyvsp[0].itype); }
#line 1657 "lalr.yacc.tab.c"
    break;

  case 103:
#line 245 "lalr.yacc.y"
            { (yyval.itype) = 1; }
#line 1663 "lalr.yacc.tab.c"
    break;

  case 104:
#line 246 "lalr.yacc.y"
                                  { (yyval.itype) = (yyvsp[-1].itype) / (yyvsp[0].itype); install("/", 0, 0, 1); }
#line 1669 "lalr.yacc.tab.c"
    break;

  case 108:
#line 254 "lalr.yacc.y"
                { (yyval.itype) = (yyvsp[0].itype); }
#line 1675 "lalr.yacc.tab.c"
    break;

  case 109:
#line 255 "lalr.yacc.y"
                    { (yyval.itype) = (yyvsp[0].itype); }
#line 1681 "lalr.yacc.tab.c"
    break;

  case 110:
#line 256 "lalr.yacc.y"
                    { (yyval.itype) = (-1) * (yyvsp[0].itype); }
#line 1687 "lalr.yacc.tab.c"
    break;

  case 121:
#line 275 "lalr.yacc.y"
               { (yyval.type) = (yyvsp[0].type); }
#line 1693 "lalr.yacc.tab.c"
    break;

  case 122:
#line 276 "lalr.yacc.y"
                { (yyval.type) = (yyvsp[0].type); }
#line 1699 "lalr.yacc.tab.c"
    break;

  case 123:
#line 277 "lalr.yacc.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 1705 "lalr.yacc.tab.c"
    break;

  case 126:
#line 282 "lalr.yacc.y"
                  { (yyval.ctype) = (yyvsp[0].ctype); }
#line 1711 "lalr.yacc.tab.c"
    break;

  case 127:
#line 283 "lalr.yacc.y"
                  { (yyval.dtype) = (yyvsp[0].dtype); }
#line 1717 "lalr.yacc.tab.c"
    break;

  case 128:
#line 284 "lalr.yacc.y"
                { (yyval.itype) = (yyvsp[0].itype); }
#line 1723 "lalr.yacc.tab.c"
    break;


#line 1727 "lalr.yacc.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 287 "lalr.yacc.y"


TreeScope * newScopeSibling(char* nome){
       TreeScope * ts;
       ts = (TreeScope *) malloc (sizeof(TreeScope));
       ts->name = (char *) malloc(strlen(nome)+1);
       strcpy(ts->name, nome);
       ts->nextSiblingScope = (struct TreeScope *) tree_table;
       tree_table = ts;
       sym_table = ts->symbols;
       return ts;
}

TreeScope * newScopeChild(char* nome){
       TreeScope * ts;
       ts = (TreeScope *) malloc (sizeof(TreeScope));
       ts->name = (char *) malloc(strlen(nome)+1);
       strcpy(ts->name, nome);
       ts->symbols = sym_table;
       ts->firstChildScope = (struct TreeScope *) tree_table;
       tree_table = ts;
       Symbol *s;
       //s = (Symbol *) malloc (sizeof(Symbol));
       sym_table = s;
       return ts;
}

Symbol * addSymbol(char* nome, int param, int type, int isOperand){
       Symbol *s;
       s = (Symbol *) malloc (sizeof(Symbol));
       s->name = (char *) malloc(strlen(nome)+1);
       s->type = type;
       s->isOperand = isOperand;
       s->paramFunc = param;
       strcpy(s->name, nome);
       s->nextSymbol = (struct Symbol *) sym_table;
       sym_table = s;
       return s;
}

Symbol * findSymbol(char * nome){
       Symbol * s;
       for(s = sym_table; s != (Symbol *) 0; s = (Symbol *) s->nextSymbol){
              if(strcmp(s->name, nome) == 0 && s->paramFunc == 0 && s->isOperand == 0){
                     return s;
              }
       }
       return 0;
}

TreeScope * findScope(char *nome){
       TreeScope * ts;
       for(ts = tree_table; ts != (TreeScope *) 0; ts = (TreeScope *) ts->firstChildScope){
              if(strcmp(ts->name, nome) == 0){
                     return ts;
              }
       }
       return 0;
}

void installScope(char * nome){
       TreeScope * ts;
       ts = findScope(nome);
       if(ts == 0){
              ts = newScopeChild(nome);
       } else{
              printf("Escopo já foi definido\n");
       }
}

void install(char * nome, int paramfunc, int type, int isOperand){
       Symbol * s;
       s = findSymbol(nome);
       if(s == 0){
              s = addSymbol(nome, paramfunc, type, isOperand);
       } else{
              printf("%s já foi declarado\n", nome);
       }
}

void context_check(char *nome){
       if(findSymbol(nome) == 0){
              printf("%s é um identificador não declaravel\n", nome);
       }
}

void check_type(){
       printf("Começou\n");
       TreeScope *ts;
       for(ts = tree_table; ts != (TreeScope *) 0; ts = (TreeScope *) ts->firstChildScope){
              printf("Percorrendo: %s\n", ts->name);
              if(ts->symbols == 0){
                     printf("É nulo\n");
              }
              Symbol * s;
              //s = ;
              for(s = ts->symbols; s != (Symbol *) 0; s = (Symbol *) s->nextSymbol){
                     printf("Simbolo: %s\n", s->name);
              }
       }
}

void yyerror(char *s){
       fprintf(stderr, "%s\n", s);
}

int main(){
       //TreeScope * root;
       //yydebug =  1;
       yyparse();
       check_type();
       return 0;
}
