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
"module"                  col += yyleng; printf("KW_MODULE\n"); 
"while"                   col += yyleng; printf("KW_WHILE\n");
"extern"                  col += yyleng; printf("KW_EXTERN\n");
"break"                   col += yyleng; printf("KW_BREAK\n");
"continue"                col += yyleng; printf("KW_CONTINUE\n");
"if"                      col += yyleng; printf("KW_IF\n");
"else"                    col += yyleng; printf("KW_ELSE\n");
"false"                   col += yyleng; printf("KW_FALSE\n");
"true"                    col += yyleng; printf("KW_TRUE\n");
"switch"                  col += yyleng; printf("KW_SWITCH\n");
"case"                    col += yyleng; printf("KW_CASE\n");
"default"                 col += yyleng; printf("KW_DEFAULT\n");
"gotoconsideredharmfu"    col += yyleng; printf("KW_GOTO\n");
"label"                   col += yyleng; printf("KW_LABEL\n");
"int"                     col += yyleng; printf("KW_INT\n");
"bool"                    col += yyleng; printf("KW_BOOL\n");
"float"                   col += yyleng; printf("KW_FLOAT\n");
"char"                    col += yyleng; printf("KW_CHAR\n");
"untyped"                 col += yyleng; printf("KW_UNTYPED\n");
"void"                    col += yyleng; printf("KW_VOID\n");
"return"                  col += yyleng; printf("KW_RETURN\n");
"start"                   col += yyleng; printf("KW_START\n");
"{"                       col += yyleng; printf("LBRACE\n");
"}"                       col += yyleng; printf("RBRACE\n");
"("                       col += yyleng; printf("LPAREN\n");
")"                       col += yyleng; printf("RPAREN\n");
"["                       col += yyleng; printf("LBRACKET\n");
"]"                       col += yyleng; printf("RBRACKET\n");
","                       col += yyleng; printf("COMMA\n");
"+"                       col += yyleng; printf("OP_ADD\n");
"-"                       col += yyleng; printf("OP_SUBTRACT\n");
"~"                       col += yyleng; printf("OP_BITWISE_COMPLEMENT\n");
"*"                       col += yyleng; printf("OP_MULTIPLY\n");
"/"                       col += yyleng; printf("OP_DIVIDE\n");
"%"                       col += yyleng; printf("OP_MODULUS\n");
"<"                       col += yyleng; printf("OP_LESS\n");
"<="                      col += yyleng; printf("OP_LESSEQUAL\n");
">"                       col += yyleng; printf("OP_GREATER\n");
">="                      col += yyleng; printf("OP_GREATEREQUAL\n");
"=="                      col += yyleng; printf("OP_EQUAL\n");
"!="                      col += yyleng; printf("OP_NOTEQUAL\n");
"||"                      col += yyleng; printf("OP_LOGICAL_OR\n");
"!"                       col += yyleng; printf("OP_NOT\n");
">>"                      col += yyleng; printf("OP_BITWISE_RSHIFT\n");
"<<"                      col += yyleng; printf("OP_BITWISE_LSHIFT\n");
"^"                       col += yyleng; printf("OP_BITWISE_XOR\n");
"&&"                      col += yyleng; printf("OP_LOGICAL_AND\n");
"&"                       col += yyleng; printf("OP_BITWISE_AND\n");
";"                       col += yyleng; printf("SEMICOLON\n");
":"                       col += yyleng; printf("COLON\n");
"->"                      col += yyleng; printf("ARROW\n");
"="                       col += yyleng; printf("OP_ASSIGN\n");
"|"                       col += yyleng; printf("OP_BITWISE_OR\n");
"?"                       col += yyleng; printf("OP_TERNARY_IF\n");
"#import"                 col += yyleng; printf("KW_IMPORT\n", yytext);
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
