#include "token.h"
#include <stdio.h>

int main() {
    Token *head = NULL;
    Token token = generate_token(2, "test");
    add_token(&head, token);
    printf("token_size() : %d\n", token_size(head));

    token = generate_token(4, "test2");
    add_token(&head, token);
    printf("token_size() : %d\n", token_size(head));

    remove_token(head, 0);
    printf("token_size() : %d\n", token_size(head));

    Token *p = get_token(head, 0);
    print_token(p);

    clear_token(head);
    printf("token_size() : %d\n", token_size(head));
}
