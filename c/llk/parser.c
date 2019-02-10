#include "parser.h"
#include "lexer.h"
#include <stdlib.h>

ParserInfo * init_parser(char **str, int k) {
    ParserInfo *pi = (ParserInfo *)calloc(1, sizeof (ParserInfo));
    pi->k = k;
    pi->p = 0;

    Token *t = (Token *)calloc(k, sizeof (Token));
    for (int i = 0; i < k; i++) {
        t[i] = next_token(str);
    }
    pi->token = t;
    return pi;
}

int parse_list(char **str, ParserInfo *pi) {
    int rc;
    rc = match(LBRACK, str, pi); 
    if (!rc) return 0;
    rc = elements(str, pi); 
    if (!rc) return 0;
    rc = match(RBRACK, str, pi);
    return rc;
}

static int elements(char **str, ParserInfo *pi) {
    int rc;
    rc = element(str, pi);
    if ((pi->token)[pi->p].type == COMMA) {
        match(COMMA, str, pi);
        rc = element(str, pi);
    }
    return rc;
}

static int element(char **str, ParserInfo *pi) {
    int rc;
    if (gettype(1, pi) == NAME && gettype(2, pi) == EQUALS) {
        rc = match(NAME, str, pi);
        if (!rc) return 0;
        rc = match(EQUALS, str, pi);
        if (!rc) return 0;
        rc = match(NAME, str, pi);
    } else if ((pi->token)[pi->p].type == NAME) {
        rc = match(NAME, str, pi);
    } else if ((pi->token)[pi->p].type == LBRACK) {
        rc = parse_list(str, pi);
    } else {
        rc = 0;
        //puts("error1");
        //exit(1);
    }
    return rc;
}

static int match(int type, char **str, ParserInfo *pi) {
    Token *token = pi->token;
    int p = pi->p;

    if (type == token[p].type) {
        token[p] = next_token(str);
        pi->p = ++p % pi->k;
        return 1;
    } else {
        return 0;
        //puts("error2");
        //exit(1);
    }
}

static int gettype(int n, ParserInfo *pi) {
    Token *token = pi->token;
    int p = pi->p;
    return token[(p + n - 1) % pi->k].type;
}
