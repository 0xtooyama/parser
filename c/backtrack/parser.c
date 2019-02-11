#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "marker"

#include <stdlib.h>

ParserInfo * init_parser(char *input) {
    ParserInfo *pi = (ParserInfo *)calloc(1, sizeof (ParserInfo));
    pi->input_ptr = input;
    pi->p = 0;
    pi->marker = init_marker();

    pi->head = NULL;
    Token token = next_token(&(pi->input_ptr));
    add_token(pi->head, token);

    return pi;
}

int stat(ParserInfo *pi) {
    if (is_list(pi)) {
        list(pi);
        match(END, pi);
    } else if (is_asign(pi)) {
        assign(pi);
        match(END, pi);
    } else {
        return 0;
    }
}

int is_list(ParserInfo *pi) {
    mark(pi);
    int rc = list(pi);
    if (!rc) goto end;
    rc = match(END, pi);
    if (!rc) goto end;
    return 1;
end:
    release(pi);
    return 0;
}

int is_assign(ParserInfo *pi) {
    mark(pi);
    int rc = assign(pi);
    if (!rc) goto end;
    rc = match(END, pi);
    if (!rc) goto end;
    return 1;
end:
    release(pi);
    return 0;
}

void mark(ParserInfo *pi) {
    push(pi->marker, pi->p);
}

void release(ParserInfo *pi) {
    pi->p = pop(pi->marker);
}

static int list(ParserInfo *pi) {
    int rc;
    rc = match(LBRACK, pi); 
    if (!rc) return 0;
    rc = elements(str, pi); 
    if (!rc) return 0;
    rc = match(RBRACK, pi);
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
        rc = list(str, pi);
    } else {
        rc = 0;
        //puts("error1");
        //exit(1);
    }
    return rc;
}

static int match(int type, ParserInfo *pi) {
    if (type == get_type(1, pi)) {
        // next token
        (pi->p)++;
        // if (not backtrack) p reset && head reset
        if (
        Token token = next_token(&(pi->input_ptr));
        add_token(pi->head, token);
    }

    Token *token = pi->token;
    int p = pi->p;

    if (type == token[p].type) {
        token[p] = next_token(str);
        pi->p = ++p % pi->k;
        return 1;
    } else {
        return 0;
    }
}

static int gettype(int n, ParserInfo *pi) {
    Token *token = pi->token;
    int p = pi->p;
    return token[(p + n - 1) % pi->k].type;
}
