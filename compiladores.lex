/*
 * Compiladores
 *
 */

%{
int num_lines = 1, col = 0;
%}

underline   _
letter     [a-zA-Z]
hexLetter  [a-fA-F]
digit     [0-9]
char       (letter|digit|" " |())
comment    ("/∗"|"//")("∗")({char}+)"∗/"
hextail        ({digit}|{hexLetter}){1,8}
hex            0[xX]{hextail}
identifier ({underline}|{letter})({underline}|{letter}|{digit}){0,30}
bin    [0-1]+"b"
int    ("-"|"")({digit}){1,32}
string \".*.\"


%%
"//".*.                   ;
"/*".*."*/"               printf("ignorando comentario\n");
" "                       ;

\n  num_lines++;          col = 0;
"module"                  col += strlen(yytext); printf("module\n"); 
"for"                     col += strlen(yytext); printf("for\n");
"while"                   col += strlen(yytext); printf("while\n");
"extern"                  col += strlen(yytext); printf("extern\n");
"break"                   col += strlen(yytext); printf("break\n");
"continue"                col += strlen(yytext); printf("continue\n");
"if"                      col += strlen(yytext); printf("if\n");
"else"                    col += strlen(yytext); printf("else\n");
"switch"                  col += strlen(yytext); printf("switch\n");
"default"                 col += strlen(yytext); printf("default\n");
"gotoconsideredharmfu"    col += strlen(yytext); printf("gotoconsideredharmfu\n");
"label"                   col += strlen(yytext); printf("label\n");
"int"                     col += strlen(yytext); printf("int\n");
"bool"                    col += strlen(yytext); printf("bool\n");
"float"                   col += strlen(yytext); printf("float\n");
"char"                    col += strlen(yytext); printf("char\n");
"untyped"                 col += strlen(yytext); printf("untyped\n");
"void"                    col += strlen(yytext); printf("void\n");
"start"                   col += strlen(yytext); printf("start\n");
"{"                       col += strlen(yytext); printf("{\n");
"}"                       col += strlen(yytext); printf("}\n");
"("                       col += strlen(yytext); printf("(\n");
")"                       col += strlen(yytext); printf(")\n");
"+"                       col += strlen(yytext); printf("+\n");
"-"                       col += strlen(yytext); printf("-\n");
"~"                       col += strlen(yytext); printf("~\n");
"*"                       col += strlen(yytext); printf("%s\n", yytext);
"/"                       col += strlen(yytext); printf("%s\n", yytext);
"%"                       col += strlen(yytext); printf("%s\n", yytext);
">>"                      col += strlen(yytext); printf("%s\n", yytext);
"<<"                      col += strlen(yytext); printf("%s\n", yytext);
"#import"                 col += strlen(yytext); printf("%s\n", yytext);
{hex}                     col += strlen(yytext); printf("%s hex\n", yytext);
{bin}                     col += strlen(yytext); printf("%s bin\n", yytext);
{int}                     col += strlen(yytext); printf("%s int\n", yytext);
{string}                  col += strlen(yytext); printf("%s str\n", yytext);
{identifier}              col += strlen(yytext); printf("%s\n", yytext);
.                         col += strlen(yytext); printf("unspected char '%s' at line: %d col %d\n", yytext, num_lines,col);
%%

int main()
{
    yylex();
    return 0;
}
