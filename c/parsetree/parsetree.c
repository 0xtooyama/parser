#include "parsetree.h"
#include "token.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ParseTree * add_child(ParseTree *node, int node_type, void *child) {
    ParseTree *new_node = (ParseTree *)calloc(1, sizeof (ParseTree));
    new_node->node_type = node_type;
    new_node->node = child;
    new_node->n_child = 0;
    if (node == NULL) {
        node = new_node;
        return node;
    } else {
        (node->n_child)++;
        node->children = (ParseTree **)realloc(node->children, sizeof (ParseTree *) * node->n_child);
        (node->children)[node->n_child - 1] = new_node;
        return new_node;
    }
}

RuleNode * gen_rule_node(char *rule) {
    RuleNode *rule_node = (RuleNode *)calloc(1, sizeof (RuleNode));
    rule_node->rule = (char *)calloc(strlen(rule) + 1, sizeof (char));
    strcpy(rule_node->rule, rule);
    return rule_node;
}

TokenNode * gen_token_node(Token *token) {
    TokenNode *token_node = (TokenNode *)calloc(1, sizeof (TokenNode));
    token_node->token = token;
    return token_node;
}

void print_parse_tree(ParseTree *pt, int depth) {
    printf("depth : %d\n", depth);
    if (pt->node_type == RULE) {
        RuleNode *rule = (RuleNode *)pt->node;
        printf("\tnode_type : RULE\n");
        printf("\trule : %s\n", rule->rule);
    } else {
        TokenNode *token = (TokenNode *)pt->node;
        printf("\tnode_type : TOKEN\n");
        print_token(token->token);
    }

    int n_child = pt->n_child;
    for (int i = 0; i < n_child; i++) {
        print_parse_tree((pt->children)[i], depth + 1);
    }
}
