/*
 * Compiladores
 * 
 */

%{
int num_lines = 1, col = 1;
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
string \".*.\"

START    "/*"
END    "*/"
SIMPLE    [^]
COMPLEX    ""/[^/]

%s START_COMMENT COMMENT END_COMMENT


%%
"//".*.                   ;
"/*"(.|\n)*"*/"        printf("ignorando comentario\n");
" "                       ;
\n  num_lines++;          col = 0;
"module"                  col += yyleng; printf("module\n"); 
"for"                     col += yyleng; printf("for\n");
"while"                   col += yyleng; printf("while\n");
"extern"                  col += yyleng; printf("extern\n");
"break"                   col += yyleng; printf("break\n");
"continue"                col += yyleng; printf("continue\n");
"if"                      col += yyleng; printf("if\n");
"else"                    col += yyleng; printf("else\n");
"switch"                  col += yyleng; printf("switch\n");
"default"                 col += yyleng; printf("default\n");
"gotoconsideredharmfu"    col += yyleng; printf("gotoconsideredharmfu\n");
"label"                   col += yyleng; printf("label\n");
"int"                     col += yyleng; printf("int\n");
"bool"                    col += yyleng; printf("bool\n");
"float"                   col += yyleng; printf("float\n");
"char"                    col += yyleng; printf("char\n");
"untyped"                 col += yyleng; printf("untyped\n");
"void"                    col += yyleng; printf("void\n");
"start"                   col += yyleng; printf("start\n");
"{"                       col += yyleng; printf("{\n");
"}"                       col += yyleng; printf("}\n");
"("                       col += yyleng; printf("(\n");
")"                       col += yyleng; printf(")\n");
"["                       col += yyleng; printf("(\n");
"]"                       col += yyleng; printf(")\n");
","                       col += yyleng; printf(")\n");
"+"                       col += yyleng; printf("+\n");
"-"                       col += yyleng; printf("-\n");
"~"                       col += yyleng; printf("~\n");
"*"                       col += yyleng; printf("%s\n", yytext);
"/"                       col += yyleng; printf("%s\n", yytext);
"%"                       col += yyleng; printf("%s\n", yytext);
"<"                       col += yyleng; printf("%s\n", yytext);
"<="                      col += yyleng; printf("%s\n", yytext);
">"                       col += yyleng; printf("%s\n", yytext);
">="                      col += yyleng; printf("%s\n", yytext);
"=="                      col += yyleng; printf("%s\n", yytext);
"!="                      col += yyleng; printf("%s\n", yytext);
"||"                      col += yyleng; printf("%s\n", yytext);
"!"                       col += yyleng; printf("%s\n", yytext);
">>"                      col += yyleng; printf("%s\n", yytext);
"<<"                      col += yyleng; printf("%s\n", yytext);
"&&"                      col += yyleng; printf("%s\n", yytext);
"&"                       col += yyleng; printf("%s\n", yytext);
";"                       col += yyleng; printf("%s\n", yytext);
":"                       col += yyleng; printf("%s\n", yytext);
"->"                      col += yyleng; printf("%s\n", yytext);
"="                       col += yyleng; printf("%s\n", yytext);
"|"                       col += yyleng; printf("%s\n", yytext);
"?"                       col += yyleng; printf("%s\n", yytext);
"#import"                 col += yyleng; printf("%s\n", yytext);
{hex}                     col += yyleng; printf("%s hex\n", yytext);
{bin}                     col += yyleng; printf("%s bin\n", yytext);
{int}                     col += yyleng; printf("%s int\n", yytext);
{charobj}                 col += yyleng; printf("%s char\n", yytext);
{string}                  col += yyleng; printf("%s str\n", yytext);
{identifier}              col += yyleng; printf("%s\n", yytext);
.                         col += yyleng; printf("unspected char '%s' at line: %d col %d\n", yytext, yylineno,col);
%%

int main()
{
    yylex();
    return 0;
}
