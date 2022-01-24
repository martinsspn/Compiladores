#include <vector>
#include <unordered_map>
#include <utility>
#include "lex.yy.h"

using namespace std;

/*  taken from: https://stackoverflow.com/a/32685618
 *
 *  Only for pairs of std::hash-able types for simplicity.
 *  You can of course template this struct to allow other hash functions
 */
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

typedef unordered_map<pair<int,int>, vector<int>, pair_hash> token_table;
typedef vector<int> token_list; 

/*
 * token table
 */
token_table tokenTable
{
    {pair(KW_BOOL,KW_BOOL),     {KW_IF, KW_BREAK}}
};