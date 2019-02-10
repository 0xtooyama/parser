#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
    Token *token;
    int k;
    int p;
} ParserInfo;

ParserInfo * init_parser(char **, int);
int parse_list(char **, ParserInfo *);
static int elements(char **, ParserInfo *);
static int element(char **, ParserInfo *);
static int match(int , char **, ParserInfo *);
static int gettype(int, ParserInfo *);

#endif
