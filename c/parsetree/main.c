#include "parser.h"
#include "parsetree.h"

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

    print_parse_tree(pi->tree_head, 0);
}

void main(int argc, char **argv) {
    parser(argv);
}
