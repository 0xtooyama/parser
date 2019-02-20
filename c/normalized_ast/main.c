#include "ast.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    Token plus = generate_token(PLUS, "+");
    Token one = generate_token(INT, "1");
    Token two = generate_token(INT, "2");

    Ast *add_root = NULL;
    add_root = ast_add_node(add_root, ast_int_node(one), plus, ast_int_node(two));
    ast_print_tree(add_root, 0);

    puts("");

    int size = 4;
    Ast vector[size];
    Token vec;
    char buf[4];
    for (int i = 0; i < size; i++) {
        sprintf(buf, "%d", (i + 1) * 100);
        vec = generate_token(INT, buf);
        vector[i] = *(ast_int_node(vec));
    }

    Ast *vec_root = NULL;
    vec_root = ast_vector_node(vec_root, vector, size);
    ast_print_tree(vec_root, 0);

    puts("");

    add_root = ast_add_node(NULL, add_root, plus, vec_root);
    ast_print_tree(add_root, 0);
}
