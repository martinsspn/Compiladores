/*
 * Compiladores
 * 
 */

%{
//#include "lex.yy.h"
int col = 1;
#include "lalr.yacc.tab.h"
#define YYSTYPE yyltype
#define ERROR 500
%}


%option yylineno

letter     [a-zA-Z]
hexLetter  [a-fA-F]
digit     [0-9]
char       (letter|digit|" " |())
charobj    "\'"({letter}|{digit}|" "){0,1}"\'"
comment    ("/∗"|"//")({char}+)"∗/"
hextail        ({digit}|{hexLetter}){1,8}
hex            0[xX]{hextail}
identifier (\_|{letter})(\_|{letter}|{digit}){0,30}
bin    [0-1]+"b"
int    ("-"|"")({digit}){1,32}
floatpoint {int}("."|""){digit}{0,32}
string \".*.\"





%%
"//".*                    ;
"/*"(.|\n)*"*/"           ;
" "                       col++;
."\n"                     col = 1;
"do"                      col += yyleng; return KW_DO;
"module"                  col += yyleng; return KW_MODULE;
"while"                   col += yyleng; return KW_WHILE;
"extern"                  col += yyleng; return KW_EXTERN;
"break"                   col += yyleng; return KW_BREAK;
"continue"                col += yyleng; return KW_CONTINUE;
"if"                      col += yyleng; return KW_IF;
"else"                    col += yyleng; return KW_ELSE;
"false"                   col += yyleng; return KW_FALSE;
"true"                    col += yyleng; return KW_TRUE;
"switch"                  col += yyleng; return KW_SWITCH;
"case"                    col += yyleng; return KW_CASE;
"default"                 col += yyleng; return KW_DEFAULT;
"gotoconsideredharmful"   col += yyleng; return KW_GOTO;
"label"                   col += yyleng; return KW_LABEL;
"int"                     col += yyleng; return KW_INT;
"bool"                    col += yyleng; return KW_BOOL;
"float"                   col += yyleng; return KW_FLOAT;
"char"                    col += yyleng; return KW_CHAR;
"void"                    col += yyleng; return KW_VOID;
"return"                  col += yyleng; return KW_RETURN;
"start"                   col += yyleng; return KW_START;
"->"                      col += yyleng; return ARROW;
"{"                       col += yyleng; return '{';
"}"                       col += yyleng; return '}';
"("                       col += yyleng; return '(';
")"                       col += yyleng; return ')';
"["                       col += yyleng; return '[';
"]"                       col += yyleng; return ']';
","                       col += yyleng; return ',';
"+"                       col += yyleng; return '+';
"-"                       col += yyleng; return '-';
"~"                       col += yyleng; return '~';
"*"                       col += yyleng; return '*';
"/"                       col += yyleng; return '/';
"%"                       col += yyleng; return '%';
"<"                       col += yyleng; return '<';
"<="                      col += yyleng; return OP_LESSEQUAL;
">"                       col += yyleng; return '>';
">="                      col += yyleng; return OP_GREATEREQUAL;
"=="                      col += yyleng; return OP_EQUAL;
"!="                      col += yyleng; return OP_NOTEQUAL;
"||"                      col += yyleng; return OP_LOGICAL_OR;
"!"                       col += yyleng; return '!';
">>"                      col += yyleng; return OP_BITWISE_RSHIFT;
"<<"                      col += yyleng; return OP_BITWISE_LSHIFT;
"^"                       col += yyleng; return '^';
"&&"                      col += yyleng; return OP_LOGICAL_AND;
"&"                       col += yyleng; return '&';
";"                       col += yyleng; return ';';
":"                       col += yyleng; return ':';
"="                       col += yyleng; return '=';
"|"                       col += yyleng; return '|';
"?"                       col += yyleng; return '?';
{int}                     col += yyleng; yylval.itype = (int) atoi(yytext); return INT;
{floatpoint}              col += yyleng; yylval.dtype = (double) atol(yytext); return FLOAT;
{charobj}                 col += yyleng; yylval.ctype = (char) yytext[0]; return CHAR;
{identifier}              col += yyleng; yylval.string = (char *) strdup(yytext); return IDENTIFIER;
.                         col += yyleng;  return ERROR;
%%
int yywrap(void) {
    return 1;
}