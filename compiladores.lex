/*
 * Compiladores
 *
 */

 int num_lines = 0, col = 0;

module  module
underline   _
letter     [a-zA-Z]
number     [0-9]

identifier ({underline}|{letter})({underline}|{letter}|{number}){1,30}
bin    [0-1]
int    ({+}|{-}|{~})number{1,64}

%%
\n  num_lines++; col = 0;
.   col++;
{identifier} printf("Found a identifier %s!", yytext);
%%

main()
{
    yylex();
}
