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
"module"                  col += yyleng; printf("KW_MODULE at line: %d col %d\n", yylineno,col); 
"while"                   col += yyleng; printf("KW_WHILE at line: %d col %d\n", yylineno,col);
"extern"                  col += yyleng; printf("KW_EXTERN at line: %d col %d\n", yylineno,col);
"break"                   col += yyleng; printf("KW_BREAK at line: %d col %d\n", yylineno,col);
"continue"                col += yyleng; printf("KW_CONTINUE at line: %d col %d\n", yylineno,col);
"if"                      col += yyleng; printf("KW_IF at line: %d col %d\n", yylineno,col);
"else"                    col += yyleng; printf("KW_ELSE at line: %d col %d\n", yylineno,col);
"false"                   col += yyleng; printf("KW_FALSE at line: %d col %d\n", yylineno,col);
"true"                    col += yyleng; printf("KW_TRUE at line: %d col %d\n", yylineno,col);
"switch"                  col += yyleng; printf("KW_SWITCH at line: %d col %d\n", yylineno,col);
"case"                    col += yyleng; printf("KW_CASE at line: %d col %d\n", yylineno,col);
"default"                 col += yyleng; printf("KW_DEFAULT at line: %d col %d\n", yylineno,col);
"gotoconsideredharmfu"    col += yyleng; printf("KW_GOTO at line: %d col %d\n", yylineno,col);
"label"                   col += yyleng; printf("KW_LABEL at line: %d col %d\n", yylineno,col);
"int"                     col += yyleng; printf("KW_INT at line: %d col %d\n", yylineno,col);
"bool"                    col += yyleng; printf("KW_BOOL at line: %d col %d\n", yylineno,col);
"float"                   col += yyleng; printf("KW_FLOAT at line: %d col %d\n", yylineno,col);
"char"                    col += yyleng; printf("KW_CHAR at line: %d col %d\n", yylineno,col);
"untyped"                 col += yyleng; printf("KW_UNTYPED at line: %d col %d\n", yylineno,col);
"void"                    col += yyleng; printf("KW_VOID at line: %d col %d\n", yylineno,col);
"return"                  col += yyleng; printf("KW_RETURN at line: %d col %d\n", yylineno,col);
"start"                   col += yyleng; printf("KW_START at line: %d col %d\n", yylineno,col);
"{"                       col += yyleng; printf("LBRACE at line: %d col %d\n", yylineno,col);
"}"                       col += yyleng; printf("RBRACE at line: %d col %d\n", yylineno,col);
"("                       col += yyleng; printf("LPAREN at line: %d col %d\n", yylineno,col);
")"                       col += yyleng; printf("RPAREN at line: %d col %d\n", yylineno,col);
"["                       col += yyleng; printf("LBRACKET at line: %d col %d\n", yylineno,col);
"]"                       col += yyleng; printf("RBRACKET at line: %d col %d\n", yylineno,col);
","                       col += yyleng; printf("COMMA at line: %d col %d\n", yylineno,col);
"+"                       col += yyleng; printf("OP_ADD at line: %d col %d\n", yylineno,col);
"-"                       col += yyleng; printf("OP_SUBTRACT at line: %d col %d\n", yylineno,col);
"~"                       col += yyleng; printf("OP_BITWISE_COMPLEMENT at line: %d col %d\n", yylineno,col);
"*"                       col += yyleng; printf("OP_MULTIPLY at line: %d col %d\n", yylineno,col);
"/"                       col += yyleng; printf("OP_DIVIDE at line: %d col %d\n", yylineno,col);
"%"                       col += yyleng; printf("OP_MODULUS at line: %d col %d\n", yylineno,col);
"<"                       col += yyleng; printf("OP_LESS at line: %d col %d\n", yylineno,col);
"<="                      col += yyleng; printf("OP_LESSEQUAL at line: %d col %d\n", yylineno,col);
">"                       col += yyleng; printf("OP_GREATER at line: %d col %d\n", yylineno,col);
">="                      col += yyleng; printf("OP_GREATEREQUAL at line: %d col %d\n", yylineno,col);
"=="                      col += yyleng; printf("OP_EQUAL at line: %d col %d\n", yylineno,col);
"!="                      col += yyleng; printf("OP_NOTEQUAL at line: %d col %d\n", yylineno,col);
"||"                      col += yyleng; printf("OP_LOGICAL_OR at line: %d col %d\n", yylineno,col);
"!"                       col += yyleng; printf("OP_NOT at line: %d col %d\n", yylineno,col);
">>"                      col += yyleng; printf("OP_BITWISE_RSHIFT at line: %d col %d\n", yylineno,col);
"<<"                      col += yyleng; printf("OP_BITWISE_LSHIFT at line: %d col %d\n", yylineno,col);
"^"                       col += yyleng; printf("OP_BITWISE_XOR at line: %d col %d\n", yylineno,col);
"&&"                      col += yyleng; printf("OP_LOGICAL_AND at line: %d col %d\n", yylineno,col);
"&"                       col += yyleng; printf("OP_BITWISE_AND at line: %d col %d\n", yylineno,col);
";"                       col += yyleng; printf("SEMICOLON at line: %d col %d\n", yylineno,col);
":"                       col += yyleng; printf("COLON at line: %d col %d\n", yylineno,col);
"->"                      col += yyleng; printf("ARROW at line: %d col %d\n", yylineno,col);
"="                       col += yyleng; printf("OP_ASSIGN at line: %d col %d\n", yylineno,col);
"|"                       col += yyleng; printf("OP_BITWISE_OR at line: %d col %d\n", yylineno,col);
"?"                       col += yyleng; printf("OP_TERNARY_IF at line: %d col %d\n", yylineno,col);
"#import"                 col += yyleng; printf("KW_IMPORT at line: %d col %d\n", yylineno,col);
{hex}                     col += yyleng; printf("%s hex at line: %d col %d\n", yytext, yylineno,col);
{bin}                     col += yyleng; printf("%s bin at line: %d col %d\n", yytext, yylineno,col);
{int}                     col += yyleng; printf("%s int at line: %d col %d\n", yytext, yylineno,col);
{charobj}                 col += yyleng; printf("%s char at line: %d col %d\n", yytext, yylineno,col);
{string}                  col += yyleng; printf("%s str at line: %d col %d\n", yytext, yylineno,col);
{identifier}              col += yyleng; printf("%s\n", yytext);
.                         col += yyleng; printf("unspected char '%s' at line: %d col %d\n", yytext, yylineno,col);
%%

int main()
{
    yylex();
    return 0;
}
