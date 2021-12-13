#include "lex.yy.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stack>

int main(){

    // linhas = não terminais | colunas = terminais
    std::unordered_map<int, std::unordered_map<int, std::vector<int>>> tabela;
    
    // REGRA MODULE (INVERTER A LISTA)
    std::vector<int> module_ = {KW_MODULE, IDENTIFIER, SEMICOLON, NT_GLOBALS };
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
    globals_rule.insert({EOI, globals_ });
    globals_rule.insert({T_BOOL, globals_1 });
    globals_rule.insert({T_CHAR, globals_1 });
    globals_rule.insert({T_FLOAT, globals_1 });
    globals_rule.insert({T_INT, globals_1 });
    globals_rule.insert({T_UNTYPE, globals_1 });
    globals_rule.insert({KW_START, globals_1 });
    globals_rule.insert({IDENTIFIER, globals_1 });
    globals_rule.insert({COLON, globals_1 });
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
        {T_BOOL, global_1},
        {T_CHAR, global_1},
        {T_FLOAT, global_1},
        {T_INT, global_1},
        {T_UNTYPE, global_1},
        
        {T_BOOL, global_},
        {T_CHAR, global_},
        {T_FLOAT, global_},
        {T_INT, global_},
        {T_UNTYPE, global_},
        {EOI, global_},
        {KW_START, global_},
        {IDENTIFIER, global_},
        {SEMICOLON, global_},
        {LBRACE, global_},
        {NT_DECLARATIONBLOCK, global_1}
    };
    tabela.insert({NT_GLOBAL, global_rule});

    std::vector<int> function_ = {NT_FUNCTIONHEADER, NT_FUNCTIONREST};
    std::unordered_map<int, std::vector<int>> function_rule = {
        {NT_FUNCTIONHEADER, function_}
    };
    tabela.insert({NT_FUNCTION, function_rule});

    std::vector<int> functionheader_ = {NT_MODIFIERS, IDENTIFIER, COLON, NT_PARAMLIST, ARROW, NT_RETURNTYPE};
    std::unordered_map<int, std::vector<int>> functionheader_rule = {
        {NT_MODIFIERS, functionheader_}
    };
    tabela.insert({NT_FUNCTIONHEADER, functionheader_rule});
    

    std::vector<int> functionrest_ = {SEMICOLON};
    std::vector<int> functionrest_1 = {NT_BLOCK};
    std::unordered_map<int, std::vector<int>> functionrest_rule = {
        {SEMICOLON, functionrest_},
        {NT_BLOCK, functionrest_1}
    };
    tabela.insert({NT_FUNCTIONREST, functionrest_rule});
    

    std::vector<int> modifiers_ = {KW_START};
    std::vector<int> modifiers_1 = {KW_START};
    std::unordered_map<int, std::vector<int>> modifiers_rule = {{KW_START, modifiers_}};
    tabela.insert({NT_MODIFIERS ,modifiers_rule});

    std::vector<int> paramlist_ = {KW_VOID};
    std::vector<int> paramlist_1 = {NT_PARAMBLOCK, NT_MOREPARAMBLOCK};
    std::unordered_map<int, std::vector<int>> paramlist_rule = {
        {KW_VOID, paramlist_},
        {NT_PARAMBLOCK, paramlist_1}
    };
    tabela.insert({NT_PARAMLIST, paramlist_rule});

    std::vector<int> moreparamblock_ = {SEMICOLON, NT_PARAMBLOCK, NT_MOREPARAMBLOCK};
    std::unordered_map<int, std::vector<int>> moreparamblock_rule = {
        {SEMICOLON, moreparamblock_}
    };
    tabela.insert({NT_MOREPARAMBLOCK, moreparamblock_rule});

    std::vector<int> paramblock_ = {NT_TYPE, NT_PARAM, NT_MOREPARAM};
    std::unordered_map<int, std::vector<int>> paramblock_rule = {
        {NT_TYPE, paramblock_}
    };
    tabela.insert({NT_PARAMBLOCK, paramblock_rule});

    std::vector<int> moreparam_ = {COLON, NT_PARAM, NT_MOREPARAM};
    std::unordered_map<int, std::vector<int>> moreparam_rule = {
        {COLON, moreparam_}
    };
    tabela.insert({NT_MOREPARAM, moreparam_rule});

    std::vector<int> param_ = {NT_REFERENCE, IDENTIFIER, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> param_rule = {
        {NT_REFERENCE, param_}
    };
    tabela.insert({NT_PARAM, param_rule});

    std::vector<int> returntype_ = {NT_TYPE, NT_REFERENCE, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> returntype_rule = {
        {NT_TYPE, returntype_}
    };
    tabela.insert({NT_RETURNTYPE, returntype_rule});

    std::vector<int> reference_ = {OP_MULTIPLY, NT_REFERENCE};
    std::unordered_map<int, std::vector<int>> reference_rule = {
        {OP_MULTIPLY, reference_}
    };
    tabela.insert({NT_REFERENCE, reference_rule});

    std::vector<int> dimensionblock_ = {LBRACKET, RBRACKET, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> dimensionblock_rule = {
        {LBRACKET, dimensionblock_}
    };
    tabela.insert({LBRACKET, dimensionblock_rule});

    std::vector<int> block_ = {LBRACE, NT_CODE, RBRACE};
    std::unordered_map<int, std::vector<int>> block_rule = {
        {LBRACE, block_}
    };
    tabela.insert({NT_BLOCK, block_rule});

    std::vector<int> code_ = {NT_BLOCK, NT_CODE};
    std::vector<int> code_1 = {NT_STATEMENT, NT_CODE};
    std::unordered_map<int, std::vector<int>> code_rule = {
        {NT_BLOCK, code_},
        {NT_STATEMENT, code_1}
    };
    tabela.insert({NT_CODE, code_rule});

    std::vector<int> statement_ = {KW_LABEL, IDENTIFIER};
    std::vector<int> statement_1 = {SEMICOLON};
    std::vector<int> statement_2 = {KW_BREAK, SEMICOLON};
    std::vector<int> statement_3 = {KW_CONTINUE, SEMICOLON};
    std::vector<int> statement_4 = {KW_IF, LPAREN, NT_EXPRESSION, RPAREN, NT_BLOCK, NT_elseBLOCK};
    std::vector<int> statement_5 = {GOTO, IDENTIFIER, SEMICOLON};
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
        {GOTO, statement_5},
        {KW_WHILE, statement_6},
        {DO, statement_7},
        {KW_SWITCH, statement_8},
        {KW_RETURN, statement_9},
        {NT_EXPRESSION, statement_10},
        {NT_DECLARATIONBLOCK, statement_11}
    };
    tabela.insert({NT_STATEMENT, statement_rule});

    std::vector<int> elseBlock_ = {KW_ELSE, NT_BLOCK};
    std::unordered_map<int, std::vector<int>> elseBlock_rule = {
        {KW_ELSE, elseBlock_}
    };
    tabela.insert({NT_elseBLOCK, elseBlock_rule});

    std::vector<int> switchcase_ = {KW_CASE, INT, NT_BLOCK};
    std::unordered_map<int, std::vector<int>> switchcase_rule = {
        {KW_CASE, switchcase_}
    };
    tabela.insert({NT_SWITCHCASES, switchcase_rule});

    std::vector<int> declarationblock_ = {NT_TYPE, NT_DECLARATION, NT_RESTDECLARATION};
    std::unordered_map<int, std::vector<int>> _rule = {
        {}
    };
    // tabela.insert({, _rule});


    std::vector<int> _ = {};
    std::unordered_map<int, std::vector<int>> _rule = {
        {}
    };
    tabela.insert({, _rule});

    std::stack<int> order;

    int next = yylex();
    int error = 0;

    order.push(next);

    while(!order.empty()){

        int top = order.top();

        if(top > 349){
            if(top == next){
                order.pop();
                next = yylex();
            } else{
                std::cout << "TERMINAL NÃO RECONHECIDO\n";
                break;
            }
        } else{
            
        }

    }


    return 0;
}