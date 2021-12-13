#ifndef SINTAX_ANALIZER
#define SINTAX_ANALIZER

#define KW_MODULE                300
#define KW_WHILE                 301
#define KW_EXTERN                302
#define KW_BREAK                 303
#define KW_CONTINUE              304
#define KW_IF                    305
#define KW_ELSE                  306
#define KW_FALSE                 307
#define KW_TRUE                  308
#define KW_SWITCH                309
#define KW_CASE                  310
#define KW_DEFAULT               311
#define KW_ OTO                  312
#define KW_LABEL                 313
#define KW_INT                   314
#define KW_BOOL                  315
#define KW_FLOAT                 316
#define KW_CHAR                  317
#define KW_UNTYPED               318
#define KW_VOID                  319
#define KW_RETURN                320
#define KW_START                 321
#define LPAREN                   322
#define RPAREN                   323
#define LBRACE                   324
#define RBRACE                   325
#define LBRACKET                 326
#define RBRACKET                 327
#define COMMA                    328
#define OP_ADD                   329
#define OP_SUBTRACT              330
#define OP_BITWISE_COMPLEMENT    331
#define OP_MULTIPLY              332
#define OP_DIVIDE                333
#define OP_MODULUS               334
#define OP_LESS                  335
#define OP_LESSEQUAL             336
#define OP_GREATER               337
#define OP_GREATEREQUAL          338
#define OP_EQUAL                 339
#define OP_NOTEQUAL              341
#define OP_LOGICAL_OR            342
#define OP_NOT                   343
#define OP_BITWISE_RSHIFT        344
#define OP_BITWISE_LSHIFT        345
#define OP_BITWISE_XOR           346
#define OP_LOGICAL_AND           347
#define OP_BITWISE_AND           348
#define SEMICOLON                349
#define COLON                    351
#define ARROW                    352
#define OP_ASSIGN                353
#define OP_BITWISE_OR            354
#define OP_TERNARY_IF            355
#define KW_IMPORT                356
#define HEX                      357
#define BIN                      358
#define INT                      359
#define CHAR                     360
#define STRING                   361
#define IDENTIFIER               362
#define DO                       363
#define GOTO                     364
#define EMPTY                    365
#define ERROR                    606
#define EOI                      0

#define T_BOOL                  200
#define T_CHAR                  201
#define T_FLOAT                 202
#define T_INT                   203
#define T_UNTYPE                204


#define NT_MODULE               500
#define NT_GLOBALS              501
#define NT_GLOBAL               502
#define NT_FUNCTION             503
#define NT_FUNCTIONHEADER       504
#define NT_FUNCTIONREST         505
#define NT_MODIFIERS            506
#define NT_PARAMLIST            507
#define NT_MOREPARAMBLOCK       508
#define NT_PARAMBLOCK           509
#define NT_MOREPARAM            510
#define NT_DECLARATIONBLOCK     511
#define NT_RETURNTYPE           512
#define NT_BLOCK                513
#define NT_TYPE                 514
#define NT_PARAM                515
#define NT_DIMENSIONBLOCK       516
#define NT_REFERENCE            517
#define NT_CODE                 518
#define NT_STATEMENT            519
#define NT_EXPRESSION           520
#define NT_elseBLOCK            521
#define NT_SWITCHCASES          522
#define NT_DECLARATION          523
#define NT_RESTDECLARATION      524

int yylex();
#endif