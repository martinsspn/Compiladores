#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <algorithm>

extern int yylex();
extern int lineno;
extern int col;

int expression_parser(const std::vector<int> &, int &, int &);

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

int factor(const std::vector<int> &inp,
           int &index,
           int &error)
{
    if (inp[index] == LPAREN)
    {
        index++;
        expression_parser(inp, index, error);
        if (inp[index] != RPAREN)
        {
            printf("missing close parenthesis\n");
            error++;
            return 0;
        }
        index++;
    }
    else if (immediate(inp[index]))
    {
        index++;
        return 0;
    }
    return 0;
}

int unary2(const std::vector<int> &inp,
           int &index,
           int &error)
{
    switch (inp[index])
    {
    case OP_ADD:      // +=
    case OP_SUBTRACT: //
    case OP_NOT:
        index++;
        factor(inp, index, error);
        break;
    default:
        factor(inp, index, error);
        break;
    }
    return 0;
}

int unary3(const std::vector<int> &inp,
           int &index,
           int &error)
{
    switch (inp[index])
    {
    case OP_BITWISE_AND: //enderço de memoria
    case OP_MULTIPLY:    //derreferenciar pointer
    case OP_SUBTRACT:    // menos unario
        index++;
        unary2(inp, index, error);
        break;
    default:
        unary2(inp, index, error);
    }
    return 0;
}

int rest_multiplication(const std::vector<int> &inp,
                        int &index,
                        int &error)
{
    if (is_multiplication(inp[index]))
    {
        index++;
        unary3(inp, index, error);
        rest_multiplication(inp, index, error);
    }
    return 0;
}

int multiplication(const std::vector<int> &inp,
                   int &index,
                   int &error)
{
    unary3(inp, index, error);
    rest_multiplication(inp, index, error);
    return 0;
}

int rest_addition(const std::vector<int> &inp,
                  int &index,
                  int &error)
{
    if (is_add_operator(inp[index]))
    {
        multiplication(inp, index, error);
        rest_addition(inp, index, error);
    }
    return 0;
}

int addition(const std::vector<int> &inp,
             int &index,
             int &error)
{
    multiplication(inp, index, error);
    rest_addition(inp, index, error);
    return 0;
}

int rest_shift(const std::vector<int> &inp,
               int &index,
               int &error)
{
    if (inp[index] == OP_BITWISE_LSHIFT || inp[index] == OP_BITWISE_RSHIFT)
    {
        index++;
        addition(inp, index, error);
        rest_shift(inp, index, error);
    }
    return 0;
}

int shift(const std::vector<int> &inp,
          int &index,
          int &error)
{
    addition(inp, index, error);
    rest_shift(inp, index, error);
    return 0;
}

int rest_relation(const std::vector<int> &inp,
                  int &index,
                  int &error)
{
    if (is_rel(inp[index]))
    {
        index++;
        shift(inp, index, error);
        rest_relation(inp, index, error);
    }
    return 0;
}

int relation(const std::vector<int> &inp,
             int &index,
             int &error)
{
    shift(inp, index, error);
    rest_relation(inp, index, error);
    return 0;
}

int rest_equality(const std::vector<int> &inp,
                  int &index,
                  int &error)
{
    if (is_eqoperator(inp[index]))
    {
        index++;
        relation(inp, index, error);
        rest_equality(inp, index, error);
    }
    return 0;
}

int equality(const std::vector<int> &inp,
             int &index,
             int &error)
{

    relation(inp, index, error);
    rest_equality(inp, index, error);
    return 0;
}

int rest_bitwise_and(const std::vector<int> &inp,
                     int &index,
                     int &error)
{
    if (inp[index] == OP_BITWISE_AND)
    {
        equality(inp, index, error);
        rest_bitwise_and(inp, index, error);
    }
    return 0;
}

int bitwise_and(const std::vector<int> &inp,
                int &index,
                int &error)
{
    equality(inp, index, error);
    rest_bitwise_and(inp, index, error);
    return 0;
}

int rest_bitwise_xor(const std::vector<int> &inp,
                     int &index,
                     int &error)
{
    if (inp[index] == OP_BITWISE_AND)
    {
        index++;
        bitwise_and(inp, index, error);
        rest_bitwise_xor(inp, index, error);
    }
    return 0;
}

int bitwise_xor(const std::vector<int> &inp,
                int &index,
                int &error)
{
    bitwise_and(inp, index, error);
    rest_bitwise_xor(inp, index, error);
    return 0;
}

int rest_bitwise_or(const std::vector<int> &inp,
                    int &index,
                    int &error)
{
    if (inp[index] == OP_BITWISE_OR)
    {
        index++;
        bitwise_xor(inp, index, error);
        rest_bitwise_or(inp, index, error);
    }
    return 0;
}

int bitwise_or(const std::vector<int> &inp,
               int &index,
               int &error)
{
    bitwise_xor(inp, index, error);
    rest_bitwise_or(inp, index, error);
    return 0;
}

int rest_logical_and(const std::vector<int> &inp,
                     int &index,
                     int &error)
{
    if (inp[index] == OP_LOGICAL_AND)
    {
        index++;
        bitwise_or(inp, index, error);
        rest_logical_and(inp, index, error);
    }
    return 0;
}

int logical_and(const std::vector<int> &inp,
                int &index,
                int &error)
{
    bitwise_or(inp, index, error);
    rest_logical_and(inp, index, error);
    return 0;
}

int rest_logical_or(const std::vector<int> &inp,
                    int &index,
                    int &error)
{
    if (inp[index] == OP_LOGICAL_OR)
    {
        index++;
        logical_and(inp, index, error);
        rest_logical_or(inp, index, error);
    }
    return 0;
}

int logical_or(const std::vector<int> &inp,
               int &index,
               int &error)
{
    logical_and(inp, index, error);
    rest_logical_or(inp, index, error);
    return 0;
}

int rest_expression(const std::vector<int> &inp,
                    int &index,
                    int &error)
{
    if (inp[index] == OP_ASSIGN)
    {
        index++;
        logical_or(inp, index, error);
        rest_expression(inp, index, error);
    }
    return 0;
}

int expression_parser(const std::vector<int> &inp, int &index, int &error)
{
    logical_or(inp, index, error);
    rest_expression(inp, index, error);
    return 0;
}

int declaration_parser(const std::vector<int> &inp, int &index, int &error)
{
    index++;
    while (inp[index] == OP_MULTIPLY)
        index++;

    switch (inp[index])
    {
    case IDENTIFIER:
        index++;
        if (inp[index] == SEMICOLON)
            return 0;
        if (inp[index] != OP_ASSIGN)
        {
            printf("expected either assigment or semicolom");

            return ++error;
        }
        index++;
        expression_parser(inp, index, error);
        if (error != 0)
        {
            printf("malformed expression\n");
        }
        if (inp[index] != SEMICOLON)
        {
            printf("expected ';'\n");

            return ++error;
        }
        index++;
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

int function_paramblock_parser(const std::vector<int> &inp, int &index, int &error)
{
}

int initializer(const std::vector<int> &inp, int &index, int &error)
{

    if (inp[index] == OP_EQUAL)
    {
        index++;
        expression_parser(inp, index, error);
    }

    return 0;
}

int indexblock_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == LBRACKET)
    {
        index++;

        if (inp[index] == INT)
        {
            index++;
            if (inp[index] != RBRACKET)
            {
                error++;
                printf("RBRACKET not found");
                return 1;
            }

            indexblock_parser(inp, index, error);
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

int restdeclaration_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == COMMA)
    {
        index++;
        declaration_parser(inp, index, error);
        restdeclaration_parser(inp, index, error);
    }

    return 0;
}

int declarationblock_parser(const std::vector<int> &inp, int &index, int &error)
{

    if (type_parser(inp[index]))
    {
        index++;
        declaration_parser(inp, index, error);
        restdeclaration_parser(inp, index, error);
    }

    error++;
    printf("DECLARATIONBLOCK error");
    return 1;
}

int function_switchcases_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == KW_CASE)
    {
        index++;
        if(inp[index] != INT){
            error++;
            printf("INT not found");
            return 1;
        }
        function_block_parser(inp, index, error);
    }

    return 0;
}

int function_elseBlock_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == KW_ELSE)
    {
        index++;
        function_block_parser(inp, index, error);
    }

    return 0;
}

int function_statemente_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (inp[index])
    {
    case KW_LABEL:
        index++;
        if (inp[index] != IDENTIFIER)
        {
            error++;
            printf("IDENTIFIER not exists");
            return 1;
        }
        index++;
        if (inp[index] != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case SEMICOLON:
        break;
    case KW_BREAK:
        index++;
        if (inp[index] != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case KW_CONTINUE:
        index++;
        if (inp[index] != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case KW_IF:
        index++;
        if (inp[index] != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        index++;
        expression_parser(inp, index, error);
        if (inp[index] != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        index++;
        function_block_parser(inp, index, error);
        function_elseBlock_parser(inp, index, error);
        break;
    case KW_GOTO:
        index++;
        if (inp[index] != IDENTIFIER)
        {
            error++;
            printf("IDENTIFIER not found");
            return 1;
        }
        index++;
        if (inp[index] != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    case KW_WHILE:
        index++;
        if (inp[index] != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        index++;
        expression_parser(inp, index, error);
        if (inp[index] != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        index++;
        if (inp[index] != DO)
        {
            error++;
            printf("DO not found");
            return 1;
        }
        index++;
        function_block_parser(inp, index, error);
        break;
    case DO:
        index++;
        function_block_parser(inp, index, error);
        if (inp[index] != WHILE)
        {
            error++;
            printf("WHILE not found");
            return 1;
        }
        index++;
        if (inp[index] != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        index++;
        expression_parser(inp, index, error);
        if (inp[index] != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        break;
    case KW_SWITCH:
        index++;
        if (inp[index] != LPAREN)
        {
            error++;
            printf("LPARAN not found");
            return 1;
        }
        index++;
        expression_parser(inp, index, error);
        if (inp[index] != RPAREN)
        {
            error++;
            printf("RPARAN not found");
            return 1;
        }
        index++;
        if (inp[index] != LBRACE)
        {
            error++;
            printf("LBRACE not found");
            return 1;
        }
        function_switchcases_parser(inp, index, error);
        if (inp[index] != KW_DEFAULT)
        {
            error++;
            printf("KW_DEFAULT not found");
            return 1;
        }
        index++;
        function_block_parser(inp, index, error);
        if (inp[index] != RBRACE)
        {
            error++;
            printf("RBRACE not found");
            return 1;
        }
        break;
    case KW_RETURN:
        expression_parser(inp, index, error);
        if (inp[index] != SEMICOLON)
        {
            error++;
            printf("SEMICOLON not found");
            return 1;
        }
        break;
    default:
        if (type_parser(inp[index]))
        {
            function_declarationblock_parser(inp, index, error);
            if (inp[index] != SEMICOLON)
            {
                error++;
                printf("SEMICOLON not found");
                return 1;
            }
        }
        else
        {
            expression_parser(inp, index, error);
            if (inp[index] != SEMICOLON)
            {
                error++;
                printf("SEMICOLON not found");
                return 1;
            }
        }
        break;
    }

    index++;
    return 0;
}

int function_code_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == LBRACE)
    {
        function_block_parser(inp, index, error);
        function_code_parser(inp, index, error);
    }
    else
    {
        function_statement_parser(inp, index, error);
        function_code_parser(inp, index, error);
    }

    return 0;
}

int function_block_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == LBRACE)
    {
        index++;

        function_code_parser(inp, index, error);

        if (inp[index] == RBRACE)
        {
            index++;
            return 0;
        }
    }
    else
    {
        error++;
        return 1;
    }
}

int function_dimensionblock_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == LBRACKET)
    {
        index++;
        if (inp[index] == RBRACKET)
        {
            index++;
            function_dimensionblock_parser(inp, index, error);
            retun 0;
        }
        else
        {
            error++;
            return 1;
        }
    }

    return 0;
}

int function_reference_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == OP_MULTIPLY)
    {
        index++;
        function_reference_parser(inp, index, error);
    }
    return 0;
}

int function_returntype_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (type_parser(inp[index]))
    {
    case 1:
        index++;
        function_reference_parser(inp, index, error);
        function_dimensionblock_parser(inp, index, error);
    default:
        break;
    }

    error++;
    printf("TYPE not exists");
    return 0;
}

int function_param_parser(const std::vector<int> &inp, int &index, int &error)
{
    function_reference_parser(inp, index, error);

    if (inp[index] != IDENTIFIER)
    {
        error++;
        printf("IDENTIFIER not exists");
        return 1;
    }

    index++;

    function_dimensionblock_parser(inp, index, error);
    return 0;
}

int function_moreparam(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == COMMA)
    {
        index++;
        function_param_parser(inp, index, error);
        function_moreparam(inp, index, error);
    }
    return 0;
}

int function_moreparamblock_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == SEMICOLON)
    {
        index++;
        function_paramblock_parser(inp, index, error);
        function_moreparamblock_parser(inp, index, error);
    }
    else if (type_parser(inp[index]))
    {
        index++;
        function_param_parser(inp, index, error);
        function_moreparam(inp, index, error);
    }
    else
    {
    }

    return 0;
}

int function_paramlist_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (inp[index])
    {
    case KW_VOID:
        index++;
        break;
    default:
        index++;
        function_paramblock_parser(inp, index, error);
        function_moreparamblock_parser(inp, index, error);
        break;
    }
    return 0;
}

int function_modifiers_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (inp[index])
    {
    case KW_START:
        index++;
        break;
    default:
        break;
    }

    return 0;
}

int function_rest_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (inp[index])
    {
    case SEMICOLON:
        index++;
        break;
    default:
        return function_block_parser(inp, index, error);
        break;
    }

    return 0;
}

int function_header_parser(const std::vector<int> &inp, int &index, int &error)
{
    function_modifiers_parser(inp, index, error);

    if (inp[index] != IDENTIFIER)
    {
        printf("IDENTIFIER not exists\n");
        error++;
        return 1;
    }

    index++;

    if (inp[index] != COLON)
    {
        printf("COLON not exists\n");
        error++;
        return 1;
    }

    index++;

    function_paramlist_parser(inp, index, error);

    if (inp[index] != ARROW)
    {
        printf("ARROW not exists\n");
        error++;
        return 1;
    }

    function_returntype_parser(inp, index, error);

    return 0;
}

int function_parser(const std::vector<int> &inp, int &index, int &error)
{
    function_header_parser(inp, index, error);
    function_rest_parser(inp, index, error);

    return 0;
}

int global_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (type_parser(inp[index]))
    {
    case 1: // tipo
        return declaration_parser(inp, index, error);
        break;
    default: // identifier
        printf("token: %d\n", inp[index]);
        index++;
        break;
        //       printf("function parser nor implemented\n");
        // function_parser(inp, index, error);
    }

    ++error;
    return 1;
}

int globals_parser(const std::vector<int> &inp, int &index, int &error)
{
    if (inp[index] == 0)
        return 0;
    switch (inp[index])
    {
    case KW_EXTERN:
        index++;
        global_parser(inp, index, error);
        return globals_parser(inp, index, error);
    default:
        global_parser(inp, index, error);

        globals_parser(inp, index, error);
        if (error == 0)
        {
            printf("input consumido nem um erro encontrado\n");
        }
        return error;
    }
}

int module_parser(const std::vector<int> &inp, int &index, int &error)
{
    switch (inp[index])
    {
    case KW_MODULE:
        index++;

        if (inp[index] == IDENTIFIER && inp[index + 1] == SEMICOLON)
        {
            index += 2;
            return globals_parser(inp, index, error);
        }
        break;
    default:
        printf("expected module declaration\n");
    }
    error += 1;
    return 1;
}

void clean(std::vector<int> &inp)
{
    for (int i = 0; i < inp.size() - 1; i++)
    {
        if (inp[i] != 606)
            continue;
        inp.erase(inp.begin() + i);
    }
}

int main()
{
    int x = yylex();
    std::vector<int> inp;
    inp.push_back(x);
    while (x)
    {
        x = yylex();
        inp.push_back(x);
    }
    clean(inp);
    while (*(inp.end() - 1) < 10)
        inp.erase(inp.end() - 1);
    for (int e : inp)
        printf("%d\n", e);
    int index = 0, error = 0;
    printf("resultado %d\n", module_parser(inp, index, error));

    printf("index = %d e tamanho entrada = %ld\n", index, inp.size());
    return 0;
}