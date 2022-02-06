%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TREE.c"
//#define YYDEBUG 1
void yyerror(char *s);
int yylex();


Symbol * sym_table;
Symbol * addSymbol(char* nome);
Symbol * findSymbol(char * nome);
void install(char *nome);
void context_check(char *nome);
void criarNovoSimbolo(TreeScope * ts, char * name, int type);
%}
//%define parse.error verbose
%token KW_MODULE IDENTIFIER KW_EXTERN KW_VOID KW_START ARROW KW_LABEL KW_BREAK KW_CONTINUE KW_IF KW_GOTO KW_WHILE KW_SWITCH KW_DEFAULT KW_RETURN KW_ELSE KW_CASE KW_BOOL KW_CHAR KW_DO KW_FLOAT KW_INT KW_TRUE KW_FALSE INT FLOAT CHAR OP_LOGICAL_OR OP_LOGICAL_AND OP_BITWISE_RSHIFT OP_BITWISE_LSHIFT OP_EQUAL OP_NOTEQUAL OP_GREATEREQUAL OP_LESSEQUAL
%start PROG
%union {
       int itype;
       double dtype;
       char ctype;
       char* string;
}
%%

PROG :        /* empty */     
       | KW_MODULE IDENTIFIER ';' GLOBALS { install( $<string>2 ); }
       ;

GLOBALS :  /* empty */
        | GLOBAL GLOBALS
        | KW_EXTERN GLOBAL GLOBALS
        ;

GLOBAL : FUNCTION
       | DECLARATIONBLOCK ';'
       ;

FUNCTION : FUNCTIONHEADER FUNCTIONREST
           ;

FUNCTIONHEADER : MODIFIERS IDENTIFIER ':' PARAMLIST ARROW RETURNTYPE { install($<string>2); }
               ;

FUNCTIONREST : ';'
             | BLOCK
             ;

MODIFIERS : 
          | KW_START
          ;

PARAMLIST : KW_VOID
          | PARAMBLOCK MOREPARAMBLOCK
          ;

PARAMBLOCK : TYPE PARAM MOREPARAM
           ;

MOREPARAMBLOCK : 
               | ';' PARAMBLOCK MOREPARAMBLOCK
               ;

MOREPARAM : 
          | ',' PARAM MOREPARAM
          ;

PARAM : REFERENCE IDENTIFIER DIMENSIONBLOCK { install( $<string>2 ); }
      ;

RETURNTYPE : KW_VOID DIMENSIONBLOCK
           |TYPE REFERENCE DIMENSIONBLOCK
           ;

REFERENCE :
          | '*' REFERENCE
          ;

DIMENSIONBLOCK : 
               | '['']' DIMENSIONBLOCK
               ;

BLOCK : '{' CODE '}'
      ;

CODE : 
     | BLOCK CODE
     | STATEMENT CODE
     ;

STATEMENT : KW_LABEL IDENTIFIER ';' { install($<string>2); }
          | ';'
          | KW_BREAK ';'
          | KW_CONTINUE ';'
          | KW_IF '(' EXPRESSION ')' BLOCK elseBLOCK
          | KW_GOTO IDENTIFIER ';' { install($<string>2); }
          | KW_WHILE '(' EXPRESSION ')' KW_DO BLOCK
          | KW_DO BLOCK KW_WHILE '(' EXPRESSION ')'
          | KW_SWITCH '(' EXPRESSION ')' '{' SWITCHCASES KW_DEFAULT BLOCK '}'
          | KW_RETURN EXPRESSION ';'
          | EXPRESSION ';'
          | DECLARATIONBLOCK ';'
          ;

elseBLOCK : 
          | KW_ELSE BLOCK
          ;

SWITCHCASES : 
            | KW_CASE INT BLOCK SWITCHCASES
            ;

DECLARATIONBLOCK : TYPE DECLARATION RESTDECLARATION
                 ;

DECLARATION : REFERENCE IDENTIFIER INDEXBLOCK INITIALIZER { install($<string>2); }
            ;

RESTDECLARATION : 
                | ',' DECLARATION RESTDECLARATION
                ;

INDEXBLOCK :
           | '[' INT ']' INDEXBLOCK
           | '[' IDENTIFIER ']' INDEXBLOCK
           ;

INITIALIZER : 
            | '=' EXPRESSION
            ;

EXPRESSION : LOGICALOR RESTEXPRESSION
           ;

RESTEXPRESSION : 
               | '=' LOGICALOR RESTEXPRESSION
               ;

LOGICALOR : LOGICALAND RESTLOGICALOR
          ;

RESTLOGICALOR : 
              | OP_LOGICAL_OR LOGICALAND RESTLOGICALOR
              ;

LOGICALAND : BITWISEOR RESTLOGICALAND
           ;

RESTLOGICALAND : 
               | OP_LOGICAL_AND BITWISEOR RESTLOGICALAND
               ;

BITWISEOR : BITWISEXOR RESTBITWISEOR
          ;

RESTBITWISEOR : 
              | '|' BITWISEXOR RESTBITWISEOR
              ;

BITWISEXOR : BITWISEAND RESTBITWISEXOR
           ;

RESTBITWISEXOR : 
               | '^' BITWISEAND RESTBITWISEXOR
               ;

BITWISEAND : EQUALITY RESTBITWISEAND
           ;

RESTBITWISEAND : 
               | '&' EQUALITY RESTBITWISEAND
               ;

EQUALITY : RELATION RESTEQUALITY
         ;

RESTEQUALITY : 
             | EQUALITYOPERATOR RELATION RESTEQUALITY
             ;

EQUALITYOPERATOR : OP_EQUAL
                 | OP_NOTEQUAL
                 ;

RELATION : SHIFT RESTRELATION
         ;

RESTRELATION : 
             | RELATIONOPERATOR SHIFT RESTRELATION
             ;

RELATIONOPERATOR : '<'
                 | OP_LESSEQUAL
                 | '>'
                 | OP_GREATEREQUAL
                 ;

SHIFT : ADDITION RESTSHIFT
      ;

RESTSHIFT : 
          | SHIFTOPERATOR ADDITION RESTSHIFT
          ;

SHIFTOPERATOR : OP_BITWISE_LSHIFT
              | OP_BITWISE_RSHIFT
              ;

ADDITION : MULTIPLICATION RESTADDITION
         ;

RESTADDITION : 
             | ADDITIONOPERATOR MULTIPLICATION RESTADDITION
             ;

ADDITIONOPERATOR : '+'
                 | '-'
                 ;

MULTIPLICATION : UNARY3 RESTMULTIPLICATION
               ;

RESTMULTIPLICATION : 
                   | MULTIPLICATIONOPERATOR UNARY3 RESTMULTIPLICATION
                   ;

MULTIPLICATIONOPERATOR : '*'
                       | '/'
                       | '%'
                       ;

UNARY3 : UNARY2
       | '&' UNARY2
       | '*' UNARY2
       ;

UNARY2 : FACTOR
       | '+' FACTOR
       | '-' FACTOR
       | '!' FACTOR
       ;

FACTOR : IDENTIFIER APPLICATION
       | IMMEDIATE
       | '(' EXPRESSION ')'
       ;

APPLICATION :
            | '[' EXPRESSION ']' APPLICATION
            | '(' EXPRESSION MOREEXPRESSION ')'
            ;

MOREEXPRESSION : 
               | ',' EXPRESSION MOREEXPRESSION
               ;

TYPE : KW_BOOL
     | KW_CHAR
     | KW_FLOAT
     | KW_INT
     ;

IMMEDIATE : KW_TRUE
          | KW_FALSE
          | CHAR
          | FLOAT
          | INT
          ;

%%

Symbol * addSymbol(char* nome){
       printf("NOME = %s\n", nome);
       Symbol *s;
       s = (Symbol *) malloc (sizeof(Symbol));
       s->name = (char *) malloc(strlen(nome)+1);
       strcpy(s->name, nome);
       s->nextSymbol = (struct Symbol *) sym_table;
       sym_table = s;
       return s;
}

Symbol * findSymbol(char * nome){
       Symbol * s;
       for(s = sym_table; s != (Symbol *) 0; s = (Symbol *) s->nextSymbol){
              if(strcmp(s->name, nome) == 0){
                     return s;
              }
       }
       return 0;
}

void install(char * nome){
       Symbol * s;
       s = findSymbol(nome);
       if(s == 0){
              s = addSymbol(nome);
       } else{
              printf("%s já foi declarado\n", nome);
       }
}

void context_check(char *nome){
       if(findSymbol(nome) == 0){
              printf("%s é um identificador não declaravel\n", nome);
       }
}


void yyerror(char *s){
       fprintf(stderr, "%s\n", s);
}

int main(){
       //TreeScope * root;
       //yydebug =  1;
       yyparse();
       return 0;
}