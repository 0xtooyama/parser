#ifndef AST_H
#define AST_H

#include "token.h"

typedef struct Ast {
    Token token;
    int n_child;
    struct Ast **children;
} Ast;

Ast * add_ast_child(Ast *, Token);
void print_ast_tree(Ast *, int);

#endif
