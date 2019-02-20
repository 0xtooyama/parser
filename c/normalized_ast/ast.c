#include "ast.h"
#include "token.h"

#include <stdlib.h>
#include <stdio.h>

Ast * ast_add_child(Ast *ast, Ast *child) {
    if (ast == NULL) {
        return child;
    }

    (ast->n_child)++;
    ast->children = (Ast **)realloc(ast->children, sizeof (Ast *) * ast->n_child);
    (ast->children)[ast->n_child - 1] = child;
    return child;
}

Ast * ast_add_node(Ast *ast, Ast *left, Token token, Ast *right) {
    Ast *add_ast = (Ast *)calloc(1, sizeof (Ast));
    add_ast->token = token;
    add_ast->expr_type = INVALID;
    add_ast->n_child = 0;
    add_ast->children = NULL;

    Ast *sub_root = ast_add_child(ast, add_ast);
    ast_add_child(sub_root, left);
    ast_add_child(sub_root, right);
    return sub_root;
}

Ast * ast_int_node(Token token) {
    Ast *int_node = (Ast *)calloc(1, sizeof (Ast));
    int_node->token = token;
    int_node->expr_type = INTEGER;
    int_node->n_child = 0;
    int_node->children = NULL;
    return int_node;
}

Ast * ast_vector_node(Ast *ast, Ast *elements, int size) {
    Ast *vector_node = (Ast *)calloc(1, sizeof (Ast));
    vector_node->token = generate_token(0, "");
    vector_node->expr_type = VECTOR;
    vector_node->n_child = size;
    vector_node->children = NULL;

    Ast *sub_root = ast_add_child(ast, vector_node);
    for (int i = 0; i < size; i++) {
        ast_add_child(sub_root, elements + i);
    }

    return sub_root;
}

void ast_print_tree(Ast *ast, int depth) {
    if (ast == NULL) return;
    printf("depth: %d\n", depth);
    printf("expr_type: %s\n", expr_names[ast->expr_type]);
    print_token(&(ast->token));
    for (int i = 0; i < ast->n_child; i++) {
        ast_print_tree((ast->children)[i], depth + 1);
    }
}
