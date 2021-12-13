#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

extern int yylex();
extern int yylineno;
extern int col;

int expression_parser(int &, int &);
int function_block_parser (int &, int &);
int declarationblock_parser(int &, int &);

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
    return x == INT ||
           x == HEX ||
           x == BIN ||
           x == KW_TRUE ||
           x == KW_FALSE ||
           x == CHAR ||
           x == STRING;
}

int more_expression(int &next, int &error) {
    switch(next) {
        case COMMA:
            next = yylex();
            expression_parser(next, error);
            more_expression(next, error);
            break;
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
            return 0;
    }
    return 0;
}

int factor(
           int &next,
           int &error)
{
    if (next == LPAREN)
    {
        next = yylex();
        expression_parser(next, error);
        if (next != RPAREN)
        {
            printf(" at line: %d, col: %d missing close parenthesis\n",yylineno, col);
            error++;
            return 0;
        }
        next = yylex();
    }
    else if (next == IDENTIFIER){
        next = yylex();
        application_parser(next,error);
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
    next = yylex();
    while (next == OP_MULTIPLY)
        next == yylex();
    switch (next)
    {
    case IDENTIFIER:
        next = yylex();
        if (next == SEMICOLON) {
            next = yylex();
            return 0;
        }
        if (next == LBRACKET) {
            next = yylex();
            expression_parser(next, error);
            if (next != RBRACKET) {
                printf("at line: %d col: %d expected ']'\n", yylineno, col);
            }
            next = yylex();
            return 0;
        }
        if (next != OP_ASSIGN)
        {
            printf(" at line: %d, col: %d expected either assigment or semicolom\n",yylineno, col);
            return ++error;
        }
        next = yylex();
        expression_parser(next, error);
        if (error != 0)
        {
            printf(" at line: %d, col: %d malformed expression\n",yylineno, col);
        }
        if (next != SEMICOLON)
        {
            printf(" at line: %d, col: %d expected ';'\n",yylineno, col);

            return ++error;
        }
        next = yylex();
        break;
    default:
        printf(" at line: %d, col: %d expected declaration\n",yylineno, col);
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



int initializer(int &next, int &error)
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
    }

    return 0;
}

int declarationblock_parser( int &next, int &error)
{

    if (type_parser(next))
    {
        declaration_parser(next, error);
        restdeclaration_parser(next, error);
        return 0;
    }

    error++;
    printf(" at line: %d, col: %d DECLARATIONBLOCK error\n",yylineno, col);
    return 1;
}

int function_switchcases_parser( int &next, int &error)
{
    if (next == KW_CASE)
    {
        next = yylex();
        if(next != INT){
            error++;
            printf(" at line: %d, col: %d INT not found\n",yylineno, col);
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

int function_statement_parser( int &next, int &error)
{
    switch (next)
    {
    case KW_LABEL:
        next = yylex();
        if (next != IDENTIFIER)
        {
            error++;
            printf(" at line: %d, col: %d expected identifier\n",yylineno, col);
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
        function_block_parser(next, error);
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
        function_block_parser(next, error);
        break;
    case DO:
        next = yylex();
        function_block_parser(next, error);
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
        function_switchcases_parser(next, error);
        if (next != KW_DEFAULT)
        {
            error++;
            printf(" at line: %d, col: %d KW_DEFAULT not found\n",yylineno, col);
            return 1;
        }
        next = yylex();
        function_block_parser(next, error);
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
    case IDENTIFIER:
        next = yylex();
        application_parser(next, error);
        initializer(next, error);
        if (next != SEMICOLON){
            error++;
            printf("at line %d col: %d expected ';'\n", yylineno, col);
            return 0;
        }
        next = yylex();
        break;
    default:
        if (type_parser(next))
        {
            declarationblock_parser(next, error);
        }
        else
        {
            expression_parser(next, error);
            if (next != SEMICOLON)
            {
                error++;
                printf("%d at line: %d, col: %d SEMICOLON not found\n",next,yylineno, col);
                return 1;
            }
            next = yylex();
        }
        break;
    }
    return 0;
}

int function_code_parser( int &next, int &error)
{
    if (next == RBRACE) return 0;
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
        printf("expected '{' at line: %d col: %d\n", yylineno, col);
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
    if (next != ARROW) {
        error++;
        return 0;
    }
    next = yylex();
    switch (type_parser(next) || next == KW_VOID)
    {
    case 1:
        next = yylex();
        function_reference_parser(next, error);
        function_dimensionblock_parser(next, error);
        return 0;
    default:
        printf(" at line: %d, col: %d expected return type\n",yylineno, col);
        break;
    }

    error++;
    printf(" at line: %d, col: %d TYPE not exists\n",yylineno, col);
    return 0;
}

int function_param_parser( int &next, int &error)
{
    function_reference_parser(next, error);

    if (next != IDENTIFIER)
    {
        error++;
        printf(" at line: %d, col: %d IDENTIFIER not exists\n",yylineno, col);
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
    if (!type_parser(next)){
        error++;
        printf(" at line: %d, col: %d expected type\n",yylineno, col);
    }
    next = yylex();
    function_param_parser(next, error);
    function_moreparam(next,error);
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
        printf(" at line: %d, col: %d IDENTIFIER not exists\n",yylineno, col);
        error++;
        return 1;
    }

    next = yylex();

    if (next != COLON)
    {
        printf(" at line: %d, col: %d COLON not exists\n",yylineno, col);
        error++;
        return 1;
    }

    next = yylex();

    function_paramlist_parser(next, error);

    if (next != ARROW)
    {
        printf(" at line: %d, col: %d ARROW not exists\n",yylineno, col);
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
        declaration_parser(next, error);
        break;
    default: // identifier
        return function_parser(next, error);
        break;
        //       printf(" at line: %d, col: %d function parser nor implemented\n");
        // function_parser(next, error);
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
        return globals_parser(next,error);
    default:
        global_parser(next,error);
        globals_parser(next,error);
        return error;
    }
}

void module_parser(int& next, int& error)
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
                printf("hoy at line: %d, col: %d expected module declaration\n",yylineno, col);
            }
            if (error == 0)
            {
                printf("input consumido nem um erro encontrado\n");
            }
            break;
        }
    default:
        printf(" at line: %d, col: %d expected module declaration\n",yylineno, col);
    }
}

int main()
{
    int next = yylex(), error = 0;
    module_parser(next,error);
    return 0;
}