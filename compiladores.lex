/*
 * Compiladores
 * 
 */

%{
#include "lex.yy.h"
int col = 1;


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
error ("\n"|".")





%%
"//".*                    ;
"/*"(.|\n)*"*/"           ;
" "                       col++;
."\n"                     col = 1;
"do"                      col += yyleng; return DO;
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
"untyped"                 col += yyleng; return KW_UNTYPED;
"void"                    col += yyleng; return KW_VOID;
"return"                  col += yyleng; return KW_RETURN;
"start"                   col += yyleng; return KW_START;
"->"                      col += yyleng; return ARROW;
"{"                       col += yyleng; return LBRACE;
"}"                       col += yyleng; return RBRACE;
"("                       col += yyleng; return LPAREN;
")"                       col += yyleng; return RPAREN;
"["                       col += yyleng; return LBRACKET;
"]"                       col += yyleng; return RBRACKET;
","                       col += yyleng; return COMMA;
"+"                       col += yyleng; return OP_ADD;
"-"                       col += yyleng; return OP_SUBTRACT;
"~"                       col += yyleng; return OP_BITWISE_COMPLEMENT;
"*"                       col += yyleng; return OP_MULTIPLY;
"/"                       col += yyleng; return OP_DIVIDE;
"%"                       col += yyleng; return OP_MODULUS;
"<"                       col += yyleng; return OP_LESS;
"<="                      col += yyleng; return OP_LESSEQUAL;
">"                       col += yyleng; return OP_GREATER;
">="                      col += yyleng; return OP_GREATEREQUAL;
"=="                      col += yyleng; return OP_EQUAL;
"!="                      col += yyleng; return OP_NOTEQUAL;
"||"                      col += yyleng; return OP_LOGICAL_OR;
"!"                       col += yyleng; return OP_NOT;
">>"                      col += yyleng; return OP_BITWISE_RSHIFT;
"<<"                      col += yyleng; return OP_BITWISE_LSHIFT;
"^"                       col += yyleng; return OP_BITWISE_XOR;
"&&"                      col += yyleng; return OP_LOGICAL_AND;
"&"                       col += yyleng; return OP_BITWISE_AND;
";"                       col += yyleng; return SEMICOLON;
":"                       col += yyleng; return COLON;
"="                       col += yyleng; return OP_ASSIGN;
"|"                       col += yyleng; return OP_BITWISE_OR;
"?"                       col += yyleng; return OP_TERNARY_IF;
"#import"                 col += yyleng; return KW_IMPORT;
{hex}                     col += yyleng; return HEX;
{bin}                     col += yyleng; return BIN;
{int}                     col += yyleng; return INT;
{floatpoint}              col += yyleng; return FLOAT;
{charobj}                 col += yyleng; return CHAR;
{string}                  col += yyleng; return STRING;
{identifier}              col += yyleng; return IDENTIFIER;
.                         col += yyleng; return ERROR;
%%
int yywrap(void) {
    return 1;
}