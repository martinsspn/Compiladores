#include "lex.yy.h"
#include "parser_table.h"
#include <stdio.h>
#include <vector>

int main() {
    printf("%d", tokenTable[pair(KW_BOOL,KW_BOOL)][0]);
}