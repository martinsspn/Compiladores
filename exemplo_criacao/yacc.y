%{
    #include <stdio.h>
    //#define YYDEBUG 1
    int yylex();
    void yyerror(char *s);
%}
//%define parse.error verbose

%start p
%token KW_MODULE
%%

p:  KW_MODULE {printf("Exempl");}
    ;

%%

void yyerror(char *s){
    fprintf(stderr, "%s\n", s);
}

int main(){
    //yydebug = 1;
    yyparse();
    return 0;
}