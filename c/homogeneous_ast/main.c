#include "ast.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    Token plus = generate_token(PLUS, "+");
    Token one = generate_token(INT, "1");
    Token two = generate_token(INT, "2");

    Ast *root = NULL;
    root = add_ast_child(root, plus);
    add_ast_child(root, one);
    add_ast_child(root, two);
    print_ast_tree(root, 0);

    puts("");

    Token imaginary_token = generate_token(0, "");

    Ast *list = NULL;
    list = add_ast_child(list, imaginary_token);
    add_ast_child(list, one);
    add_ast_child(list, two);
    print_ast_tree(list, 0);
}
