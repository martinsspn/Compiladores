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
    globals_rule.insert({SEMICOLON, globals_1 });
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

        {T_BOOL, global_1},
        {T_CHAR, global_1},
        {T_FLOAT, global_1},
        {T_INT, global_1},
        {T_UNTYPE, global_1},
    };
    tabela.insert({NT_GLOBAL, global_rule});

    std::vector<int> function_ = {NT_FUNCTIONHEADER, NT_FUNCTIONREST};
    std::unordered_map<int, std::vector<int>> function_rule = {
        {EOI, function_},
        {KW_EXTERN, function_},
        {T_BOOL, function_},
        {T_CHAR, function_},
        {T_FLOAT, function_},
        {T_INT, function_},
        {T_UNTYPE, function_},
        {KW_START, function_},
        {IDENTIFIER, function_},
        {SEMICOLON, function_},
        {LBRACE, function_}
    };
    tabela.insert({NT_FUNCTION, function_rule});

    std::vector<int> functionheader_ = {NT_MODIFIERS, IDENTIFIER, COLON, NT_PARAMLIST, ARROW, NT_RETURNTYPE};
    std::unordered_map<int, std::vector<int>> functionheader_rule = {
        {SEMICOLON, functionheader_},
        {KW_START, functionheader_},
        {LBRACE, functionheader_}
    };
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
        {KW_START, modifiers_1}
    };
    tabela.insert({NT_MODIFIERS ,modifiers_rule});

    std::vector<int> paramlist_ = {KW_VOID};
    std::vector<int> paramlist_1 = {NT_PARAMBLOCK, NT_MOREPARAMBLOCK};
    std::unordered_map<int, std::vector<int>> paramlist_rule = {
        {KW_VOID, paramlist_},
        {T_BOOL, paramlist_1},
        {T_CHAR, paramlist_1},
        {T_FLOAT, paramlist_1},
        {T_INT, paramlist_1},
        {T_UNTYPE, paramlist_1}
    };
    tabela.insert({NT_PARAMLIST, paramlist_rule});

    std::vector<int> moreparamblock_ = {EMPTY};
    std::vector<int> moreparamblock_1 = {SEMICOLON, NT_PARAMBLOCK, NT_MOREPARAMBLOCK};
    std::unordered_map<int, std::vector<int>> moreparamblock_rule = {
        {ARROW, moreparamblock_},
        {SEMICOLON, moreparamblock_1}
    };
    tabela.insert({NT_MOREPARAMBLOCK, moreparamblock_rule});

    std::vector<int> paramblock_ = {NT_TYPE, NT_PARAM, NT_MOREPARAM};
    std::unordered_map<int, std::vector<int>> paramblock_rule = {
        {T_BOOL, paramblock_},
        {T_CHAR, paramblock_},
        {T_FLOAT, paramblock_},
        {T_INT, paramblock_},
        {T_UNTYPE, paramblock_}
    };
    tabela.insert({NT_PARAMBLOCK, paramblock_rule});

    std::vector<int> moreparam_ = {EMPTY};
    std::vector<int> moreparam_1 = {COLON, NT_PARAM, NT_MOREPARAM};
    std::unordered_map<int, std::vector<int>> moreparam_rule = {
        {ARROW, moreparam_},
        {SEMICOLON, moreparam_},
        
        {COLON, moreparam_1}
    };
    tabela.insert({NT_MOREPARAM, moreparam_rule});

    std::vector<int> param_ = {EMPTY};
    std::vector<int> param_1 = {NT_REFERENCE, IDENTIFIER, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> param_rule = {
        {ARROW, param_},
        {SEMICOLON, param_},
        {COLON, param_},

        {OP_MULTIPLY, param_1}
    };
    tabela.insert({NT_PARAM, param_rule});

    std::vector<int> returntype_ = {NT_TYPE, NT_REFERENCE, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> returntype_rule = {
        {T_BOOL, returntype_},
        {T_CHAR, returntype_},
        {T_FLOAT, returntype_},
        {T_INT, returntype_},
        {T_UNTYPE, returntype_}
    };
    tabela.insert({NT_RETURNTYPE, returntype_rule});

    std::vector<int> reference_ = {EMPTY};
    std::vector<int> reference_1 = {OP_MULTIPLY, NT_REFERENCE};
    std::unordered_map<int, std::vector<int>> reference_rule = {
        {IDENTIFIER, reference_},
        {SEMICOLON, reference_},
        {LBRACE, reference_},
        {LBRACKET, reference_},
        
        {OP_MULTIPLY, reference_1}
    };
    tabela.insert({NT_REFERENCE, reference_rule});

    std::vector<int> dimensionblock_ = {EMPTY};
    std::vector<int> dimensionblock_1 = {LBRACKET, RBRACKET, NT_DIMENSIONBLOCK};
    std::unordered_map<int, std::vector<int>> dimensionblock_rule = {
        {ARROW, dimensionblock_},
        {SEMICOLON, dimensionblock_},
        {COLON, dimensionblock_},
        {LBRACE, dimensionblock_},

        {LBRACKET, dimensionblock_1}
    };
    tabela.insert({LBRACKET, dimensionblock_rule});

    std::vector<int> block_ = {LBRACE, NT_CODE, RBRACE};
    std::unordered_map<int, std::vector<int>> block_rule = {
        {LBRACE, block_}
    };
    tabela.insert({NT_BLOCK, block_rule});

    std::vector<int> code_ = {EMPTY};
    std::vector<int> code_1 = {NT_BLOCK, NT_CODE};
    std::vector<int> code_2 = {NT_STATEMENT, NT_CODE};
    std::unordered_map<int, std::vector<int>> code_rule = {
        {RBRACE, code_},

        {LBRACE, code_1},
        
        {KW_LABEL, code_2},
        {SEMICOLON, code_2},
        {KW_BREAK, code_2},
        {KW_CONTINUE, code_2},
        {KW_IF, code_2},
        {GOTO, code_2},
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
        {T_CHAR, code_2},
        {T_FLOAT, code_2},
        {T_INT, code_2},
        {T_BOOL, code_2},
        {T_UNTYPE, code_2}
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
        
        {IDENTIFIER, statement_10},
        {KW_TRUE, statement_10},
        {KW_FALSE, statement_10},
        {KW_CHAR, statement_10},
        {KW_FLOAT, statement_10},
        {KW_INT, statement_10},
        {KW_UNTYPED, statement_10},
        {LPAREN, statement_10},

        {T_CHAR, statement_11},
        {T_FLOAT, statement_11},
        {T_INT, statement_11},
        {T_BOOL, statement_11},
        {T_UNTYPE, statement_11}
    };
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
        {GOTO, elseBlock_},
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
        {KW_ELSE, elseBlock_1}
    };
    tabela.insert({NT_elseBLOCK, elseBlock_rule});

    std::vector<int> switchcase_ = {EMPTY};
    std::vector<int> switchcase_1 = {KW_CASE, INT, NT_BLOCK};
    std::unordered_map<int, std::vector<int>> switchcase_rule = {
        {KW_DEFAULT, switchcase_},
        {KW_CASE, switchcase_1}
    };
    tabela.insert({NT_SWITCHCASES, switchcase_rule});

    std::vector<int> declarationblock_ = {NT_TYPE, NT_DECLARATION, NT_RESTDECLARATION};
    std::unordered_map<int, std::vector<int>> declarationblock_rule = {
        {T_BOOL, declarationblock_},
        {T_UNTYPE, declarationblock_},
        {T_CHAR, declarationblock_},
        {T_FLOAT, declarationblock_},
        {T_INT, declarationblock_}
    };
    tabela.insert({NT_DECLARATIONBLOCK, declarationblock_rule});

    std::vector<int> restdeclaration_ = {EMPTY};
    std::vector<int> restdeclaration_1 = {COLON, NT_DECLARATION, NT_RESTDECLARATION};
    std::unordered_map<int, std::vector<int>> restdeclaration_rule = {
        {EOI, restdeclaration_},
        {COLON, restdeclaration_1}
    };
    tabela.insert({NT_RESTDECLARATION, restdeclaration_rule});

    std::vector<int> declaration_ = {NT_REFERENCE, IDENTIFIER, NT_INDEXBLOCK, NT_INITIALIZER};
    std::unordered_map<int, std::vector<int>> declaration_rule = {
        {SEMICOLON, declaration_},
        {COLON, declaration_},
        {OP_MULTIPLY, declaration_}
    };
    tabela.insert({NT_DECLARATION, declaration_rule});

    std::vector<int> indexblock_ = {EMPTY};
    std::vector<int> indexblock_1 = {LBRACKET, KW_INT, RBRACKET, NT_INDEXBLOCK};
    std::unordered_map<int, std::vector<int>> indexblock_rule = {
        {SEMICOLON, indexblock_},
        {COLON, indexblock_},
        {OP_EQUAL, indexblock_},
        {LBRACKET, indexblock_1}
    };
    tabela.insert({NT_INDEXBLOCK, indexblock_rule});

    std::vector<int> initializer_ = {EMPTY};
    std::vector<int> initializer_1 = {OP_EQUAL, NT_EXPRESSION};
    std::unordered_map<int, std::vector<int>> initializer_rule = {
        {SEMICOLON, initializer_},
        {COLON, initializer_},
        {OP_EQUAL, initializer_1}
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
        {LPAREN, expression_}
    };
    tabela.insert({NT_EXPRESSION, expression_rule});

    std::vector<int> restexpression_ = {EMPTY};
    std::vector<int> restexpression_ = {OP_EQUAL, NT_LOGICALOR, NT_RESTEXPRESSION};
    std::unordered_map<int, std::vector<int>> restexpression_rule = {
        {}
    };
    tabela.insert({NT_RESTEXPRESSION, restexpression_rule});

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