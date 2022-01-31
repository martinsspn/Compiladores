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





%%
"module"                  col += yyleng; return KW_MODULE;
"while"                   col += yyleng; return KW_WHILE;
"extern"                  col += yyleng; return KW_EXTERN;
%%
int yywrap(void) {
    return 1;
}