/*
 * Compiladores
 *
 */

%{
int num_lines = 1, col = 1;
%}

letter     [a-zA-Z]
hexLetter  [a-fA-F]
digit      [0-9]
char       (letter|digit|())
comment    ("/∗"|"//")("∗")(.*)"∗/"
hextail        ({digit}|{hexLetter}){1,8}
hex            0[xX]{hextail}
identifier (\_|{letter})(\_|{letter}|{digit}){0,30}
bin    [0-1]+"b"
int    ("-"|"")({digit}){1,32}
string \".*.\"


%%
" "                       col++;
"//".*.                   printf("ignorando comentario\n");
"/*".*."*/"               printf("ignorando comentario\n");
";"                       col += yyleng; printf("%s\n", yytext);
\n                        num_lines++; col = 0;
"module"                  col += yyleng; printf("%s\n", yytext);
"for"                     col += yyleng; printf("%s\n", yytext);
"while"                   col += yyleng; printf("%s\n", yytext);
"extern"                  col += yyleng; printf("%s\n", yytext);
"break"                   col += yyleng; printf("%s\n", yytext);
"continue"                col += yyleng; printf("%s\n", yytext);
"if"                      col += yyleng; printf("%s\n", yytext);
"else"                    col += yyleng; printf("%s\n", yytext);
"switch"                  col += yyleng; printf("%s\n", yytext);
"default"                 col += yyleng; printf("%s\n", yytext);
"gotoconsideredharmfu"    col += yyleng; printf("%s\n", yytext);
"label"                   col += yyleng; printf("%s\n", yytext);
"int"                     col += yyleng; printf("%s\n", yytext);
"bool"                    col += yyleng; printf("%s\n", yytext);
"float"                   col += yyleng; printf("%s\n", yytext);
"char"                    col += yyleng; printf("%s\n", yytext);
"untyped"                 col += yyleng; printf("%s\n", yytext);
"void"                    col += yyleng; printf("%s\n", yytext);
"start"                   col += yyleng; printf("%s\n", yytext);
"{"                       col += yyleng; printf("%s\n", yytext);
"}"                       col += yyleng; printf("%s\n", yytext);
"("                       col += yyleng; printf("%s\n", yytext);
")"                       col += yyleng; printf("%s\n", yytext);
"+"                       col += yyleng; printf("%s\n", yytext);
"-"                       col += yyleng; printf("%s\n", yytext);
"~"                       col += yyleng; printf("%s\n", yytext);
"*"                       col += yyleng; printf("%s\n", yytext);
"/"                       col += yyleng; printf("%s\n", yytext);
"%"                       col += yyleng; printf("%s\n", yytext);
">>"                      col += yyleng; printf("%s\n", yytext);
"<<"                      col += yyleng; printf("%s\n", yytext);
"="                       col += yyleng; printf("%s\n", yytext);
"#import"                 col += yyleng; printf("%s\n", yytext);
{hex}                     col += yyleng; printf("%s hex\n", yytext);
{bin}                     col += yyleng; printf("%s bin\n", yytext);
{int}                     col += yyleng; printf("%s int\n", yytext);
{string}                  col += yyleng; printf("%s str\n", yytext);
{identifier}              col += yyleng; printf("%s\n", yytext);
.                         col += yyleng; printf("unspected char '%s' at line: %d col %d\n", yytext, num_lines,col);
%%

int main()
{
    yylex();
    return 0;
}
