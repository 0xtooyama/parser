#include "lexer.h"

void main(int argc, char **argv) {
    char *str = argv[1];
    Token t = next_token(&str);
    print_token(t);
    while (t.type != END) {
        t = next_token(&str);
        print_token(t);
    }
}
