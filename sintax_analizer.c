#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

extern int yylex();
extern int yylineno;
extern int col;

int expression_parser(int &, int &);
int block_parser (int &, int &);
int declarationblock_parser(int &, int &);
int reference_parser(int&, int&);
int initializer_parser(int&, int&);
int check_expression_follow(int&, int&);
int check_expression_first(int&, int&);


int is_eqoperator(int x)
{
    return x == OP_EQUAL || x == OP_NOTEQUAL;
}

int is_rel(int x)
{
    return x == OP_GREATER ||
           x == OP_GREATEREQUAL ||
           x == OP_LESS ||
           x == OP_LESSEQUAL;
}

int is_add_operator(int x)
{
    return x == OP_ADD || x == OP_SUBTRACT;
}

int is_multiplication(int x)
{
    return x == OP_MULTIPLY ||
           x == OP_DIVIDE ||
           x == OP_MODULUS;
}

int immediate(int& next, int& error) {
    switch(next){
        case INT:
        case HEX:
        case BIN:
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case STRING:
        case FLOAT:
           next = yylex();
           break;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
    }
    check_expression_follow(next,error);
    return 0;
}

int more_expression(int &next, int &error) {
    switch(next) {
        case COMMA:
            next = yylex();
            expression_parser(next, error);
            more_expression(next, error);
            break;
        case RPAREN:
            break;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
    }
    return 0;
}

int application_parser(int &next, int &error) {
    switch(next) {
        case LBRACKET:
            next = yylex();
            expression_parser(next, error);
            if (next != RBRACKET) {
                printf("at line: %d col: %d expected ']'\n", yylineno, col);
                error++;
            }
            next = yylex();
            application_parser(next, error);
            break;
        case LPAREN:
            next = yylex();
            expression_parser(next, error);
            more_expression(next, error);
            if (next != RPAREN) {
                error++;
                printf("at line: %d col: %d expected ')'\n", yylineno, col);
            }
            next = yylex();
        default:
            if (check_expression_follow(next, error)) {
                return 0;
            }
            else {
                printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
            }
    }
    return 0;
}

int factor(int &next, int &error)
{
    switch(next) {
        case IDENTIFIER:
            next = yylex();
            application_parser(next,error);
            break;
        case LPAREN:
            next = yylex();
            expression_parser(next,error);
            if (next != RPAREN) {
                printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
            }
            next = yylex();
            break;
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case FLOAT:
        case INT:
        case STRING:
            immediate(next, error);
            break;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
            break;
    }
    return 0;
}

int unary2(
           int &next,
           int &error)
{

    switch (next)
    {
    case IDENTIFIER:
    case LPAREN:
    case KW_TRUE:
    case KW_FALSE:
    case CHAR:
    case FLOAT:
    case INT:
    case STRING:      // +=
        factor(next,error);
        break;
    case OP_ADD:
    case OP_SUBTRACT: //
    case OP_NOT:
        next = yylex();
        factor(next, error);
        break;
    default:
        printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
        break;
    }
    check_expression_follow(next,error);
    return 0;
}

int unary3(int &next, int &error)
{

    switch (next)
    {
    case OP_BITWISE_AND: //enderço de memoria
    case OP_MULTIPLY:    //derreferenciar pointer
    case OP_SUBTRACT:    // menos unario
        next = yylex();
        unary2(next, error);
        break;
    default:
        if(check_expression_first(next, error)) {
            unary2(next, error);
        } else {
            printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
        }
    }
    return 0;
}

int rest_multiplication(int &next,int &error) {
    if (is_multiplication(next))
    {
        next = yylex();
        unary3(next, error);
        rest_multiplication(next, error);
    }
    return 0;
}

int multiplication(int &next, int &error) {
    if (check_expression_first(next, error)) {
        unary3(next, error);
        rest_multiplication(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int rest_addition(int &next, int &error) {
    if (is_add_operator(next))
    {
        next = yylex();
        multiplication(next, error);
        rest_addition(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int addition(int &next,int &error) {
    if (check_expression_first) {
        multiplication(next, error);
        rest_addition(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int rest_shift(int &next, int &error)
{
    if (next == OP_BITWISE_LSHIFT || next == OP_BITWISE_RSHIFT)
    {
        next = yylex();
        addition(next, error);
        rest_shift(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int shift(int &next, int &error)
{
    if(check_expression_first(next,error)) {
        addition(next, error);
        rest_shift(next, error);
    }
    check_expression_follow(next, error);
    return 0;
}

int rest_relation(int &next, int &error) {
    if (is_rel(next))
    {
        next = yylex();
        shift(next, error);
        rest_relation(next, error);
    }
    check_expression_follow(next, error);
    return 0;
}

int relation(int &next, int &error)
{

    if(check_expression_first(next, error)) {
        shift(next, error);
        rest_relation(next, error);
    }
    return 0;
}

int rest_equality(
                  int &next,
                  int &error)
{
    if (is_eqoperator(next))
    {
        next = yylex();
        relation(next, error);
        rest_equality(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int equality(int &next, int &error)
{
    if(check_expression_first(next,error)) {
        relation(next, error);
        rest_equality(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int rest_bitwise_and(int &next, int &error) {
    if (next == OP_BITWISE_AND)
    {
        next = yylex();
        equality(next, error);
        rest_bitwise_and(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int bitwise_and(int &next, int &error) {
    if(check_expression_first(next,error)) {
        equality(next, error);
        rest_bitwise_and(next, error);
    }
    check_expression_follow(next, error);
    return 0;
}

int rest_bitwise_xor(
                     int &next,
                     int &error)
{
    if (next == OP_BITWISE_XOR)
    {
        next = yylex();
        bitwise_and(next, error);
        rest_bitwise_xor(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int bitwise_xor(int &next,
                int &error)
{
    if(check_expression_first(next, error)) {
        bitwise_and(next, error);
        rest_bitwise_xor(next, error);
    }
    check_expression_follow(next,error);
    return 0;
}

int rest_bitwise_or(
                    int &next,
                    int &error)
{
    if (next == OP_BITWISE_OR)
    {
        next = yylex();
        bitwise_xor(next, error);
        rest_bitwise_or(next, error);
    }
    check_expression_follow(next, error);
    return 0;
}

int bitwise_or(
               int &next,
               int &error)
{
    if(check_expression_first(next, error)) {
        bitwise_xor(next, error);
        rest_bitwise_or(next, error);
    }
    check_expression_follow(next, error);
    return 0;
}

int rest_logical_and(
                     int &next,
                     int &error)
{
    if (next == OP_LOGICAL_AND)
    {
        next = yylex();
        bitwise_or(next, error);
        rest_logical_and(next, error);
    }
    return 0;
}

int logical_and(int &next,
                int &error)
{
    if(check_expression_first(next, error)) {
        bitwise_or(next, error);
        rest_logical_and(next, error);
    }
    if(check_expression_follow(next, error)) return 0;
    return 0;
}

int rest_logical_or(int &next,
                    int &error)
{

    if (next == OP_LOGICAL_OR)
    {
        next = yylex();
        logical_and(next, error);
        rest_logical_or(next, error);
    }
    if(check_expression_follow(next, error)) return 0;
    return 0;
}

int check_expression_first(int &next, int &error) {
    switch(next) {
        case OP_BITWISE_AND:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
        case IDENTIFIER:
        case LPAREN:
        case OP_ADD:
        case OP_NOT:
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case FLOAT:
        case INT:
        case STRING:
            return true;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
            return false;
    }
}
int check_expression_follow(int &next,int &error) {
    switch(next) {
        case RPAREN:
        case SEMICOLON:
        case COMMA:
        case RBRACKET:
        case OP_ASSIGN:
        case OP_LOGICAL_OR:
        case OP_LOGICAL_AND:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
        case OP_BITWISE_AND:
        case OP_EQUAL:
        case OP_NOTEQUAL:
        case OP_LESS:
        case OP_LESSEQUAL:
        case OP_GREATER:
        case OP_GREATEREQUAL:
        case OP_BITWISE_LSHIFT:
        case OP_BITWISE_RSHIFT:
        case OP_ADD:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_MODULUS:
            return true;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
            return false;
    }
}

int logical_or(int &next,
               int &error)
{
    switch(next) {
        case OP_BITWISE_AND:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
        case IDENTIFIER:
        case LPAREN:
        case OP_ADD:
        case OP_NOT:
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case FLOAT:
        case INT:
        case STRING:
            logical_and(next, error);
            rest_logical_or(next, error);
            break;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
    }
    if(check_expression_follow(next,error)) return 0;
    else {
        printf("at line:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
    }
    return 0;
}

int rest_expression(int &next, int &error) {
    switch(next) {
        case OP_ASSIGN:
            next = yylex();
            logical_or(next, error);
            rest_expression(next, error);
            break;
        case RPAREN:
        case SEMICOLON:
        case COMMA:
        case RBRACKET:
        case OP_LOGICAL_OR:
        case OP_LOGICAL_AND:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
        case OP_BITWISE_AND:
        case OP_EQUAL:
        case OP_NOTEQUAL:
        case OP_LESS:
        case OP_LESSEQUAL:
        case OP_GREATER:
        case OP_GREATEREQUAL:
        case OP_BITWISE_LSHIFT:
        case OP_BITWISE_RSHIFT:
        case OP_ADD:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_MODULUS:
            return 0;
        default:
            printf("at line1:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
                return 0;
    }
    return 0;
}

int expression_parser( int &next, int &error) {
    switch(next) {
        case OP_BITWISE_AND:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
        case IDENTIFIER:
        case LPAREN:
        case OP_ADD:
        case OP_NOT:
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case FLOAT:
        case INT:
        case STRING:
            logical_or(next, error);
            rest_expression(next, error);
            break;
        default:
            printf("at line1:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
    }
    switch(next) {
        case RPAREN:
        case SEMICOLON:
        case COMMA:
        case RBRACKET:
        case OP_ASSIGN:
        case OP_LOGICAL_OR:
        case OP_LOGICAL_AND:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
        case OP_BITWISE_AND:
        case OP_EQUAL:
        case OP_NOTEQUAL:
        case OP_LESS:
        case OP_LESSEQUAL:
        case OP_GREATER:
        case OP_GREATEREQUAL:
        case OP_BITWISE_LSHIFT:
        case OP_BITWISE_RSHIFT:
        case OP_ADD:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_MODULUS:
            return 0;
        default:
            printf("at line1:%d, col:%d unexpected char %d\n"
                    ,yylineno, col, next);
    }
    
    return 0;
}

int index_block_parser(int&next, int& error) {
    switch(next){
        case LBRACKET:
            next = yylex();
            if (next == INT) {
                next = yylex();
            } else{
                printf(" at line: %d, col: %d expected interger", yylineno, col);
                return 0;
            }
            if (next == RBRACKET) {
                next = yylex();
            } else {
                printf(" at line: %d, col: %d expected ]", yylineno, col);
                return 0;
            }
            index_block_parser(next, error);
            return 0;
        case SEMICOLON:
        case COMMA:
        case OP_ASSIGN:
            return 0;
        default:
            printf("at line: %d, col: %d expected either ';', ',' or '=' but found none\n", yylineno, col);
            return 0;
    }
}

int declaration_parser( int &next, int &error)
{
    reference_parser(next, error);
    switch (next)
    {
    case IDENTIFIER:
        next = yylex();
        index_block_parser(next, error);
        initializer_parser(next, error);
        break;
    default:
        printf("at line: %d, col: %d expected identifier\n"
                ,yylineno, col);
    }
    switch(next){
        case SEMICOLON:
        case COMMA:
            return 0;
        default:
            printf("at line1: %d, col: %d expected ';' got %d\n"
                ,yylineno, col, next);
    }
    return 0;
}

int type_parser(int & next)
{
    switch(next) {
        case KW_INT :
        case KW_BOOL :
        case KW_FLOAT :
        case KW_CHAR :
        case KW_UNTYPED:
            next = yylex();
            break;
        default:
            printf("at line: %d, col: %d expected type\n",yylineno, col);
            break;
    }
    return 0;
}



int initializer_parser(int &next, int &error)
{
    if (next == OP_ASSIGN)
    {
        next = yylex();
        expression_parser(next, error);
    } else {
        switch(next) {
            case SEMICOLON:
            case COMMA:
                return 0;
            default:
                printf("at line2: %d, col:%d expected ';' or ','\n", 
                        yylineno, col);
        }
    }

    return 0;
}

int nextblock_parser( int &next, int &error)
{
    if (next == LBRACKET)
    {
        next = yylex();

        if (next == INT)
        {
            next = yylex();
            if (next != RBRACKET)
            {
                error++;
                printf(" at line: %d, col: %d RBRACKET not found\n",yylineno, col);
                return 1;
            }

            nextblock_parser(next, error);
        }
        else
        {
            error++;
            printf(" at line: %d, col: %d RBRACKET not found\n",yylineno, col);
            return 1;
        }
    }
    return 0;
}

int restdeclaration_parser( int &next, int &error)
{
    if (next == COMMA)
    {
        next = yylex();
        declaration_parser(next, error);
        restdeclaration_parser(next, error);
    } else if (next == SEMICOLON) {
        return 0;
    } else {
        printf("at line3: %d, col: %d expected ';'\n"
            ,yylineno, col);
    }
    return 0;
}

int declarationblock_parser( int &next, int &error)
{
    switch(next) {
        case KW_BOOL:
        case KW_CHAR:
        case KW_FLOAT:
        case KW_INT:
        case KW_UNTYPED:
            next = yylex();
            declaration_parser(next, error);
            restdeclaration_parser(next, error);
            break;
        default:
            printf("at line: %d, col: %d expected type keyword\n"
                ,yylineno, col);
    }
    if (next != SEMICOLON) {
        printf("at line4: %d, col: %d expected ';'\n"
            ,yylineno, col);
    }
    next = yylex();
    return 0;
}

int switchcases_parser( int &next, int &error) {
    if (next == KW_DEFAULT) return 0;
    if (next == KW_CASE)
    {
        next = yylex();
        if(next != INT){
            error++;
            printf(" at line: %d, col: %d INT not found\n",yylineno, col);
            return 1;
        }
        block_parser(next, error);
        switchcases_parser(next, error);
    }
    else {
        printf("tu errou nesse switch macho\n");
    }

    return 0;
}

int function_elseBlock_parser( int &next, int &error)
{
    if (next == KW_ELSE)
    {
        next = yylex();
        block_parser(next, error);
    }

    return 0;
}

int statement_parser( int &next, int &error)
{
    switch (next) {
    case KW_LABEL:
        next = yylex();
        if (next != IDENTIFIER)
        {
            error++;
            printf("at line: %d, col: %d expected identifier\n",yylineno, col);
            return 1;
        }
        next = yylex();
        if (next != SEMICOLON)
        {
            error++;
            printf(" at line: %d, col: %d SEMICOLON not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        break;
    case SEMICOLON:
        next = yylex();
        break;
    case KW_BREAK:
    case KW_CONTINUE:
        next = yylex();;
        if (next != SEMICOLON)
        {
            error++;
            printf(" at line: %d, col: %d SEMICOLON not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        break;
    case KW_IF:
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf(" at line: %d, col: %d expected '(' not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf(" at line: %d, col: %d expected ')' not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        block_parser(next, error);
        function_elseBlock_parser(next, error);
        break;
    case KW_GOTO:
        next = yylex();
        if (next != IDENTIFIER)
        {
            error++;
            printf(" at line: %d, col: %d IDENTIFIER not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        if (next != SEMICOLON)
        {
            error++;
            printf(" at line: %d, col: %d SEMICOLON not found\n",yylineno, col);
            return 1;
        }
        break;
    case KW_WHILE:
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf(" at line: %d, col: %d LPARAN not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf(" at line: %d, col: %d RPARAN not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        if (next != DO)
        {
            error++;
            printf(" at line: %d, col: %d DO not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        block_parser(next, error);
        break;
    case DO:
        next = yylex();
        block_parser(next, error);
        if (next != KW_WHILE)
        {
            error++;
            printf(" at line: %d, col: %d WHILE not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf(" at line: %d, col: %d LPARAN not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf(" at line: %d, col: %d RPARAN not found\n",yylineno, col);
            return 1;
        }
        if (next != SEMICOLON){
            error++;
            printf(" at line: %d, col: %d ';'\n", yylineno, col);
        }
        next = yylex();
        break;
    case KW_SWITCH:
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf(" at line: %d, col: %d LPARAN not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf(" at line: %d, col: %d RPARAN not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        if (next != LBRACE)
        {
            error++;
            printf(" at line: %d, col: %d LBRACE not found\n",yylineno, col);
            return 1;
        }
        switchcases_parser(next, error);
        if (next != KW_DEFAULT)
        {
            error++;
            printf(" at line: %d, col: %d KW_DEFAULT not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        block_parser(next, error);
        if (next != RBRACE)
        {
            error++;
            printf(" at line: %d, col: %d RBRACE not found\n",yylineno, col);
            return 1;
        }
        break;
    case KW_RETURN:
        next = yylex();
        expression_parser(next, error);
        if (next != SEMICOLON)
        {
            error++;
            printf("at line: %d, col: %d SEMICOLON after expression not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        break;
    case KW_BOOL:
    case KW_CHAR:
    case KW_FLOAT:
    case KW_INT:
    case KW_UNTYPED:
        declarationblock_parser(next,error);
        break;
    case OP_BITWISE_AND:
    case OP_MULTIPLY:
    case OP_SUBTRACT:
    case IDENTIFIER:
    case LPAREN:
    case OP_ADD:
    case OP_NOT:
    case KW_TRUE:
    case KW_FALSE:
    case CHAR:
    case FLOAT:
    case INT:
    case STRING:
        expression_parser(next, error);
        break;
    default:
        printf("nao devia ter metido essa\n");
    }
    return 0;
}

int code_parser( int &next, int &error)
{
    switch(next) {
        case RBRACE:
            return 0;
        case LBRACE:
            block_parser(next, error);
            code_parser(next, error);
            break;
        case KW_LABEL:
        case SEMICOLON:
        case KW_BREAK:
        case KW_CONTINUE:
        case KW_IF:
        case KW_GOTO:
        case KW_WHILE:
        case DO:
        case KW_SWITCH:
        case KW_RETURN:
        case KW_BOOL:
        case KW_CHAR:
        case KW_FLOAT:
        case KW_INT:
        case KW_UNTYPED:
        case OP_BITWISE_AND:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
        case IDENTIFIER:
        case LPAREN:
        case OP_ADD:
        case OP_NOT:
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case FLOAT:
        case INT:
        case STRING:
            statement_parser(next, error);
            code_parser(next, error);
            break;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
    }
    switch(next) {
        case RBRACE:
            return 0;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
    }

    return 0;
}

int block_parser( int &next, int &error)
{
    if (next == LBRACE)
    {
        next = yylex();

        code_parser(next, error);

        if (next == RBRACE)
        {
            next = yylex();
        }
        return 0;
    }
    switch(next) {
        case EOI:
        case KW_EXTERN:
        case KW_BOOL:
        case KW_CHAR:
        case KW_FLOAT:
        case KW_INT:
        case KW_UNTYPED:
        case KW_START:
        case IDENTIFIER:
        case SEMICOLON:
        case LBRACE:
        case RBRACE:
        case KW_LABEL:
        case KW_BREAK:
        case KW_CONTINUE:
        case KW_IF:
        case KW_GOTO:
        case KW_WHILE:
        case DO:
        case KW_SWITCH:
        case KW_RETURN:
        case OP_BITWISE_AND:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
        case LPAREN:
        case OP_ADD:
        case OP_NOT:
        case KW_TRUE:
        case KW_FALSE:
        case CHAR:
        case FLOAT:
        case INT:
        case STRING:
        case KW_ELSE:
        case KW_DEFAULT:
            return 0;
        default:
            printf("f\n");
            return 0;
    }
}

int dimensionblock_parser( int &next, int &error)
{
    if (next == LBRACKET)
    {
        next = yylex();
        if (next == RBRACKET)
        {
            next = yylex();
            dimensionblock_parser(next, error);
            return 0;
        }
        else
        {
            printf("at line:%d, col:%d expected ']'\n"
            ,yylineno, col);
            error++;
            return 1;
        }
    }
    switch(next) {
        case ARROW:
        case COMMA:
        case SEMICOLON:
        case LBRACE:
            return 0;
        default:
            printf("at line:%d, col:%d unexpected char %d\n"
                ,yylineno, col, next);
            return 0;
    }

    return 0;
}

int reference_parser( int &next, int &error)
{
    switch (next)
    {
        case OP_MULTIPLY:
            next = yylex();
            reference_parser(next, error);
        case IDENTIFIER:
        case SEMICOLON:
        case LBRACE:
        case LBRACKET:
            return 0;
            
    }

    return 0;
}

int function_returntype_parser( int &next, int &error)
{
    switch (next)
    {
    case KW_VOID:
    case KW_BOOL:
    case KW_CHAR:
    case KW_FLOAT:
    case KW_INT:
    case KW_UNTYPED:
        next = yylex();
        reference_parser(next, error);
        dimensionblock_parser(next, error);
        break;
    default:
        printf("at line: %d, col: %d expected return type\n",yylineno, col);
        break;
    }
    switch(next) {
        case SEMICOLON:
        case LBRACE:
            return 0;
        default:
            printf("at line5: %d, col: %d expected ';' or '{'\n",yylineno, col);

    }
    return 0;
}

int function_param_parser( int &next, int &error)
{
    switch(next) {
        case OP_MULTIPLY:
        case IDENTIFIER:
            reference_parser(next, error);
            if (next != IDENTIFIER) {
                printf("at line: %d, col: %d unexpected %d\n",
                    yylineno, col, next);
            }
            next = yylex();
            dimensionblock_parser(next, error);
            break;
        default:
            printf("at line: %d, col1: %d unexpected %d\n",
                    yylineno, col, next);
    }
    switch(next) {
        case ARROW:
        case SEMICOLON:
        case COMMA:
            return 0;
        default:
            printf("at line: %d, col2: %d expected arrow or ';' or ','\n"
            ,yylineno, col);
            return 0;
    }
    return 0;
}

int function_moreparam( int &next, int &error)
{
    switch(next) {
        case SEMICOLON:
        case ARROW:
            return 0;
            break;
        case COMMA:
            next = yylex();
            function_param_parser(next, error);
            function_moreparam(next, error);
            break;
        default:
            printf("at line: %d, col: %d expected ','\n"
            ,yylineno, col);
    }
    switch(next) {
        case SEMICOLON:
        case ARROW:
            return 0;
        default:
            printf("at line6: %d, col: %d expected ';' or '->'\n"
            ,yylineno, col);
    }
    return 0;
}


int function_paramblock_parser(int &next, int &error)
{
    switch (next){
        case KW_BOOL:
        case KW_CHAR:
        case KW_FLOAT:
        case KW_INT:
        case KW_UNTYPED:
            next = yylex();
            function_param_parser(next, error);
            function_moreparam(next,error);
            break;
        default:
            printf("at line: %d, col: %d unexpected %d\n"
            ,yylineno, col, next);
            break;
    }
    switch(next) {
        case ARROW:
        case SEMICOLON:
            return 0;
            break;
        default:
            printf("at lin1e: %d, col: %d unexpected %d\n"
            ,yylineno, col, next);
    }
    return 0;
}
int function_moreparamblock_parser( int &next, int &error)
{
    switch (next) {
        case SEMICOLON:
            next = yylex();
            function_paramblock_parser(next, error);
            function_moreparamblock_parser(next, error);
            return 0;
        case ARROW:
            return 0;
        default:
            printf("at line7: %d, col: %d expected ';'\n",yylineno, col);
    }
    return 0;
}


int function_paramlist_parser( int &next, int &error)
{
    switch (next) {
    case KW_VOID:
        next = yylex();
        break;
    case KW_BOOL:
    case KW_CHAR:
    case KW_FLOAT:
    case KW_INT:
    case KW_UNTYPED:
        function_paramblock_parser(next, error);
        function_moreparamblock_parser(next, error);
        break;
    default:
        printf("at line:%d, col:%d expected type\n"
            ,yylineno, col);
    }
    switch (next) {
        case ARROW:
            return 0;
        default:
            printf("at line:%d, col:%d expected '->'\n"
            ,yylineno, col);
    }
    return 0;
}

int function_modifiers_parser( int &next, int &error)
{
    switch (next)
    {
    case KW_START:
        next = yylex();
        break;
    default:
        break;
    }
    switch(next) {
        case IDENTIFIER:
            return 0;
        default:
            printf("at line:%d, col:%d expected fucntion name\n",yylineno, col);
    }

    return 0;
}

int function_rest_parser( int &next, int &error)
{
    switch (next)
    {
        case SEMICOLON:
            next = yylex();
            break;
        case LBRACE:
            block_parser(next, error);
            return 0;
        default:
            printf("at line:%d, col:%d unexpected  %d\n",
            yylineno, col, next);
    }
    switch(next) {
        case EOI:
        case KW_EXTERN:
        case KW_BOOL:
        case KW_CHAR:
        case KW_FLOAT:
        case KW_INT:
        case KW_UNTYPED:
        case KW_START:
        case IDENTIFIER:
        case SEMICOLON:
        case LBRACE:
            return 0;
        default:
            printf("at line:%d, col:%d unexpected  %d\n",
            yylineno, col, next);
    }
    return 0;
}

int function_header_parser( int &next, int &error)
{
    switch(next) {
        case KW_START:
        case IDENTIFIER:
            function_modifiers_parser(next, error);

            if (next != IDENTIFIER)
            {
                printf(" at line: %d, col: %d IDENTIFIER not exists\n",yylineno, col);
                return 0;
            }

            next = yylex();

            if (next != COLON)
            {
                printf(" at line: %d, col: %d COLON not exists\n",yylineno, col);
                error++;
                return 1;
            }

            next = yylex();
            switch(next){
                case KW_VOID:
                case KW_BOOL:
                case KW_CHAR:
                case KW_FLOAT:
                case KW_INT:
                case KW_UNTYPED:
                    function_paramlist_parser(next, error);
                    break;
                default:
                    printf("at line: %d, col: %d expected parameters\n",yylineno, col);
            }

            if (next != ARROW)
            {
                printf("at line: %d, col: %d ARROW not exists\n",yylineno, col);
                error++;
                return 1;
            }
            next = yylex();
            function_returntype_parser(next, error);
    }
    
    switch(next) {
        case SEMICOLON:
        case LBRACE:
            break;
        default:
            printf("at line8: %d, col: %d expected ';' or '{'\n",yylineno, col);
    }

    return 0;
}

int function_parser( int &next, int &error)
{
    switch(next) {
        case KW_START:
        case IDENTIFIER:
        case SEMICOLON:
        case LBRACE:
            function_header_parser(next, error);
            function_rest_parser(next, error);
            return 0;
        default:
            printf("at line9: %d, col: %d expected ';' or '{'\n",yylineno, col);
            return 0;
    }

    return 0;
}


int global_parser(int& next, int &error)
{
    switch (next)
    {
    case KW_BOOL:
    case KW_CHAR:
    case KW_FLOAT:
    case KW_INT:
    case KW_UNTYPED:
        declarationblock_parser(next, error);
        break;
    case KW_START:
    case IDENTIFIER:
        function_parser(next, error);
        break;
    default:
        printf("at line: %d, col: %d expected type or idetifier but got %d\n", yylineno, col, next);
    }
    switch(next) {
        case EOI:
        case KW_EXTERN:
        case KW_BOOL:
        case KW_CHAR:
        case KW_FLOAT:
        case KW_INT:
        case KW_UNTYPED:
        case KW_START:
        case IDENTIFIER:
        case SEMICOLON:
        case LBRACE:
            return 0;
        default:
            printf("at line:%d, col:%d unexpected entry %d\n"
            ,yylineno, col, next);
    }
    return 0;
}

int globals_parser(int& next, int& error)
{
    if (next == EOI) // EOI = end of input
        return 0;
    switch (next)
    {
    case KW_EXTERN:
        next = yylex();
        global_parser(next,error);
        globals_parser(next,error);
        return 0;;
    case KW_BOOL:
    case KW_CHAR:
    case KW_FLOAT:
    case KW_INT:
    case KW_UNTYPED:
    case KW_START:
    case IDENTIFIER:
    case SEMICOLON:
    case LBRACE:
        global_parser(next,error);
        globals_parser(next,error);
        break;
    default:
        printf("at line: %d, col: %d unexpected char %d\n", yylineno, col, next);
        break;
    }
    switch(next) {
        case EOI:
            return 0;
        default:
            printf("at line: %d, col: %d unexpected char %d\n", yylineno, col, next);
    }
    return 0;
}

int module_parser(int& next, int& error)
{
    switch (next)
    {
    case KW_MODULE:
        {
            int identi = yylex();
            int semicol = yylex();
            if (identi == IDENTIFIER && semicol == SEMICOLON)
            {
                next = yylex();
                globals_parser(next, error);
            }
            else {
                printf("at line: %d, col: %d expected module declaration\n",yylineno, col);
            }
            break;
        }
    default:
        printf("at line: %d, col: %d expected module declaration\n",yylineno, col);
    }
    switch(next) {
        case EOI:
            return 0;
        default:
            printf("at line: %d, col: %d unexpected char %d\n", yylineno, col, next);
    }
    return 0;
}

int main()
{
    int next = yylex(), error = 0;
    module_parser(next,error);
    return 0;
}