#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "marker.h"

typedef struct {
    char *input_ptr;
    Token *head;
    int p;
    Marker *marker;
} ParserInfo;

ParserInfo * init_parser(char **, int);
int parse_list(char **, ParserInfo *);
static int elements(char **, ParserInfo *);
static int element(char **, ParserInfo *);
static int match(int , char **, ParserInfo *);
static int gettype(int, ParserInfo *);

#endif
