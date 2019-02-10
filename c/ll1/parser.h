#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

int parse_list(char **, Token *);
static int elements(char **, Token *);
static int element(char **, Token *);
static int match(int , char **, Token *);

#endif
