#include "lex.yy.h"
enum token {IF, ELSE, BEGIN, END, NUM, EQ};
extern enum token getToken(void);

enum token tok;
void advance(){ tok = getToken(); }
void eat(enum token t) { if (tok == t) advance(); else error();}

void MODULE(void){
    if(token == MODULE){
        
    }
}

void STATEMENT(void) {
    switch(tok){
        case IF:
            eat(KW_IF);
            eat(LPAREN);
            EXPRESSION();
            eat(RPAREN);
            BLOCK();
            elseBLOCK();
            break;
    }
}