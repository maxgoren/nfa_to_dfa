#ifndef ast_hpp
#define ast_hpp
#include "token.hpp"

enum NodeType {
    CCL_EXPR, CONCAT_EXPR, CONST_EXPR, KLEENE_EXPR, OPT_EXPR, OR_EXPR, RANGE_EXPR 
};

struct astnode {
    NodeType type;
    Token token;
    astnode* children[3];
    astnode* next;
    astnode(Token t) : token(t) { for (int i = 0; i < 3; i++) children[i] = nullptr; next = nullptr; }
};

void preorder(astnode* ast, int n);

#endif