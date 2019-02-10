#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

void parser(char **argv) {
    char *str = argv[1];
    int k = 2;
    ParserInfo *pi = init_parser(&str, k);
    int rc = parse_list(&str, pi);
    if (rc) printf("list\n");
    else printf("not list\n");
    free(pi);
}

void main(int argc, char **argv) {
    parser(argv);
}
