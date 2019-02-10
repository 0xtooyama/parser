#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

Token generate_token(int type, char *text) {
    Token token;
    token.type = type;
    int len = strlen(text);
    token.text = (char *)calloc(len + 1, sizeof (char));
    strncpy(token.text, text, len);
    token.text[len] = '\0';
    return token;
}

void print_token(Token token) {
    printf("<'%s',%s>\n", token.text, token_names[token.type]);
}

static int is_char(char c) {
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}

static Token proc_char(char **str) {
    int i = 0;
    while (is_char((*str)[i])) i++;
    char *tmp = (char*)calloc(i + 1, sizeof (char));
    strncpy(tmp, *str, i);
    tmp[i] = '\0';
    Token token =  generate_token(NAME, tmp);
    free(tmp);
    *str = *str + i;
    return token;
}

static void ignore(char **str) {
    while(**str == ' ') {
        (*str)++;
    }
}

Token next_token(char **str) {
    while (**str) {
        switch (*str[0]) {
            case ' ' :
                ignore(str);
                continue;

            case '[' :
                (*str)++;
                return generate_token(LBRACK, "[\0"); 

            case ']' :
                (*str)++;
                return generate_token(RBRACK, "]\0"); 

            case ',' :
                (*str)++;
                return generate_token(COMMA, ",\0"); 

            case '=' :
                (*str)++;
                return generate_token(EQUALS, "=\0");

            default :
                if (is_char(*str[0])) {
                    return proc_char(str);
                } else {
                    printf("error\n");
                    exit(1);
                }
        }
    }
    return generate_token(END, "<END>\0");
}
