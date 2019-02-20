#ifndef AST_H
#define AST_H

#include "token.h"

static int INVALID = 0;
static int INTEGER = 1;
static int VECTOR  = 2;

static char expr_names[][10] = {"INVALID", "INTEGER", "VECTOR"};

typedef struct Ast {
    Token token;
    int expr_type;
    int n_child;
    struct Ast **children;
} Ast;

Ast * ast_add_child(Ast *, Ast *);
Ast * ast_add_node(Ast *, Ast*, Token, Ast *);
Ast * ast_int_node(Token);
Ast * ast_vector_node(Ast *, Ast *, int);
void ast_print_tree(Ast *, int);

#endif
