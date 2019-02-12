#ifndef TOKEN_H
#define TOKEN_H

static int END    = 1;
static int BRANK  = 2;
static int LBRACK = 3;
static int RBRACK = 4;
static int COMMA  = 5;
static int NAME   = 6;
static int EQUALS = 7;

static char token_names[][10] = {"n/a", "END", "BRANK", "LBRACK", "RBRACK", "COMMA", "NAME", "EQUALS"};

typedef struct Token {
    char used; // 0 not used. 1 used.
    int type;
    char *text;
    struct Token *next;
} Token;

Token generate_token(int, char *);
void add_token(Token **, Token);
Token * get_token(Token *, int);
int remove_token(Token *, int);
int clear_token(Token *);
int token_size(Token *);
void print_token(Token *);

#endif
