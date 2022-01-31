%{
    #include <stdio.h>
    int yylex();
    void yyerror(char *s);
%}
%token KW_MODULE
%start PROG
%%

PROG : { printf("TESTE\n"); } KW_MODULE ';'

%%

void yyerror(char *s){
    printf("ERROR\n");
}

int main(){
    return yyparse();
}