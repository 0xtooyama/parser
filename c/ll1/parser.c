#include "parser.h"
#include "lexer.h"
#include <stdlib.h>

int parse_list(char **str, Token *token) {
    int rc;
    rc = match(LBRACK, str, token); 
    if (!rc) return 0;
    rc = elements(str, token); 
    if (!rc) return 0;
    rc = match(RBRACK, str, token);
    return rc;
}

static int elements(char **str, Token *token) {
    int rc;
    rc = element(str, token);
    if (token->type == COMMA) {
        match(COMMA, str, token);
        rc = element(str, token);
    }
    return rc;
}

static int element(char **str, Token *token) {
    int rc;
    if (token->type == NAME) {
        rc = match(NAME, str, token);
    } else if (token->type == LBRACK) {
        rc = parse_list(str, token);
    } else {
        rc = 0;
        //puts("error1");
        //exit(1);
    }
    return rc;
}

static int match(int type, char **str, Token *token) {
    if (type == token->type) {
        *token = next_token(str);
        return 1;
    } else {
        return 0;
        //puts("error2");
        //exit(1);
    }
}
