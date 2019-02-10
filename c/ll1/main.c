#include "lexer.h"
#include "parser.h"

void parser(char **argv) {
    char *str = argv[1];
    Token t = next_token(&str);
    int rc = parse_list(&str, &t);
    if (rc) puts("list");
    else puts("not list");
}

void lexer(char **argv) {
    char *str = argv[1];
    Token t = next_token(&str);
    print_token(t);
    while (t.type != END) {
        t = next_token(&str);
        print_token(t);
    }
}

void main(int argc, char **argv) {
    //lexer(argv);
    parser(argv);
}
