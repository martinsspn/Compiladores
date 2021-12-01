#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <algorithm>

extern int yylex();
extern int lineno;
extern int col;

int expression_parser(int &, int &);
int function_block_parser (int &, int &);
int function_declarationblock_parser(int &, int &){return 0;}
int function_statement_parser(int &, int &){return 0;}

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

int immediate(int x)
{
    return x == IDENTIFIER ||
           x == INT ||
           x == HEX ||
           x == BIN ||
           x == KW_TRUE ||
           x == KW_FALSE ||
           x == CHAR ||
           x == STRING;
}

int factor(
           int &next,
           int &error)
{
    if (next == LPAREN)
    {
        next = yylex();
        printf("hoy %d\n", next);
        expression_parser(next, error);
        if (next != RPAREN)
        {
            printf("missing close parenthesis\n");
            error++;
            return 0;
        }
        next = yylex();
    }
    else if (immediate(next))
    {
        next = yylex();
        return 0;
    }
    return 0;
}

int unary2(
           int &next,
           int &error)
{
    switch (next)
    {
    case OP_ADD:      // +=
    case OP_SUBTRACT: //
    case OP_NOT:
        next = yylex();
        factor(next, error);
        break;
    default:
        factor(next, error);
        break;
    }
    return 0;
}

int unary3(
           int &next,
           int &error)
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
        unary2(next, error);
    }
    return 0;
}

int rest_multiplication(
                        int &next,
                        int &error)
{
    if (is_multiplication(next))
    {
        next = yylex();
        unary3(next, error);
        rest_multiplication(next, error);
    }
    return 0;
}

int multiplication(
                   int &next,
                   int &error)
{
    unary3(next, error);
    rest_multiplication(next, error);
    return 0;
}

int rest_addition(
                  int &next,
                  int &error)
{
    if (is_add_operator(next))
    {
        next = yylex();
        multiplication(next, error);
        rest_addition(next, error);
    }
    return 0;
}

int addition(
             int &next,
             int &error)
{
    multiplication(next, error);
    rest_addition(next, error);
    return 0;
}

int rest_shift(
               int &next,
               int &error)
{
    if (next == OP_BITWISE_LSHIFT || next == OP_BITWISE_RSHIFT)
    {
        next = yylex();
        addition(next, error);
        rest_shift(next, error);
    }
    return 0;
}

int shift(
          int &next,
          int &error)
{
    addition(next, error);
    rest_shift(next, error);
    return 0;
}

int rest_relation(
                  int &next,
                  int &error)
{
    if (is_rel(next))
    {
        next = yylex();
        shift(next, error);
        rest_relation(next, error);
    }
    return 0;
}

int relation(
             int &next,
             int &error)
{
    shift(next, error);
    rest_relation(next, error);
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
    return 0;
}

int equality(
             int &next,
             int &error)
{

    relation(next, error);
    rest_equality(next, error);
    return 0;
}

int rest_bitwise_and(
                     int &next,
                     int &error)
{
    if (next == OP_BITWISE_AND)
    {
        next = yylex();
        equality(next, error);
        rest_bitwise_and(next, error);
    }
    return 0;
}

int bitwise_and(
                int &next,
                int &error)
{
    equality(next, error);
    rest_bitwise_and(next, error);
    return 0;
}

int rest_bitwise_xor(
                     int &next,
                     int &error)
{
    if (next == OP_BITWISE_AND)
    {
        next = yylex();
        bitwise_and(next, error);
        rest_bitwise_xor(next, error);
    }
    return 0;
}

int bitwise_xor(
                int &next,
                int &error)
{
    bitwise_and(next, error);
    rest_bitwise_xor(next, error);
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
    return 0;
}

int bitwise_or(
               int &next,
               int &error)
{
    bitwise_xor(next, error);
    rest_bitwise_or(next, error);
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

int logical_and(
                int &next,
                int &error)
{
    bitwise_or(next, error);
    rest_logical_and(next, error);
    return 0;
}

int rest_logical_or(
                    int &next,
                    int &error)
{
    if (next == OP_LOGICAL_OR)
    {
        next = yylex();
        logical_and(next, error);
        rest_logical_or(next, error);
    }
    return 0;
}

int logical_or(int &next,
               int &error)
{
    logical_and(next, error);
    rest_logical_or(next, error);
    return 0;
}

int rest_expression(int &next,
                    int &error)
{
    if (next == OP_ASSIGN)
    {
        next = yylex();
        logical_or(next, error);
        rest_expression(next, error);
    }
    return 0;
}

int expression_parser( int &next, int &error)
{
    logical_or(next, error);
    rest_expression(next, error);
    return 0;
}

int declaration_parser( int &next, int &error)
{
    int x = yylex();
    while (x == OP_MULTIPLY)
        x == yylex();

    switch (x)
    {
    case IDENTIFIER:
        x = yylex();
        if (x == SEMICOLON)
            return 0;
        if (x != OP_ASSIGN)
        {
            printf("expected either assigment or semicolom");
            return ++error;
        }
        x = yylex();
        expression_parser(x,error);
        if (error != 0)
        {
            printf("malformed expression\n");
        }
        printf("%d\n", x);
        if (x != SEMICOLON)
        {
            printf("expected ';'\n");

            return ++error;
        }
        yylex();
        return 0;
    default:
        printf("expected declaration\n");
        return 0;
    }
    return 0;
}

int type_parser(int x)
{
    int r = x == KW_INT ||
            x == KW_BOOL ||
            x == KW_FLOAT ||
            x == KW_CHAR ||
            x == KW_UNTYPED;
    return r;
}



int initializer( int &next, int &error)
{

    if (next == OP_ASSIGN)
    {
        next = yylex();
        expression_parser(next, error);
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
                printf("RBRACKET not found");
                return 1;
            }

            nextblock_parser(next, error);
        }
        else
        {
            error++;
            printf("RBRACKET not found");
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
    }

    return 0;
}

int declarationblock_parser( int &next, int &error)
{

    if (type_parser(next))
    {
        next = yylex();
        declaration_parser(next, error);
        restdeclaration_parser(next, error);
    }

    error++;
    printf("DECLARATIONBLOCK error");
    return 1;
}

int function_switchcases_parser( int &next, int &error)
{
    if (next == KW_CASE)
    {
        next = yylex();
        if(next != INT){
            error++;
            printf("INT not found");
            return 1;
        }
        function_block_parser(next, error);
    }

    return 0;
}

int function_elseBlock_parser( int &next, int &error)
{
    if (next == KW_ELSE)
    {
        next = yylex();
        function_block_parser(next, error);
    }

    return 0;
}

int function_statemente_parser( int &next, int &error)
{
    switch (next)
    {
    case KW_LABEL:
        next = yylex();
        if (next != IDENTIFIER)
        {
            error++;
            printf("expected identifier\n");
            return 1;
        }
        next = yylex();
        if (next != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found\n");
            return 1;
        }
        break;
    case SEMICOLON:
        next = yylex();
        break;
    case KW_BREAK:
        next = yylex();
        if (next != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case KW_CONTINUE:
        next = yylex();;
        if (next != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case KW_IF:
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        next = yylex();
        function_block_parser(next, error);
        function_elseBlock_parser(next, error);
        break;
    case KW_GOTO:
        next = yylex();
        if (next != IDENTIFIER)
        {
            error++;
            printf("IDENTIFIER not found");
            return 1;
        }
        next = yylex();
        if (next != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case KW_WHILE:
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        next = yylex();
        if (next != DO)
        {
            error++;
            printf("DO not found");
            return 1;
        }
        next = yylex();
        function_block_parser(next, error);
        break;
    case DO:
        next = yylex();
        function_block_parser(next, error);
        if (next != KW_WHILE)
        {
            error++;
            printf("WHILE not found");
            return 1;
        }
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        break;
    case KW_SWITCH:
        next = yylex();
        if (next != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        next = yylex();
        if (next != LBRACE)
        {
            error++;
            printf("LBRACE not found");
            return 1;
        }
        function_switchcases_parser(next, error);
        if (next != KW_DEFAULT)
        {
            error++;
            printf("KW_DEFAULT not found");
            return 1;
        }
        next = yylex();
        function_block_parser(next, error);
        if (next != RBRACE)
        {
            error++;
            printf("RBRACE not found");
            return 1;
        }
        break;
    case KW_RETURN:
        expression_parser(next, error);
        if (next != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    default:
        if (type_parser(next))
        {
            function_declarationblock_parser(next, error);
            if (next != SEMICOLON)
            {
                error++;
                printf("SEMICOLON not found");
                return 1;
            }
        }
        else
        {
            expression_parser(next, error);
            if (next != SEMICOLON)
            {
                error++;
                printf("SEMICOLON not found");
                return 1;
            }
        }
        break;
    }

    next = yylex();;
    return 0;
}

int function_code_parser( int &next, int &error)
{
    if (next == LBRACE)
    {
        function_block_parser(next, error);
        function_code_parser(next, error);
    }
    else
    {
        function_statement_parser(next, error);
        function_code_parser(next, error);
    }

    return 0;
}

int function_block_parser( int &next, int &error)
{
    if (next == LBRACE)
    {
        next = yylex();

        function_code_parser(next, error);

        if (next == RBRACE)
        {
            next = yylex();
            return 0;
        }
        return 0;
    }
    else
    {
        error++;
        return 1;
    }
}

int function_dimensionblock_parser( int &next, int &error)
{
    if (next == LBRACKET)
    {
        next = yylex();
        if (next == RBRACKET)
        {
            next = yylex();
            function_dimensionblock_parser(next, error);
            return 0;
        }
        else
        {
            error++;
            return 1;
        }
    }

    return 0;
}

int function_reference_parser( int &next, int &error)
{
    if (next == OP_MULTIPLY)
    {
        next = yylex();
        function_reference_parser(next, error);
    }
    return 0;
}

int function_returntype_parser( int &next, int &error)
{
    switch (type_parser(next))
    {
    case 1:
        next = yylex();
        function_reference_parser(next, error);
        function_dimensionblock_parser(next, error);
        return 0;
    default:
        break;
    }

    error++;
    printf("TYPE not exists");
    return 0;
}

int function_param_parser( int &next, int &error)
{
    function_reference_parser(next, error);

    if (next != IDENTIFIER)
    {
        error++;
        printf("IDENTIFIER not exists");
        return 1;
    }

    next = yylex();

    function_dimensionblock_parser(next, error);
    return 0;
}

int function_moreparam( int &next, int &error)
{
    if (next == COMMA)
    {
        next = yylex();
        function_param_parser(next, error);
        function_moreparam(next, error);
    }
    return 0;
}

int function_paramblock_parser(int &next, int &error)
{
    if (type_parser(next)){
        next = yylex();
        
    }
    return 0;
}
int function_moreparamblock_parser( int &next, int &error)
{
    if (next == SEMICOLON)
    {
        next = yylex();
        function_paramblock_parser(next, error);
        function_moreparamblock_parser(next, error);
    }
    else if (type_parser(next))
    {
        next = yylex();
        function_param_parser(next, error);
        function_moreparam(next, error);
    }
    else
    {
    }

    return 0;
}


int function_paramlist_parser( int &next, int &error)
{
    switch (next)
    {
    case KW_VOID:
        next = yylex();
        break;
    default:
        next = yylex();
        function_paramblock_parser(next, error);
        function_moreparamblock_parser(next, error);
        break;
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

    return 0;
}

int function_rest_parser( int &next, int &error)
{
    switch (next)
    {
    case SEMICOLON:
        next = yylex();
        break;
    default:
        return function_block_parser(next, error);
        break;
    }

    return 0;
}

int function_header_parser( int &next, int &error)
{
    function_modifiers_parser(next, error);

    if (next != IDENTIFIER)
    {
        printf("IDENTIFIER not exists\n");
        error++;
        return 1;
    }

    next = yylex();

    if (next != COLON)
    {
        printf("COLON not exists\n");
        error++;
        return 1;
    }

    next = yylex();

    function_paramlist_parser(next, error);

    if (next != ARROW)
    {
        printf("ARROW not exists\n");
        error++;
        return 1;
    }

    function_returntype_parser(next, error);

    return 0;
}

int function_parser( int &next, int &error)
{
    function_header_parser(next, error);
    function_rest_parser(next, error);

    return 0;
}

int global_parser(int& next, int &error)
{
    switch (type_parser(next))
    {
    case 1: // tipo
        return declaration_parser(next, error);
        break;
    default: // identifier
        printf("token: %d\n", next);
        break;
        //       printf("function parser nor implemented\n");
        // function_parser(next, error);
    }

    error++;
    return 1;
}

int globals_parser(int& next, int& error)
{
    int x = yylex();
    if (x == EOI) // EOI = end of input
        return 0;
    switch (x)
    {
    case KW_EXTERN:
        x = yylex();
        global_parser(x,error);
        return globals_parser(x,error);
    default:
        global_parser(x,error);
        globals_parser(x,error);
        if (error == 0)
        {
            printf("input consumido nem um erro encontrado\n");
        }
        return error;
    }
}

void module_parser(int& next, int& error)
{
    switch (next)
    {
    case KW_MODULE:
        if (yylex() == IDENTIFIER && yylex() == SEMICOLON)
        {
            globals_parser(next, error);
        }
        else {
            printf("expected module declaration\n");
        }
        break;
    default:
        printf("expected module declaration\n");
    }
    error += 1;
}

int main()
{
    int next = yylex(), error = 0;
    module_parser(next,error);
    return 0;
}