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

ParserInfo * init_parser(char *);
void print_parser_info(ParserInfo *);
int stat(ParserInfo *);
static int is_list(ParserInfo *);
static int is_assign(ParserInfo *);
static void mark(ParserInfo *);
static void release(ParserInfo *);
static int assign(ParserInfo *);
static int list(ParserInfo *);
static int elements(ParserInfo *);
static int element(ParserInfo *);
static int match(int , ParserInfo *);
static int is_backtrack(ParserInfo *);
static void sync(int, ParserInfo *);
static int gettype(int, ParserInfo *);

#endif
