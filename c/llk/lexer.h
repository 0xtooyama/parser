#ifndef LEXER_H
#define LEXER_H

static int END    = 1;
static int BRANK  = 2;
static int LBRACK = 3;
static int RBRACK = 4;
static int COMMA  = 5;
static int NAME   = 6;
static int EQUALS = 7;

static char token_names[][10] = {"n/a", "END", "BRANK", "LBRACK", "RBRACK", "COMMA", "NAME", "EQUALS"};

typedef struct {
    int type;
    char *text;
} Token;

Token next_token(char **);
void print_token(Token);

#endif
