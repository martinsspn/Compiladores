#include "lex.yy.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stack>

int main()
{

    // linhas = não terminais | colunas = terminais
    std::unordered_map<int, std::unordered_map<int, std::vector<int>>> tabela;

    // REGRA MODULE (INVERTER A LISTA)
    std::vector<int> module_ = {KW_MODULE, IDENTIFIER, SEMICOLON, NT_GLOBALS};
    // define a coluna
    std::unordered_map<int, std::vector<int>> module_rule;
    // insere a lista na célula
    module_rule.insert({KW_MODULE, module_});
    tabela.insert({NT_MODULE, module_rule});

    // REGRA GLOBALS
    // COMO REPRESENTAR O VAZIO? DEFINE UMA REPRESENTAÇÃO
    std::vector<int> globals_ = {EMPTY};
    std::vector<int> globals_1 = {NT_GLOBAL, NT_GLOBALS};
    std::vector<int> globals_2 = {KW_EXTERN, NT_GLOBAL, NT_GLOBALS};
    std::unordered_map<int, std::vector<int>> globals_rule;

    globals_rule.insert({EOI, globals_});

    globals_rule.insert({KW_BOOL, globals_1});
    globals_rule.insert({KW_CHAR, globals_1});
    globals_rule.insert({KW_FLOAT, globals_1});
    globals_rule.insert({KW_INT, globals_1});
    globals_rule.insert({KW_UNTYPED, globals_1});
    globals_rule.insert({KW_START, globals_1});
    globals_rule.insert({IDENTIFIER, globals_1});
    globals_rule.insert({SEMICOLON, globals_1});
    globals_rule.insert({LBRACE, globals_1});

    globals_rule.insert({KW_EXTERN, globals_2});

    tabela.insert({NT_GLOBALS, globals_rule});

    std::vector<int> global_ = {NT_FUNCTION};
    std::vector<int> global_1 = {NT_DECLARATIONBLOCK, SEMICOLON};
    std::unordered_map<int, std::vector<int>> global_rule = {
        {EOI, global_},
        {KW_START, global_},
        {IDENTIFIER, global_},
        {SEMICOLON, global_},
        {LBRACE, global_},
        {KW_EXTERN, global_},

        {KW_BOOL, global_1},
        {KW_CHAR, global_1},
        {KW_FLOAT, global_1},
        {KW_INT, global_1},
        {KW_UNTYPED, global_1},
    };
    tabela.insert({NT_GLOBAL, global_rule});

    std::vector<int> function_ = {NT_FUNCTIONHEADER, NT_FUNCTIONREST};
    std::unordered_map<int, std::vector<int>> function_rule = {
        {EOI, function_},
        {KW_EXTERN, function_},
        {KW_BOOL, function_},
        {KW_CHAR, function_},
        {KW_FLOAT, function_},
        {KW_INT, function_},
        {KW_UNTYPED, function_},
        {KW_START, function_},
        {IDENTIFIER, function_},
        {SEMICOLON, function_},
        {LBRACE, function_}};
    tabela.insert({NT_FUNCTION, function_rule});

    std::vector<int> functionheader_ = {NT_MODIFIERS, IDENTIFIER, COLON, NT_PARAMLIST, ARROW, NT_RETURNTYPE};
    std::unordered_map<int, std::vector<int>> functionheader_rule = {
        {IDENTIFIER, functionheader_},
        {SEMICOLON, functionheader_},
        {KW_START, functionheader_},
        {LBRACE, functionheader_}};
    tabela.insert({NT_FUNCTIONHEADER, functionheader_rule});

    std::vector<int> functionrest_ = {SEMICOLON};
    std::vector<int> functionrest_1 = {NT_BLOCK};
    std::unordered_map<int, std::vector<int>> functionrest_rule = {
        {SEMICOLON, functionrest_},
        {LBRACE, functionrest_1},
    };
    tabela.insert({NT_FUNCTIONREST, functionrest_rule});

    std::vector<int> modifiers_ = {EMPTY};
    std::vector<int> modifiers_1 = {KW_START};
    std::unordered_map<int, std::vector<int>> modifiers_rule = {
        {IDENTIFIER, modifiers_},
        {KW_START, modifiers_1}};
    tabela.insert({NT_MODIFIERS, modifiers_rule});

    std::vector<int> paramlist_ = {KW_VOID};
    std::vector<int> paramlist_1 = {NT_PARAMBLOCK, NT_MOREPARAMBLOCK};
    std::unordered_map<int, std::vector<int>> paramlist_rule = {
        {KW_VOID, paramlist_},
        {KW_BOOL, paramlist_1},
        {KW_CHAR, paramlist_1},
        {KW_FLOAT, paramlist_1},
        {KW_INT, paramlist_1},
        {KW_UNTYPED, paramlist_1}};
    tabela.insert({NT_PARAMLIST, paramlist_rule});

    std::vector<int> moreparamblock_ = {EMPTY};
    std::vector<int> moreparamblock_1 = {SEMICOLON, NT_PARAMBLOCK, NT_MOREPARAMBLOCK};
    std::unordered_map<int, std::vector<int>> moreparamblock_rule = {
        {ARROW, moreparamblock_},
        {COMMA, moreparamblock_},
        {SEMICOLON, moreparamblock_1}};
    tabela.insert({NT_MOREPARAMBLOCK, moreparamblock_rule});

    std::vector<int> paramblock_ = {NT_TYPE, NT_PARAM, NT_MOREPARAM};
    std::unordered_map<int, std::vector<int>> paramblock_rule = {
        {KW_BOOL, paramblock_},
        {KW_CHAR, paramblock_},
        {KW_FLOAT, paramblock_},
        {KW_INT, paramblock_},
        {KW_UNTYPED, paramblock_}};
    tabela.insert({NT_PARAMBLOCK, paramblock_rule});

    std::vector<int> moreparam_ = {EMPTY};
    std::vector<int> moreparam_1 = {COMMA, NT_PARAM, NT_MOREPARAM};
    std::unordered_map<int, std::vector<int>> moreparam_rule = {
        {ARROW, moreparam_},
        {SEMICOLON, moreparam_},
        {COMMA, moreparam_1},
        {COLON, moreparam_1}};
    tabela.insert({NT_MOREPARAM, moreparam_rule});

    std::vector<int> param_ = {EMPTY};
    std::vector<int> param_1 = {NT_REFERENCE, IDENTIFIER, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> param_rule = {
        {ARROW, param_},
        {SEMICOLON, param_},
        {COLON, param_},
        {IDENTIFIER, param_1},
        {OP_MULTIPLY, param_1}};
    tabela.insert({NT_PARAM, param_rule});

    std::vector<int> returntype_ = {NT_TYPE, NT_REFERENCE, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> returntype_rule = {
        {KW_VOID, returntype_},
        {KW_BOOL, returntype_},
        {KW_CHAR, returntype_},
        {KW_FLOAT, returntype_},
        {KW_INT, returntype_},
        {KW_UNTYPED, returntype_}};
    tabela.insert({NT_RETURNTYPE, returntype_rule});

    std::vector<int> reference_ = {EMPTY};
    std::vector<int> reference_1 = {OP_MULTIPLY, NT_REFERENCE};
    std::unordered_map<int, std::vector<int>> reference_rule = {
        {IDENTIFIER, reference_},
        {SEMICOLON, reference_},
        {LBRACE, reference_},
        {LBRACKET, reference_},

        {OP_MULTIPLY, reference_1}};
    tabela.insert({NT_REFERENCE, reference_rule});

    std::vector<int> dimensionblock_ = {EMPTY};
    std::vector<int> dimensionblock_1 = {LBRACKET, RBRACKET, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> dimensionblock_rule = {
        {ARROW, dimensionblock_},
        {SEMICOLON, dimensionblock_},
        {COLON, dimensionblock_},
        {LBRACE, dimensionblock_},
        {COMMA, dimensionblock_},
        {LBRACKET, dimensionblock_1}};
    tabela.insert({NT_DIMENSIONBLOCK, dimensionblock_rule});

    std::vector<int> block_ = {LBRACE, NT_CODE, RBRACE};
    std::unordered_map<int, std::vector<int>> block_rule = {
        {LBRACE, block_}};
    tabela.insert({NT_BLOCK, block_rule});

    std::vector<int> code_ = {EMPTY};
    std::vector<int> code_1 = {NT_BLOCK, NT_CODE};
    std::vector<int> code_2 = {NT_STATEMENT, NT_CODE};
    std::unordered_map<int, std::vector<int>> code_rule = {
        {RBRACE, code_},

        {LBRACE, code_1},
        {OP_ADD, code_2},
        {KW_LABEL, code_2},
        {SEMICOLON, code_2},
        {KW_BREAK, code_2},
        {KW_CONTINUE, code_2},
        {KW_IF, code_2},
        {KW_GOTO, code_2},
        {KW_WHILE, code_2},
        {DO, code_2},
        {KW_SWITCH, code_2},
        {KW_RETURN, code_2},
        {IDENTIFIER, code_2},
        {KW_TRUE, code_2},
        {KW_FALSE, code_2},
        {KW_CHAR, code_2},
        {KW_UNTYPED, code_2},
        {KW_FLOAT, code_2},
        {KW_INT, code_2},
        {LPAREN, code_2},
        {KW_CHAR, code_2},
        {KW_FLOAT, code_2},
        {KW_INT, code_2},
        {KW_BOOL, code_2},
        {KW_UNTYPED, code_2}};
    tabela.insert({NT_CODE, code_rule});

    std::vector<int> statement_ = {KW_LABEL, IDENTIFIER};
    std::vector<int> statement_1 = {SEMICOLON};
    std::vector<int> statement_2 = {KW_BREAK, SEMICOLON};
    std::vector<int> statement_3 = {KW_CONTINUE, SEMICOLON};
    std::vector<int> statement_4 = {KW_IF, LPAREN, NT_EXPRESSION, RPAREN, NT_BLOCK, NT_elseBLOCK};
    std::vector<int> statement_5 = {KW_GOTO, IDENTIFIER, SEMICOLON};
    std::vector<int> statement_6 = {KW_WHILE, LPAREN, NT_EXPRESSION, RPAREN, DO, NT_BLOCK};
    std::vector<int> statement_7 = {DO, NT_BLOCK, KW_WHILE, LPAREN, NT_EXPRESSION, RPAREN};
    std::vector<int> statement_8 = {KW_SWITCH, LPAREN, NT_EXPRESSION, RPAREN, LBRACE, NT_SWITCHCASES, KW_DEFAULT, NT_BLOCK, RBRACE};
    std::vector<int> statement_9 = {KW_RETURN, NT_EXPRESSION};
    std::vector<int> statement_10 = {NT_EXPRESSION, SEMICOLON};
    std::vector<int> statement_11 = {NT_DECLARATIONBLOCK, SEMICOLON};
    std::unordered_map<int, std::vector<int>> statement_rule = {
        {KW_LABEL, statement_},

        {SEMICOLON, statement_1},

        {KW_BREAK, statement_2},

        {KW_CONTINUE, statement_3},

        {KW_IF, statement_4},

        {KW_GOTO, statement_5},

        {KW_WHILE, statement_6},

        {DO, statement_7},

        {KW_SWITCH, statement_8},

        {KW_RETURN, statement_9},

        {IDENTIFIER, statement_11},
        {KW_TRUE, statement_10},
        {KW_FALSE, statement_10},
        // {KW_CHAR, statement_10},
        // {KW_FLOAT, statement_10},
        // {KW_INT, statement_10},
        // {KW_UNTYPED, statement_10},
        {LPAREN, statement_10},

        {KW_CHAR, statement_11},
        {KW_FLOAT, statement_11},
        {KW_INT, statement_11},
        {KW_BOOL, statement_11},
        // {OP_ADD, }
        {KW_UNTYPED, statement_11}};
    tabela.insert({NT_STATEMENT, statement_rule});

    std::vector<int> elseBlock_ = {EMPTY};
    std::vector<int> elseBlock_1 = {KW_ELSE, NT_BLOCK};
    std::unordered_map<int, std::vector<int>> elseBlock_rule = {
        {RBRACE, elseBlock_},
        {LBRACE, elseBlock_},
        {KW_LABEL, elseBlock_},
        {SEMICOLON, elseBlock_},
        {KW_BREAK, elseBlock_},
        {KW_CONTINUE, elseBlock_},
        {KW_IF, elseBlock_},
        {KW_GOTO, elseBlock_},
        {KW_WHILE, elseBlock_},
        {DO, elseBlock_},
        {KW_SWITCH, elseBlock_},
        {KW_RETURN, elseBlock_},
        {KW_BOOL, elseBlock_},
        {KW_CHAR, elseBlock_},
        {KW_FLOAT, elseBlock_},
        {KW_INT, elseBlock_},
        {KW_UNTYPED, elseBlock_},
        {OP_BITWISE_AND, elseBlock_},
        {OP_MULTIPLY, elseBlock_},
        {OP_SUBTRACT, elseBlock_},
        {IDENTIFIER, elseBlock_},
        {LPAREN, elseBlock_},
        {KW_ELSE, elseBlock_1}};
    tabela.insert({NT_elseBLOCK, elseBlock_rule});

    std::vector<int> switchcase_ = {EMPTY};
    std::vector<int> switchcase_1 = {KW_CASE, INT, NT_BLOCK};
    std::unordered_map<int, std::vector<int>> switchcase_rule = {
        {KW_DEFAULT, switchcase_},
        {KW_CASE, switchcase_1}};
    tabela.insert({NT_SWITCHCASES, switchcase_rule});

    std::vector<int> declarationblock_ = {NT_TYPE, NT_DECLARATION, NT_RESTDECLARATION};
    std::unordered_map<int, std::vector<int>> declarationblock_rule = {
        {IDENTIFIER, declarationblock_},
        {KW_BOOL, declarationblock_},
        {KW_UNTYPED, declarationblock_},
        {KW_CHAR, declarationblock_},
        {KW_FLOAT, declarationblock_},
        {KW_INT, declarationblock_}};
    tabela.insert({NT_DECLARATIONBLOCK, declarationblock_rule});

    std::vector<int> restdeclaration_ = {EMPTY};
    std::vector<int> restdeclaration_1 = {COLON, NT_DECLARATION, NT_RESTDECLARATION};
    std::unordered_map<int, std::vector<int>> restdeclaration_rule = {
        {EOI, restdeclaration_},
        {SEMICOLON, restdeclaration_},
        {COLON, restdeclaration_1}};
    tabela.insert({NT_RESTDECLARATION, restdeclaration_rule});

    std::vector<int> declaration_ = {NT_REFERENCE, IDENTIFIER, NT_INDEXBLOCK, NT_INITIALIZER};
    std::unordered_map<int, std::vector<int>> declaration_rule = {
        {SEMICOLON, declaration_},
        {COLON, declaration_},
        {OP_MULTIPLY, declaration_},
        {OP_ASSIGN, declaration_},
        {IDENTIFIER, declaration_}};
    tabela.insert({NT_DECLARATION, declaration_rule});

    std::vector<int> indexblock_ = {EMPTY};
    std::vector<int> indexblock_1 = {LBRACKET, NT_INDEXBLOCKTYPES, RBRACKET, NT_INDEXBLOCK};
    std::vector<int> indexblock_2 = {LPAREN, IDENTIFIER, NT_INDEXBLOCKTXT};
    std::unordered_map<int, std::vector<int>> indexblock_rule = {
        {SEMICOLON, indexblock_},
        {COLON, indexblock_},
        // {OP_EQUAL, indexblock_},
        {OP_ASSIGN, indexblock_},
        {LBRACKET, indexblock_1},
        {LPAREN, indexblock_2}};
    tabela.insert({NT_INDEXBLOCK, indexblock_rule});

    std::vector<int> indexblocktxt_ = {RPAREN};
    std::vector<int> indexblocktxt_1 = {COMMA, IDENTIFIER, NT_INDEXBLOCKTXT};
    std::unordered_map<int, std::vector<int>> indexblocktxt_rule = {
        {RPAREN, indexblocktxt_},
        {COMMA, indexblocktxt_1}
    };
    tabela.insert({NT_INDEXBLOCKTXT, indexblocktxt_rule});


    std::vector<int> indexblocktypes_ = {INT};
    std::vector<int> indexblocktypes_1 = {NT_EXPRESSION, };
    std::unordered_map<int, std::vector<int>> indexblocktypes_rules = {
        {INT, indexblocktypes_},
        {IDENTIFIER, indexblocktypes_1}
    };
    tabela.insert({NT_INDEXBLOCKTYPES, indexblocktypes_rules});


    std::vector<int> initializer_ = {EMPTY};
    std::vector<int> initializer_1 = {OP_ASSIGN, NT_EXPRESSION};
    std::unordered_map<int, std::vector<int>> initializer_rule = {
        {SEMICOLON, initializer_},
        {COLON, initializer_},
        {OP_ASSIGN, initializer_1}
        };
    tabela.insert({NT_INITIALIZER, initializer_rule});

    std::vector<int> expression_ = {NT_LOGICALOR, NT_RESTEXPRESSION};
    std::unordered_map<int, std::vector<int>> expression_rule = {
        {IDENTIFIER, expression_},
        {KW_TRUE, expression_},
        {KW_FALSE, expression_},
        {KW_CHAR, expression_},
        {KW_FLOAT, expression_},
        {KW_INT, expression_},
        {KW_UNTYPED, expression_},
        {LPAREN, expression_},
        {INT, expression_},
        {FLOAT, expression_},
        {CHAR, expression_},
        {TRUE, expression_},
        {FALSE, expression_}};
    tabela.insert({NT_EXPRESSION, expression_rule});

    std::vector<int> restexpression_ = {EMPTY};
    std::vector<int> restexpression_1 = {OP_ASSIGN, NT_LOGICALOR, NT_RESTEXPRESSION};
    std::unordered_map<int, std::vector<int>> restexpression_rule = {
        {RPAREN, restexpression_},
        {SEMICOLON, restexpression_},
        {COLON, restexpression_},
        {RBRACKET, restexpression_},
        {OP_BITWISE_OR, restexpression_},
        {OP_BITWISE_AND, restexpression_},
        {OP_LOGICAL_AND, restexpression_},
        {OP_LOGICAL_OR, restexpression_},
        {OP_EQUAL, restexpression_},
        {OP_ASSIGN, restexpression_1},
        {OP_NOTEQUAL, restexpression_},
        {OP_LESS, restexpression_},
        {OP_LESSEQUAL, restexpression_},
        {OP_GREATER, restexpression_},
        {OP_GREATEREQUAL, restexpression_},
        {OP_BITWISE_LSHIFT, restexpression_},
        {OP_BITWISE_RSHIFT, restexpression_},
        {OP_ADD, restexpression_},
        {OP_SUBTRACT, restexpression_},
        {OP_MULTIPLY, restexpression_},
        {OP_DIVIDE, restexpression_},
        {OP_MODULUS, restexpression_}};
    tabela.insert({NT_RESTEXPRESSION, restexpression_rule});

    std::vector<int> logicalor_ = {NT_LOGICALAND, NT_RESTLOGICALOR};
    std::unordered_map<int, std::vector<int>> logicalor_rule = {
        {IDENTIFIER, logicalor_},
        {KW_TRUE, logicalor_},
        {KW_FALSE, logicalor_},
        {KW_CHAR, logicalor_},
        {KW_FLOAT, logicalor_},
        {KW_INT, logicalor_},
        {KW_UNTYPED, logicalor_},
        {LPAREN, logicalor_},
        {INT, logicalor_},
        {FLOAT, logicalor_},
        {CHAR, logicalor_},
        {TRUE, logicalor_},
        {FALSE, logicalor_}};
    tabela.insert({NT_LOGICALOR, logicalor_rule});

    std::vector<int> restlogicalor_ = {EMPTY};
    std::vector<int> restlogicalor_1 = {OP_LOGICAL_OR, NT_LOGICALAND, NT_RESTLOGICALOR};
    std::unordered_map<int, std::vector<int>> restlogicalor_rule = {
        {RPAREN, restlogicalor_},
        {SEMICOLON, restlogicalor_},
        {COLON, restlogicalor_},
        {RBRACKET, restlogicalor_},
        {OP_BITWISE_OR, restlogicalor_},
        {OP_BITWISE_AND, restlogicalor_},
        {OP_LOGICAL_AND, restlogicalor_},
        {OP_LOGICAL_OR, restlogicalor_1},
        {OP_EQUAL, restlogicalor_},
        {OP_ASSIGN, restlogicalor_},
        {OP_NOTEQUAL, restlogicalor_},
        {OP_LESS, restlogicalor_},
        {OP_LESSEQUAL, restlogicalor_},
        {OP_GREATER, restlogicalor_},
        {OP_GREATEREQUAL, restlogicalor_},
        {OP_BITWISE_LSHIFT, restlogicalor_},
        {OP_BITWISE_RSHIFT, restlogicalor_},
        {OP_ADD, restlogicalor_},
        {OP_SUBTRACT, restlogicalor_},
        {OP_MULTIPLY, restlogicalor_},
        {OP_DIVIDE, restlogicalor_},
        {OP_MODULUS, restlogicalor_},
        {OP_BITWISE_OR, restlogicalor_1}};
    tabela.insert({NT_RESTLOGICALOR, restlogicalor_rule});

    std::vector<int> logicaland_ = {NT_BITWISEOR, NT_RESTLOGICALAND};
    std::unordered_map<int, std::vector<int>> logicaland_rule = {
        {IDENTIFIER, logicaland_},
        {KW_TRUE, logicaland_},
        {KW_FALSE, logicaland_},
        {KW_CHAR, logicaland_},
        {KW_FLOAT, logicaland_},
        {KW_INT, logicaland_},
        {KW_UNTYPED, logicaland_},
        {LPAREN, logicaland_},
        {INT, logicaland_},
        {FLOAT, logicaland_},
        {CHAR, logicaland_},
        {TRUE, logicaland_},
        {FALSE, logicaland_}};
    tabela.insert({NT_LOGICALAND, logicaland_rule});

    std::vector<int> restlogicaland_ = {EMPTY};
    std::vector<int> restlogicaland_1 = {OP_LOGICAL_AND, NT_BITWISEOR, NT_RESTLOGICALAND};
    std::unordered_map<int, std::vector<int>> restlogicaland_rule = {
        {RPAREN, restlogicaland_},
        {SEMICOLON, restlogicaland_},
        {COLON, restlogicaland_},
        {RBRACKET, restlogicaland_},
        {OP_BITWISE_OR, restlogicaland_},
        {OP_BITWISE_AND, restlogicaland_1},
        {OP_LOGICAL_AND, restlogicaland_1},
        {OP_LOGICAL_OR, restlogicaland_},
        {OP_EQUAL, restlogicaland_},
        {OP_ASSIGN, restlogicaland_},
        {OP_NOTEQUAL, restlogicaland_},
        {OP_LESS, restlogicaland_},
        {OP_LESSEQUAL, restlogicaland_},
        {OP_GREATER, restlogicaland_},
        {OP_GREATEREQUAL, restlogicaland_},
        {OP_BITWISE_LSHIFT, restlogicaland_},
        {OP_BITWISE_RSHIFT, restlogicaland_},
        {OP_ADD, restlogicaland_},
        {OP_SUBTRACT, restlogicaland_},
        {OP_MULTIPLY, restlogicaland_},
        {OP_DIVIDE, restlogicaland_},
        {OP_MODULUS, restlogicaland_},
        {OP_BITWISE_AND, restlogicaland_1},
        {OP_LOGICAL_AND, restlogicaland_1}};
    tabela.insert({NT_RESTLOGICALAND, restlogicaland_rule});

    std::vector<int> bitwiseor_ = {NT_BITWISEXOR, NT_RESTBITWISEOR};
    std::unordered_map<int, std::vector<int>> bitwiseor_rule = {
        {IDENTIFIER, bitwiseor_},
        {KW_TRUE, bitwiseor_},
        {KW_FALSE, bitwiseor_},
        {KW_CHAR, bitwiseor_},
        {KW_FLOAT, bitwiseor_},
        {KW_INT, bitwiseor_},
        {KW_UNTYPED, bitwiseor_},
        {LPAREN, bitwiseor_},
        {INT, bitwiseor_},
        {FLOAT, bitwiseor_},
        {CHAR, bitwiseor_},
        {TRUE, bitwiseor_},
        {FALSE, bitwiseor_}};
    tabela.insert({NT_BITWISEOR, bitwiseor_rule});

    std::vector<int> restbitwiseor_ = {EMPTY};
    std::vector<int> restbitwiseor_1 = {OP_BITWISE_OR, NT_BITWISEXOR, NT_RESTBITWISEOR};
    std::unordered_map<int, std::vector<int>> restbitwiseor_rule = {
        {RPAREN, restbitwiseor_},
        {SEMICOLON, restbitwiseor_},
        {COLON, restbitwiseor_},
        {RBRACKET, restbitwiseor_},
        {OP_BITWISE_OR, restbitwiseor_},
        {OP_LOGICAL_AND, restbitwiseor_},
        {OP_BITWISE_AND, restbitwiseor_},
        {OP_LOGICAL_OR, restbitwiseor_},
        {OP_EQUAL, restbitwiseor_},
        {OP_ASSIGN, restbitwiseor_},
        {OP_NOTEQUAL, restbitwiseor_},
        {OP_LESS, restbitwiseor_},
        {OP_LESSEQUAL, restbitwiseor_},
        {OP_GREATER, restbitwiseor_},
        {OP_GREATEREQUAL, restbitwiseor_},
        {OP_BITWISE_LSHIFT, restbitwiseor_},
        {OP_BITWISE_RSHIFT, restbitwiseor_},
        {OP_ADD, restbitwiseor_},
        {OP_SUBTRACT, restbitwiseor_},
        {OP_MULTIPLY, restbitwiseor_},
        {OP_DIVIDE, restbitwiseor_},
        {OP_MODULUS, restbitwiseor_},
        {OP_BITWISE_OR, restbitwiseor_1}};
    tabela.insert({NT_RESTBITWISEOR, restbitwiseor_rule});

    std::vector<int> bitwisexor_ = {NT_BITWISEAND, NT_RESTBITWISEXOR};
    std::unordered_map<int, std::vector<int>> bitwisexor_rule = {
        {IDENTIFIER, bitwisexor_},
        {KW_TRUE, bitwisexor_},
        {KW_FALSE, bitwisexor_},
        {KW_CHAR, bitwisexor_},
        {KW_FLOAT, bitwisexor_},
        {KW_INT, bitwisexor_},
        {KW_UNTYPED, bitwisexor_},
        {LPAREN, bitwisexor_},
        {INT, bitwisexor_},
        {FLOAT, bitwisexor_},
        {CHAR, bitwisexor_},
        {TRUE, bitwisexor_},
        {FALSE, bitwisexor_}};
    tabela.insert({NT_BITWISEXOR, bitwisexor_rule});

    std::vector<int> restbitwisexor_ = {EMPTY};
    std::vector<int> restbitwisexor_1 = {OP_BITWISE_XOR, NT_BITWISEAND, NT_RESTBITWISEXOR};
    std::unordered_map<int, std::vector<int>> restbitwisexor_rule = {
        {RPAREN, restbitwisexor_},
        {SEMICOLON, restbitwisexor_},
        {COLON, restbitwisexor_},
        {RBRACKET, restbitwisexor_},
        {OP_BITWISE_OR, restbitwisexor_},
        {OP_BITWISE_AND, restbitwisexor_},
        {OP_LOGICAL_AND, restbitwisexor_},
        {OP_LOGICAL_OR, restbitwisexor_},
        {OP_EQUAL, restbitwisexor_},
        {OP_ASSIGN, restbitwisexor_},
        {OP_NOTEQUAL, restbitwisexor_},
        {OP_LESS, restbitwisexor_},
        {OP_LESSEQUAL, restbitwisexor_},
        {OP_GREATER, restbitwisexor_},
        {OP_GREATEREQUAL, restbitwisexor_},
        {OP_BITWISE_LSHIFT, restbitwisexor_},
        {OP_BITWISE_RSHIFT, restbitwisexor_},
        {OP_ADD, restbitwisexor_},
        {OP_SUBTRACT, restbitwisexor_},
        {OP_MULTIPLY, restbitwisexor_},
        {OP_DIVIDE, restbitwisexor_},
        {OP_MODULUS, restbitwisexor_},
        {OP_BITWISE_XOR, restbitwisexor_1}};
    tabela.insert({NT_RESTBITWISEXOR, restbitwisexor_rule});

    std::vector<int> bitwiseand_ = {NT_EQUALITY, NT_RESTBITWISEAND};
    std::unordered_map<int, std::vector<int>> bitwiseand_rule = {
        {IDENTIFIER, bitwiseand_},
        {KW_TRUE, bitwiseand_},
        {KW_FALSE, bitwiseand_},
        {KW_CHAR, bitwiseand_},
        {KW_FLOAT, bitwiseand_},
        {KW_INT, bitwiseand_},
        {KW_UNTYPED, bitwiseand_},
        {LPAREN, bitwiseand_},
        {INT, bitwiseand_},
        {FLOAT, bitwiseand_},
        {CHAR, bitwiseand_},
        {TRUE, bitwiseand_},
        {FALSE, bitwiseand_}};
    tabela.insert({NT_BITWISEAND, bitwiseand_rule});

    std::vector<int> restbitwiseand_ = {EMPTY};
    std::vector<int> restbitwiseand_1 = {OP_BITWISE_AND, NT_EQUALITY, NT_RESTBITWISEAND};
    std::unordered_map<int, std::vector<int>> restbitwiseand_rule = {
        {RPAREN, restbitwiseand_},
        {SEMICOLON, restbitwiseand_},
        {COLON, restbitwiseand_},
        {RBRACKET, restbitwiseand_},
        {OP_BITWISE_OR, restbitwiseand_},
        {OP_LOGICAL_AND, restbitwiseand_},
        {OP_BITWISE_AND, restbitwiseand_},
        {OP_LOGICAL_OR, restbitwiseand_},
        {OP_EQUAL, restbitwiseand_},
        {OP_ASSIGN, restbitwiseand_},
        {OP_NOTEQUAL, restbitwiseand_},
        {OP_LESS, restbitwiseand_},
        {OP_LESSEQUAL, restbitwiseand_},
        {OP_GREATER, restbitwiseand_},
        {OP_GREATEREQUAL, restbitwiseand_},
        {OP_BITWISE_LSHIFT, restbitwiseand_},
        {OP_BITWISE_RSHIFT, restbitwiseand_},
        {OP_ADD, restbitwiseand_},
        {OP_SUBTRACT, restbitwiseand_},
        {OP_MULTIPLY, restbitwiseand_},
        {OP_DIVIDE, restbitwiseand_},
        {OP_MODULUS, restbitwiseand_},
        {OP_BITWISE_AND, restbitwiseand_1}};
    tabela.insert({NT_RESTBITWISEAND, restbitwiseand_rule});

    std::vector<int> equality_ = {NT_RELATION, NT_RESTEQUALITY};
    std::unordered_map<int, std::vector<int>> equality_rule = {
        {IDENTIFIER, equality_},
        {KW_TRUE, equality_},
        {KW_FALSE, equality_},
        {KW_CHAR, equality_},
        {KW_FLOAT, equality_},
        {KW_INT, equality_},
        {KW_UNTYPED, equality_},
        {LPAREN, equality_},
        {INT, equality_},
        {FLOAT, equality_},
        {CHAR, equality_},
        {TRUE, equality_},
        {FALSE, equality_}};
    tabela.insert({NT_EQUALITY, equality_rule});

    std::vector<int> restequality_ = {EMPTY};
    std::vector<int> restequality_1 = {NT_EQUALITYOPERATOR, NT_RELATION, NT_RESTEQUALITY};
    std::unordered_map<int, std::vector<int>> restequality_rule = {
        {RPAREN, restequality_},
        {SEMICOLON, restequality_},
        {COLON, restequality_},
        {RBRACKET, restequality_},
        {OP_BITWISE_OR, restequality_},
        {OP_LOGICAL_AND, restequality_},
        {OP_BITWISE_AND, restequality_},
        {OP_LOGICAL_OR, restequality_},
        {OP_EQUAL, restequality_1},
        {OP_ASSIGN, restequality_},
        {OP_NOTEQUAL, restequality_},
        {OP_LESS, restequality_},
        {OP_LESSEQUAL, restequality_},
        {OP_GREATER, restequality_},
        {OP_GREATEREQUAL, restequality_},
        {OP_BITWISE_LSHIFT, restequality_},
        {OP_BITWISE_RSHIFT, restequality_},
        {OP_ADD, restequality_},
        {OP_SUBTRACT, restequality_},
        {OP_MULTIPLY, restequality_},
        {OP_DIVIDE, restequality_},
        {OP_MODULUS, restequality_},
        {OP_NOTEQUAL, restequality_1}};
    tabela.insert({NT_RESTEQUALITY, restequality_rule});

    std::vector<int> equalityoperator_ = {OP_EQUAL};
    std::vector<int> equalityoperator_1 = {OP_NOTEQUAL};
    std::unordered_map<int, std::vector<int>> equalityoperator_rule = {
        {OP_EQUAL, equalityoperator_},
        {OP_NOTEQUAL, equalityoperator_1}};
    tabela.insert({NT_EQUALITYOPERATOR, equalityoperator_rule});

    std::vector<int> relation_ = {NT_SHIFT, NT_RESTRELATION};
    std::unordered_map<int, std::vector<int>> relation_rule = {
        {IDENTIFIER, relation_},
        {KW_TRUE, relation_},
        {KW_FALSE, relation_},
        {KW_CHAR, relation_},
        {KW_FLOAT, relation_},
        {KW_INT, relation_},
        {KW_UNTYPED, relation_},
        {LPAREN, relation_},
        {INT, relation_},
        {FLOAT, relation_},
        {CHAR, relation_},
        {TRUE, relation_},
        {FALSE, relation_}};
    tabela.insert({NT_RELATION, relation_rule});

    std::vector<int> restrelation_ = {EMPTY};
    std::vector<int> restrelation_1 = {NT_RELATIONOPERATOR, NT_SHIFT, NT_RESTRELATION};
    std::unordered_map<int, std::vector<int>> restrelation_rule = {
        {RPAREN, restrelation_},
        {SEMICOLON, restrelation_},
        {COLON, restrelation_},
        {RBRACKET, restrelation_},
        {OP_BITWISE_OR, restrelation_},
        {OP_LOGICAL_AND, restrelation_},
        {OP_BITWISE_AND, restrelation_},
        {OP_LOGICAL_OR, restrelation_},
        {OP_EQUAL, restrelation_},
        {OP_ASSIGN, restrelation_},
        {OP_NOTEQUAL, restrelation_},
        {OP_LESS, restrelation_1},
        {OP_LESSEQUAL, restrelation_1},
        {OP_GREATER, restrelation_1},
        {OP_GREATEREQUAL, restrelation_1},
        {OP_BITWISE_LSHIFT, restrelation_},
        {OP_BITWISE_RSHIFT, restrelation_},
        {OP_ADD, restrelation_},
        {OP_SUBTRACT, restrelation_},
        {OP_MULTIPLY, restrelation_},
        {OP_DIVIDE, restrelation_},
        {OP_MODULUS, restrelation_},
        {OP_LESS, restrelation_1},
        {OP_LESSEQUAL, restrelation_1},
        {OP_GREATER, restrelation_1},
        {OP_GREATEREQUAL, restrelation_1}};
    tabela.insert({NT_RESTRELATION, restrelation_rule});

    std::vector<int> relationoperator_ = {OP_LESS};
    std::vector<int> relationoperator_1 = {OP_LESSEQUAL};
    std::vector<int> relationoperator_2 = {OP_GREATER};
    std::vector<int> relationoperator_3 = {OP_GREATEREQUAL};
    std::unordered_map<int, std::vector<int>> relationoperator_rule = {
        {OP_LESS, relationoperator_},
        {OP_LESSEQUAL, relationoperator_1},
        {OP_GREATER, relationoperator_2},
        {OP_GREATEREQUAL, relationoperator_3}};
    tabela.insert({NT_RELATIONOPERATOR, relationoperator_rule});

    std::vector<int> shift_ = {NT_ADDITION, NT_RESTSHIFT};
    std::unordered_map<int, std::vector<int>> shift_rule = {
        {IDENTIFIER, shift_},
        {KW_TRUE, shift_},
        {KW_FALSE, shift_},
        {KW_CHAR, shift_},
        {KW_FLOAT, shift_},
        {KW_INT, shift_},
        {KW_UNTYPED, shift_},
        {LPAREN, shift_},
        {INT, shift_},
        {FLOAT, shift_},
        {CHAR, shift_},
        {TRUE, shift_},
        {FALSE, shift_},
        {OP_ASSIGN, shift_},
        {SEMICOLON, shift_}};
    tabela.insert({NT_SHIFT, shift_rule});

    std::vector<int> restshift_ = {EMPTY};
    std::vector<int> restshift_1 = {NT_SHIFTOPERATOR, NT_ADDITION, NT_RESTSHIFT};
    std::unordered_map<int, std::vector<int>> restshift_rule = {
        {RPAREN, restshift_},
        {SEMICOLON, restshift_},
        {COLON, restshift_},
        {RBRACKET, restshift_},
        {OP_BITWISE_OR, restshift_},
        {OP_LOGICAL_AND, restshift_},
        {OP_BITWISE_AND, restshift_},
        {OP_LOGICAL_OR, restshift_},
        {OP_EQUAL, restshift_},
        {OP_NOTEQUAL, restshift_},
        {OP_LESS, restshift_},
        {OP_LESSEQUAL, restshift_},
        {OP_GREATER, restshift_},
        {OP_GREATEREQUAL, restshift_},
        {OP_BITWISE_LSHIFT, restshift_},
        {OP_BITWISE_RSHIFT, restshift_},
        {OP_ADD, restshift_},
        {OP_SUBTRACT, restshift_},
        {OP_MULTIPLY, restshift_},
        {OP_DIVIDE, restshift_},
        {OP_MODULUS, restshift_},
        {OP_BITWISE_LSHIFT, restshift_1},
        {OP_BITWISE_RSHIFT, restshift_1},
        {OP_ASSIGN, restshift_}};
    tabela.insert({NT_RESTSHIFT, restshift_rule});

    std::vector<int> shiftoperator_ = {OP_BITWISE_LSHIFT};
    std::vector<int> shiftoperator_1 = {OP_BITWISE_RSHIFT};
    std::unordered_map<int, std::vector<int>> shiftoperator_rule = {
        {OP_BITWISE_LSHIFT, shiftoperator_},
        {OP_BITWISE_RSHIFT, shiftoperator_1}};
    tabela.insert({NT_SHIFTOPERATOR, shiftoperator_rule});

    std::vector<int> addition_ = {NT_MULTIPLICATION, NT_RESTADDITION};
    std::unordered_map<int, std::vector<int>> addition_rule = {
        {IDENTIFIER, addition_},
        {KW_TRUE, addition_},
        {KW_FALSE, addition_},
        {KW_CHAR, addition_},
        {KW_FLOAT, addition_},
        {KW_INT, addition_},
        {KW_UNTYPED, addition_},
        {LPAREN, addition_},
        {INT, addition_},
        {FLOAT, addition_},
        {CHAR, addition_},
        {TRUE, addition_},
        {FALSE, addition_},
        {SEMICOLON, addition_}};
    tabela.insert({NT_ADDITION, addition_rule});

    std::vector<int> restaddition_ = {EMPTY};
    std::vector<int> restaddition_1 = {NT_ADDITIONOPERATOR, NT_MULTIPLICATION, NT_RESTADDITION};
    std::unordered_map<int, std::vector<int>> restaddition_rule = {
        {RPAREN, restaddition_},
        {SEMICOLON, restaddition_},
        {COLON, restaddition_},
        {RBRACKET, restaddition_},
        {OP_BITWISE_OR, restaddition_},
        {OP_BITWISE_AND, restaddition_},
        {OP_LOGICAL_AND, restaddition_},
        {OP_LOGICAL_OR, restaddition_},
        {OP_EQUAL, restaddition_},
        {OP_NOTEQUAL, restaddition_},
        {OP_LESS, restaddition_},
        {OP_LESSEQUAL, restaddition_},
        {OP_GREATER, restaddition_},
        {OP_GREATEREQUAL, restaddition_},
        {OP_BITWISE_LSHIFT, restaddition_},
        {OP_BITWISE_RSHIFT, restaddition_},
        {OP_ADD, restaddition_1},
        {OP_SUBTRACT, restaddition_1},
        {OP_MULTIPLY, restaddition_},
        {OP_DIVIDE, restaddition_},
        {OP_MODULUS, restaddition_},
        {OP_ADD, restaddition_1},
        {OP_SUBTRACT, restaddition_1},
        {OP_ASSIGN, restaddition_}};
    tabela.insert({NT_RESTADDITION, restaddition_rule});

    std::vector<int> additionoperator_ = {OP_ADD};
    std::vector<int> additionoperator_1 = {OP_SUBTRACT};
    std::unordered_map<int, std::vector<int>> additionoperator_rule = {
        {OP_ADD, additionoperator_},
        {OP_SUBTRACT, additionoperator_1}};
    tabela.insert({NT_ADDITIONOPERATOR, additionoperator_rule});

    std::vector<int> multiplication_ = {NT_UNARY3, NT_RESTMULTIPLICATION};
    std::unordered_map<int, std::vector<int>> multiplication_rule = {
        {IDENTIFIER, multiplication_},
        {KW_TRUE, multiplication_},
        {KW_FALSE, multiplication_},
        {KW_CHAR, multiplication_},
        {KW_FLOAT, multiplication_},
        {KW_INT, multiplication_},
        {KW_UNTYPED, multiplication_},
        {LPAREN, multiplication_},
        {INT, multiplication_},
        {FLOAT, multiplication_},
        {CHAR, multiplication_},
        {TRUE, multiplication_},
        {FALSE, multiplication_},
        {SEMICOLON, multiplication_}};
    tabela.insert({NT_MULTIPLICATION, multiplication_rule});

    std::vector<int> restmultiplication_ = {EMPTY};
    std::vector<int> restmultiplication_1 = {NT_MULTIPLICATIONOPERATOR, NT_UNARY3, NT_RESTMULTIPLICATION};
    std::unordered_map<int, std::vector<int>> restmultiplication_rule = {
        {RPAREN, restmultiplication_},
        {SEMICOLON, restmultiplication_},
        {COLON, restmultiplication_},
        {RBRACKET, restmultiplication_},
        {OP_BITWISE_OR, restmultiplication_},
        {OP_BITWISE_AND, restmultiplication_},
        {OP_LOGICAL_AND, restmultiplication_},
        {OP_LOGICAL_OR, restmultiplication_},
        {OP_EQUAL, restmultiplication_},
        {OP_NOTEQUAL, restmultiplication_},
        {OP_LESS, restmultiplication_},
        {OP_LESSEQUAL, restmultiplication_},
        {OP_GREATER, restmultiplication_},
        {OP_GREATEREQUAL, restmultiplication_},
        {OP_BITWISE_LSHIFT, restmultiplication_},
        {OP_BITWISE_RSHIFT, restmultiplication_},
        {OP_ADD, restmultiplication_},
        {OP_SUBTRACT, restmultiplication_},
        {OP_MULTIPLY, restmultiplication_1},
        {OP_DIVIDE, restmultiplication_1},
        {OP_MODULUS, restmultiplication_1},
        {OP_DIVIDE, restmultiplication_1},
        {OP_ASSIGN, restmultiplication_}};
    tabela.insert({NT_RESTMULTIPLICATION, restmultiplication_rule});

    std::vector<int> multiplicationoperator_ = {OP_MULTIPLY};
    std::vector<int> multiplicationoperator_1 = {OP_DIVIDE};
    std::vector<int> multiplicationoperator_2 = {OP_MODULUS};
    std::unordered_map<int, std::vector<int>> multiplicationoperator_rule = {
        {OP_MULTIPLY, multiplicationoperator_},
        {OP_DIVIDE, multiplicationoperator_1},
        {OP_MODULUS, multiplicationoperator_2}};
    tabela.insert({NT_MULTIPLICATIONOPERATOR, multiplicationoperator_rule});

    std::vector<int> unary3_ = {NT_UNARY2};
    std::vector<int> unary3_1 = {NT_UNARY3OPERATOR, NT_UNARY2};
    std::unordered_map<int, std::vector<int>> unary3_rule = {
        {IDENTIFIER, unary3_},
        {KW_TRUE, unary3_},
        {KW_FALSE, unary3_},
        {KW_CHAR, unary3_},
        {KW_FLOAT, unary3_},
        {KW_INT, unary3_},
        {KW_UNTYPED, unary3_},
        {LPAREN, unary3_},
        {OP_BITWISE_AND, unary3_1},
        {OP_MULTIPLY, unary3_1},
        {OP_SUBTRACT, unary3_1},
        {INT, unary3_},
        {FLOAT, unary3_},
        {CHAR, unary3_},
        {TRUE, unary3_},
        {FALSE, unary3_},
        {SEMICOLON, unary3_}};
    tabela.insert({NT_UNARY3, unary3_rule});

    std::vector<int> unary3operator_ = {OP_BITWISE_AND};
    std::vector<int> unary3operator_1 = {OP_MULTIPLY};
    std::vector<int> unary3operator_2 = {OP_SUBTRACT};
    std::unordered_map<int, std::vector<int>> unary3operator_rule = {
        {OP_BITWISE_AND, unary3operator_},
        {OP_MULTIPLY, unary3operator_1},
        {OP_SUBTRACT, unary3operator_2}};
    tabela.insert({NT_UNARY3OPERATOR, unary3operator_rule});

    std::vector<int> unary2_ = {NT_FACTOR};
    std::vector<int> unary2_1 = {NT_UNARY2OPERATOR, NT_FACTOR};
    std::unordered_map<int, std::vector<int>> unary2_rule = {
        {IDENTIFIER, unary2_},
        {KW_TRUE, unary2_},
        {KW_FALSE, unary2_},
        {KW_CHAR, unary2_},
        {KW_FLOAT, unary2_},
        {KW_INT, unary2_},
        {KW_UNTYPED, unary2_},
        {LPAREN, unary2_},
        {OP_ADD, unary2_1},
        {OP_SUBTRACT, unary2_1},
        {OP_NOT, unary2_1},
        {INT, unary2_},
        {FLOAT, unary2_},
        {CHAR, unary2_},
        {TRUE, unary2_},
        {FALSE, unary2_},
        {SEMICOLON, unary2_}};
    tabela.insert({NT_UNARY2, unary2_rule});

    std::vector<int> unary2operator_ = {OP_ADD};
    std::vector<int> unary2operator_1 = {OP_SUBTRACT};
    std::vector<int> unary2operator_2 = {OP_NOT};
    std::unordered_map<int, std::vector<int>> unary2operator_rule = {
        {OP_ADD, unary2operator_},
        {OP_SUBTRACT, unary2operator_1},
        {OP_NOT, unary2operator_2}};
    tabela.insert({NT_UNARY2OPERATOR, unary2operator_rule});

    std::vector<int> factor_ = {IDENTIFIER, NT_APPLICATION};
    std::vector<int> factor_1 = {NT_IMMEDIATE};
    std::vector<int> factor_2 = {LPAREN, NT_EXPRESSION, RPAREN};
    std::vector<int> factor_3 = {NT_TYPE, NT_FACTORCOND};
    std::unordered_map<int, std::vector<int>> factor_rule = {
        {IDENTIFIER, factor_},
        {KW_TRUE, factor_3},
        {KW_FALSE, factor_3},
        {KW_CHAR, factor_3},
        {KW_FLOAT, factor_3},
        {KW_INT, factor_3},
        {KW_UNTYPED, factor_3},
        {LPAREN, factor_2},
        {INT, factor_1},
        {FLOAT, factor_1},
        {CHAR, factor_1},
        {TRUE, factor_1},
        {FALSE, factor_1},
        {SEMICOLON, factor_1}};
    tabela.insert({NT_FACTOR, factor_rule});

    std::vector<int> factorcond_ = {EMPTY};
    std::vector<int> factorcond_1 = {IDENTIFIER, NT_APPLICATION, SEMICOLON};
    std::unordered_map<int, std::vector<int>> factorcond__rule = {
        {KW_FALSE, factorcond_},
        {SEMICOLON, factorcond_},
        {KW_TRUE, factorcond_},
        {IDENTIFIER, factorcond_1}
    };
    tabela.insert({NT_FACTORCOND, factorcond__rule});

    std::vector<int> application_ = {EMPTY};
    std::vector<int> application_1 = {LBRACKET, NT_EXPRESSION, RBRACKET, NT_APPLICATION};
    std::vector<int> application_2 = {LPAREN, NT_EXPRESSION, NT_MOREEXPRESSION, RPAREN};
    std::unordered_map<int, std::vector<int>> application_rule = {
        {RPAREN, application_},
        {SEMICOLON, application_},
        {COLON, application_},
        {RBRACKET, application_},
        {OP_ASSIGN, application_},
        {OP_BITWISE_OR, application_},
        {OP_BITWISE_AND, application_},
        {OP_LOGICAL_AND, application_},
        {OP_EQUAL, application_},
        {OP_NOTEQUAL, application_},
        {OP_LESS, application_},
        {OP_LESSEQUAL, application_},
        {OP_GREATER, application_},
        {OP_GREATEREQUAL, application_},
        {OP_BITWISE_LSHIFT, application_},
        {OP_BITWISE_RSHIFT, application_},
        {OP_ADD, application_},
        {OP_SUBTRACT, application_},
        {OP_MULTIPLY, application_},
        {OP_DIVIDE, application_},
        {OP_MODULUS, application_},
        {RBRACKET, application_},
        {LBRACKET, application_1},
        {LPAREN, application_2}};
    tabela.insert({NT_APPLICATION, application_rule});

    std::vector<int> moreexpression_ = {EMPTY};
    std::vector<int> moreexpression_1 = {COLON, NT_EXPRESSION, NT_MOREEXPRESSION};
    std::unordered_map<int, std::vector<int>> moreexpression_rule = {
        {RPAREN, moreexpression_},
        {COLON, moreexpression_1}};
    tabela.insert({NT_MOREEXPRESSION, moreexpression_rule});

    std::vector<int> type_0 = {EMPTY};
    std::vector<int> type_ = {KW_BOOL};
    std::vector<int> type_1 = {KW_CHAR};
    std::vector<int> type_2 = {KW_FLOAT};
    std::vector<int> type_3 = {KW_INT};
    std::vector<int> type_4 = {KW_UNTYPED};
    std::vector<int> type_5 = {KW_VOID};
    std::vector<int> type_6 = {KW_TRUE};
    std::vector<int> type_7 = {KW_FALSE};
    std::unordered_map<int, std::vector<int>> type_rule = {
        {KW_BOOL, type_},
        {KW_TRUE, type_6},
        {KW_FALSE, type_7},
        {KW_CHAR, type_1},
        {KW_FLOAT, type_2},
        {KW_INT, type_3},
        {KW_UNTYPED, type_4},
        {KW_VOID, type_5},
        {IDENTIFIER, type_0}};
    tabela.insert({NT_TYPE, type_rule});

    std::vector<int> immediate_0 = {EMPTY};
    std::vector<int> immediate_ = {TRUE};
    std::vector<int> immediate_1 = {FALSE};
    std::vector<int> immediate_2 = {CHAR};
    std::vector<int> immediate_3 = {FLOAT};
    std::vector<int> immediate_4 = {INT};
    std::vector<int> immediate_5 = {STRING};
    std::unordered_map<int, std::vector<int>> immediate_rule = {
        {TRUE, immediate_},
        {FALSE, immediate_1},
        {CHAR, immediate_2},
        {FLOAT, immediate_3},
        {INT, immediate_4},
        {STRING, immediate_5},
        {SEMICOLON, immediate_0}};
    tabela.insert({NT_IMMEDIATE, immediate_rule});

    std::stack<int> order;

    int next = yylex();
    int error = 0;

    auto lin_ = tabela.at(NT_MODULE);
    auto col_ = lin_.at(KW_MODULE);
    size_t sz = col_.size();
    std::cout << "sz = " << sz << "\n";

    for(int i = sz-1; i >= 0 ; i--){
        order.push(col_[i]);
        std::cout << col_[i] << std::endl;
    }

    std::cout << "Passou - " << next << "\n";

    while (!order.empty() and next != EOI)
    {

        int top = order.top();


        if(top != EMPTY){
            // se o topo da pilha for um terminal
            if (top >= 300 && top < 500)
            {
                // se casa com a entrada
                if (top == next)
                {
                    // desempilha
                    order.pop();
                    // avanca
                    next = yylex();
                    // order.push(next);
                }
                else
                {
                    std::cout << top << " !================ " << next << "\n";

                    // caso contrario erro
                    std::cout << "TERMINAL NÃO RECONHECIDO\n";
                    break;
                }
            }
            else
            {
                std::cout << "Analisando - Top = " << top << " - Next = " << next << "\n";

                // troca o topo da pilha pela lista em tabela(top(), entrada)
                auto linha_ = tabela.at(top);
                auto coluna_ = linha_.at(next);

                order.pop();
                int sz_col = coluna_.size();
                // lendo de trás para frente
                for (int i = sz_col - 1; i >= 0; i--)
                {
                    // adicionando a fila
                    order.push(coluna_[i]);
                }
            }
    
        } else{
            order.pop();
        }
        std::cout << "Passou - " << next << " - TOP = " << top << "\n";
    }

    return 0;
}