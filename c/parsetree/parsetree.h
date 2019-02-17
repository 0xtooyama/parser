#ifndef PARSETREE_H
#define PARSETREE_H

#include "token.h"

#define RULE  1
#define TOKEN 2

typedef struct ParseTree {
    int node_type;
    void *node;
    int n_child;
    struct ParseTree **children;
} ParseTree;

typedef struct {
    char *rule;
} RuleNode;

typedef struct {
    Token *token;
} TokenNode;

ParseTree * add_child(ParseTree *, int, void *);
RuleNode * gen_rule_node(char *);
TokenNode * gen_token_node(Token *);
void print_parse_tree(ParseTree *, int);

#endif
