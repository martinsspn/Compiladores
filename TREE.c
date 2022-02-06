#ifndef TREE
#define TREE

#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

/**
 * Como abordagem vamos definir que os tipos serão representados por inteiors
 * 0 - int
 * 1 - float
 * 2 - char
 * 3 - bool
 * 4 - name function
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
    int type;
    struct Symbol *nextSymbol;
} Symbol;


#endif