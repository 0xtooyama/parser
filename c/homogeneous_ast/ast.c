#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

Ast * add_ast_child(Ast *ast, Token token) {
    Ast *new_ast = (Ast *)calloc(1, sizeof (Ast));
    new_ast->token = token;
    new_ast->n_child = 0;
    new_ast->children = NULL;

    if (ast == NULL) {
        return new_ast;
    }

    (ast->n_child)++;
    ast->children = (Ast **)realloc(ast->children, sizeof (Ast *) * ast->n_child);
    (ast->children)[ast->n_child - 1] = new_ast;
    return new_ast;
}

void print_ast_tree(Ast *ast, int depth) {
    if (ast == NULL) return;
    printf("depth: %d\n", depth);
    print_token(&(ast->token));
    for (int i = 0; i < ast->n_child; i++) {
        print_ast_tree((ast->children)[i], depth + 1);
    }
}
