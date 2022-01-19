%{
    int yylex(void);
    void yyerror(char *s){ EM_error(EM_tokPos, "%s", s); }
%}
%token module identifier extern  void start  multi label break continue if goto while do switch default return else case assign bool char float int  untyped true false
%start PROG


%%
PROG : module identifier ';' GLOBALS

GLOBALS :  
        | GLOBAL GLOBALS
        | extern GLOBAL GLOBALS

GLOBAL : FUNCTION
       | DECLARATIONBLOCK ';'

FUNCTION : FUNCTIONHEADER FUNCTIONREST

FUNCTIONHEADER : MODIFIERS identifier ':' PARAMLIST '-''>' RETURNTYPE

FUNCTIONREST : ';'
             | BLOCK

MODIFIERS : 
          | start

PARAMLIST : void
          | PARAMBLOCK MOREPARAMBLOCK

PARAMBLOCK : TYPE PARAM MOREPARAM

MOREPARAMBLOCK : 
               | ';' PARAMBLOCK MOREPARAMBLOCK

MOREPARAM : 
          | ',' PARAM MOREPARAM

PARAM : REFERENCE identifier DIMENSIONBLOCK

RETURNTYPE : TYPE REFERENCE DIMENSIONBLOCK

REFERENCE :
          | '*' REFERENCE

DIMENSIONBLOCK : 
               | '['']' DIMENSIONBLOCK

BLOCK : '{' CODE '}'

CODE : 
     | BLOCK CODE
     | STATEMENT CODE

STATEMENT : label identifier ';'
          | ';'
          | break ';'
          | continue ';'
          | if '(' EXPRESSION ')' BLOCK elseBLOCK
          | goto identifier ';'
          | while '(' EXPRESSION ')' do BLOCK
          | do BLOCK while '(' EXPRESSION ')'
          | switch '(' EXPRESSION ')' '{' SWITCHCASES default BLOCK '}'
          | return EXPRESSION ';'
          | EXPRESSION ';'
          | DECLARATIONBLOCK ';'

elseBLOCK : 
          | else BLOCK

SWITCHCASES : 
            | case int BLOCK SWITCHCASES

DECLARATIONBLOCK : TYPE DECLARATION RESTDECLARATION

DECLARATION : REFERENCE identifier INDEXBLOCK INITIALIZER

RESTDECLARATION : 
                | ',' DECLARATION RESTDECLARATION

INDEXBLOCK :
           | '[' int ']' INDEXBLOCK

INITIALIZER : 
            | '=' EXPRESSION

EXPRESSION : LOGICALOR RESTEXPRESSION

RESTEXPRESSION : 
               | '=' LOGICALOR RESTEXPRESSION

LOGICALOR : LOGICALAND RESTLOGICALOR

RESTLOGICALOR : 
              | '|''|' LOGICALAND RESTLOGICALOR

LOGICALAND : BITWISEOR RESTLOGICALAND

RESTLOGICALAND : 
               | '&''&' BITWISEOR RESTLOGICALAND

BITWISEOR : BITWISEXOR RESTBITWISEOR

RESTBITWISEOR : 
              | '|' BITWISEXOR RESTBITWISEOR

BITWISEXOR : BITWISEAND RESTBITWISEXOR

RESTBITWISEXOR : 
               | '^' BITWISEAND RESTBITWISEXOR

BITWISEAND : EQUALITY RESTBITWISEAND

RESTBITWISEAND : 
               | '&' EQUALITY RESTBITWISEAND

EQUALITY : RELATION RESTEQUALITY

RESTEQUALITY : 
             | EQUALITYOPERATOR RELATION RESTEQUALITY

EQUALITYOPERATOR : '=''='
                 | '!''='

RELATION : SHIFT RESTRELATION

RESTRELATION : 
             | RELATIONOPERATOR SHIFT RESTRELATION

RELATIONOPERATOR : '<'
                 | '<''='
                 | '>'
                 | '>''='

SHIFT : ADDITION RESTSHIFT

RESTSHIFT : 
          | SHIFTOPERATOR ADDITION RESTSHIFT

SHIFTOPERATOR : '<''<'
              | '>''>'

ADDITION : MULTIPLICATION RESTADDITION

RESTADDITION : 
             | ADDITIONOPERATOR MULTIPLICATION RESTADDITION

ADDITIONOPERATOR : '+'
                 | '-'

MULTIPLICATION : UNARY3 RESTMULTIPLICATION

RESTMULTIPLICATION : 
                   | MULTIPLICATIONOPERATOR UNARY3 RESTMULTIPLICATION

MULTIPLICATIONOPERATOR : '*'
                       | '/'
                       | '%'

UNARY3 : UNARY2
       | UNARY3OPERATOR UNARY2

UNARY3OPERATOR : '&'
               | '*'
               | '-'

UNARY2 : FACTOR
       | UNARY2OPERATOR FACTOR

UNARY2OPERATOR : '+'
               | '-'
               | '!'

FACTOR : identifier APPLICATION
       | IMMEDIATE
       | '(' EXPRESSION ')'

APPLICATION :
            | '[' EXPRESSION ']' APPLICATION
            | '(' EXPRESSION MOREEXPRESSION ')'

MOREEXPRESSION : 
               | ',' EXPRESSION MOREEXPRESSION

TYPE : bool
     | char
     | float
     | int
     | untyped

IMMEDIATE : true
          | false