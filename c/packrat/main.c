#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

void parser(char **argv) {
    char *str = argv[1];
    ParserInfo *pi = init_parser(str);
    int rc = stat(pi);
    if (rc == 1) printf("list\n");
    else if (rc == 2) printf("assign\n");
    else printf("not sentence\n");
    free(pi);
}

void main(int argc, char **argv) {
    parser(argv);
}
