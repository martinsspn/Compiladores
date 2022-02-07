%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TREE.c"
//#define YYDEBUG 1
void yyerror(char *s);
int yylex();


Symbol * sym_table;
TreeScope * tree_table;
Symbol * addSymbol(char* nome, int param, int type, int isOperand);
Symbol * findSymbol(char * nome);
void installScope(char * nome);
void install(char *nome, int paramfunc, int type, int isOperand);
void context_check(char *nome);
void criarNovoSimbolo(TreeScope * ts, char * name, int type);

void check_type();
TreeScope * newScopeSibling(char* nome);
TreeScope * newScopeChild(char* nome);
%}
//%define parse.error verbose
%token KW_MODULE IDENTIFIER KW_EXTERN KW_VOID KW_START ARROW KW_LABEL KW_BREAK KW_CONTINUE KW_IF KW_GOTO KW_WHILE KW_SWITCH KW_DEFAULT KW_RETURN KW_ELSE KW_CASE KW_BOOL KW_CHAR KW_DO KW_FLOAT KW_INT KW_TRUE KW_FALSE INT FLOAT CHAR OP_LOGICAL_OR OP_LOGICAL_AND OP_BITWISE_RSHIFT OP_BITWISE_LSHIFT OP_EQUAL OP_NOTEQUAL OP_GREATEREQUAL OP_LESSEQUAL
%start PROG
%union {
       int itype;
       double dtype;
       char ctype;
       char* string;
       int type;
}
%%

PROG :        /* empty */     
       | KW_MODULE IDENTIFIER ';' GLOBALS { installScope( $<string>2 ); }
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

FUNCTIONHEADER : MODIFIERS IDENTIFIER ':' PARAMLIST ARROW RETURNTYPE { installScope($<string>2); }
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

PARAM : REFERENCE IDENTIFIER DIMENSIONBLOCK  { install( $<string>2, 1, $<itype>1, 0 ); }
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

STATEMENT : KW_LABEL IDENTIFIER ';' { install($<string>2, 0, 0, 0); }
          | ';'
          | KW_BREAK ';'
          | KW_CONTINUE ';'
          | KW_IF '(' EXPRESSION ')' BLOCK elseBLOCK
          | KW_GOTO IDENTIFIER ';' { install($<string>2,0, 0, 0); }
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

DECLARATIONBLOCK : TYPE DECLARATION RESTDECLARATION {install($<string>2, 0, $<type>1, 0); }
                 ;

DECLARATION : REFERENCE IDENTIFIER INDEXBLOCK INITIALIZER { $<string>$ = $<string>2;  }
            ;

RESTDECLARATION : 
                | ',' DECLARATION RESTDECLARATION
                ;

INDEXBLOCK :
           | '[' INT ']' INDEXBLOCK
           | '[' IDENTIFIER ']' INDEXBLOCK
           ;

INITIALIZER : { $<itype>$ = 0; }
            | '=' EXPRESSION { $<type>$ = $<type>2; $<itype>$ = $<itype>2; }
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

ADDITION : SUBTRACTION RESTADDITION { $<itype>$ = $<itype>1 + $<itype>2; }
         ;

RESTADDITION : { $<itype>$ = 0; }
             | '+' SUBTRACTION RESTADDITION { $<itype>$ = $<itype>2 + $<itype>3; install("+", 0, 0, 1); }
             ;

SUBTRACTION : MULTIPLICATION RESTSUBTRACTION { $<itype>$ = $<itype>1 - $<itype>2; }
            ;

RESTSUBTRACTION : { $<itype>$ = 0; }
                | '-' MULTIPLICATION RESTSUBTRACTION { $<itype>$ = $<itype>2 - $<itype>3; install("-", 0, 0, 1); }
                ;


MULTIPLICATION : DIVIDE RESTMULTIPLICATION { $<itype>$ = $<itype>1 * $<itype>2; }
               ;

RESTMULTIPLICATION : { $<itype>$ = 1; }
                   | '*' UNARY3 RESTMULTIPLICATION { $<itype>$ = $<itype>2 * $<itype>3; install("*", 0, 0, 1);}
                   ;


DIVIDE : UNARY3 RESTDIVIDE { $<itype>$ = $<itype>1 / $<itype>2; }
       ;

RESTDIVIDE: { $<itype>$ = 1; }
          | '/' UNARY3 RESTDIVIDE { $<itype>$ = $<itype>2 / $<itype>3; install("/", 0, 0, 1); }
          ;

UNARY3 : UNARY2
       | '&' UNARY2
       | '*' UNARY2
       ;

UNARY2 : FACTOR { $<itype>$ = $<itype>1; }
       | '+' FACTOR { $<itype>$ = $<itype>2; }
       | '-' FACTOR { $<itype>$ = (-1) * $<itype>2; }
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
     | KW_CHAR { $<type>$ = $<type>1; }
     | KW_FLOAT { $<type>$ = $<type>1; }
     | KW_INT { $<type>$ = $<type>1; }
     ;

IMMEDIATE : KW_TRUE
          | KW_FALSE
          | CHAR  { $<ctype>$ = $<ctype>1; }
          | FLOAT { $<dtype>$ = $<dtype>1; }
          | INT { $<itype>$ = $<itype>1; }
          ;

%%

TreeScope * newScopeSibling(char* nome){
       TreeScope * ts;
       ts = (TreeScope *) malloc (sizeof(TreeScope));
       ts->name = (char *) malloc(strlen(nome)+1);
       strcpy(ts->name, nome);
       ts->nextSiblingScope = (struct TreeScope *) tree_table;
       tree_table = ts;
       sym_table = ts->symbols;
       return ts;
}

TreeScope * newScopeChild(char* nome){
       TreeScope * ts;
       ts = (TreeScope *) malloc (sizeof(TreeScope));
       ts->name = (char *) malloc(strlen(nome)+1);
       strcpy(ts->name, nome);
       ts->symbols = sym_table;
       ts->firstChildScope = (struct TreeScope *) tree_table;
       tree_table = ts;
       Symbol *s;
       //s = (Symbol *) malloc (sizeof(Symbol));
       sym_table = s;
       return ts;
}

Symbol * addSymbol(char* nome, int param, int type, int isOperand){
       Symbol *s;
       s = (Symbol *) malloc (sizeof(Symbol));
       s->name = (char *) malloc(strlen(nome)+1);
       s->type = type;
       s->isOperand = isOperand;
       s->paramFunc = param;
       strcpy(s->name, nome);
       s->nextSymbol = (struct Symbol *) sym_table;
       sym_table = s;
       return s;
}

Symbol * findSymbol(char * nome){
       Symbol * s;
       for(s = sym_table; s != (Symbol *) 0; s = (Symbol *) s->nextSymbol){
              if(strcmp(s->name, nome) == 0 && s->paramFunc == 0 && s->isOperand == 0){
                     return s;
              }
       }
       return 0;
}

TreeScope * findScope(char *nome){
       TreeScope * ts;
       for(ts = tree_table; ts != (TreeScope *) 0; ts = (TreeScope *) ts->firstChildScope){
              if(strcmp(ts->name, nome) == 0){
                     return ts;
              }
       }
       return 0;
}

void installScope(char * nome){
       TreeScope * ts;
       ts = findScope(nome);
       if(ts == 0){
              ts = newScopeChild(nome);
       } else{
              printf("Escopo já foi definido\n");
       }
}

void install(char * nome, int paramfunc, int type, int isOperand){
       Symbol * s;
       s = findSymbol(nome);
       if(s == 0){
              s = addSymbol(nome, paramfunc, type, isOperand);
       } else{
              printf("%s já foi declarado\n", nome);
       }
}

void context_check(char *nome){
       if(findSymbol(nome) == 0){
              printf("%s é um identificador não declaravel\n", nome);
       }
}

void check_type(){
       printf("Começou\n");
       TreeScope *ts;
       for(ts = tree_table; ts != (TreeScope *) 0; ts = (TreeScope *) ts->firstChildScope){
              printf("Percorrendo: %s\n", ts->name);
              if(ts->symbols == 0){
                     printf("É nulo\n");
              }
              Symbol * s;
              //s = ;
              for(s = ts->symbols; s != (Symbol *) 0; s = (Symbol *) s->nextSymbol){
                     printf("Simbolo: %s\n", s->name);
              }
       }
}

void yyerror(char *s){
       fprintf(stderr, "%s\n", s);
}

int main(){
       //TreeScope * root;
       //yydebug =  1;
       yyparse();
       check_type();
       return 0;
}