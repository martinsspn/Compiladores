#ifndef TREE
#define TREE

#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

/**
 * Como abordagem vamos definir que os tipos serão representados por inteiors
 * 1 - int
 * 2 - float
 * 3 - char
 */

typedef struct TreeScope{
    char* name;
    struct TreeScope *firstChildScope;
    struct TreeScope *nextSiblingScope;
    struct Symbol *symbols;
} TreeScope;

typedef struct Symbol{
    char* name;
    int paramFunc;
    int isOperand;
    int type;
    struct Symbol *nextSymbol;
} Symbol;


#endif