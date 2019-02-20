#include "token.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Token generate_token(int type, char *text) {
    Token token;
    token.used = 1;
    token.type = type;
    int len = strlen(text);
    token.text = (char *)calloc(len + 1, sizeof (char));
    strncpy(token.text, text, len);
    token.text[len] = '\0';
    return token;
}

void add_token(Token **head, Token newtoken) {
    Token *iterator = *head;
    while (iterator) {
        if (!iterator->used) {
            iterator->used = 1;
            iterator->type = newtoken.type;
            iterator->text = newtoken.text;
            return;
        }
        iterator = iterator->next;
    }

    Token *token = (Token *)calloc(1, sizeof (Token));
    token->used = 1;
    token->type = newtoken.type;
    token->text = newtoken.text;
    token->next = NULL;

    if (*head == NULL) {
        *head = token;
    } else {
        iterator = *head;
        while (iterator->next) {
            iterator = iterator->next;
        }
        iterator->next = token;
    }
}

// n is 0...
Token * get_token(Token *head, int n) {
    if (head == NULL) return NULL;
    if (n > token_size(head) - 1) return NULL;

    Token *token = head;
    for (int i = 0; i < n; i++) {
        token = token->next;
    }
    return token;
}

int remove_token(Token *head, int n) {
    if (head == NULL) return 0;
    if (n > token_size(head) -1) return 0;
    if (n == 0) {
        free(head->text);
        free(head);
        return 0;
    }

    Token *pre = get_token(head, n - 1);
    Token *delete = get_token(head, n);

    pre->next = delete->next;
    free(delete->text);
    free(delete);
}

int clear_token(Token *head) {
    if (head == NULL) return 0;

    Token *iterator = head;
    do {
        iterator->used = 0;
        iterator->type = 0;
        free(iterator->text);
        iterator->text = NULL;
        iterator = iterator->next;
    } while (iterator);

    return 1;
}

int token_size(Token *head) {
    Token *iterator = head;
    int i = 0;
    while (iterator && iterator->used) {
        i++;
        iterator = iterator->next;
    }
    return i;
}

void print_token(Token *token) {
    if (token == NULL) return;
    printf("token->used : %d\n", token->used);
    printf("token->text : %s\n", token->text);
    printf("token->type : %s\n", token_names[token->type]);
}

