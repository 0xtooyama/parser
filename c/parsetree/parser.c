#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "marker.h"
#include "pack.h"
#include "parsetree.h"

#include <stdio.h>
#include <stdlib.h>

ParserInfo * init_parser(char *input) {
    ParserInfo *pi = (ParserInfo *)calloc(1, sizeof (ParserInfo));
    pi->input_ptr = input;
    pi->p = 0;
    pi->marker = init_marker();
    pi->list_pack = NULL;
    pi->tree_head = NULL;
    pi->tree_current = NULL;

    pi->head = NULL;
    Token token = next_token(&(pi->input_ptr));
    add_token(&(pi->head), token);

    return pi;
}

void print_parser_info(ParserInfo *pi) {
    printf("input_ptr : %s\n", pi->input_ptr);
    printf("p         : %d\n", pi->p);
}

int stat(ParserInfo *pi) {
    RuleNode *rule = gen_rule_node("stat");
    pi->tree_head = add_child(pi->tree_head, RULE, rule);
    pi->tree_current = pi->tree_head;

    int rc;
    if (is_list(pi)) {
        rc = list(pi);
        if (!rc) return rc;
        pi->tree_current = pi->tree_head;
        match(END, pi);
        rc = 1;
    } else if (is_assign(pi)) {
        rc = assign(pi);
        pi->tree_current = pi->tree_head;
        if (!rc) return rc;
        match(END, pi);
        rc = 2;
    } else {
        return 0;
    }
    return rc;
}

static int is_list(ParserInfo *pi) {
    mark(pi);
    int rc = list(pi);
    if (!rc) goto end;
    rc = match(END, pi);
end:
    release(pi);
    return rc;
}

static int is_assign(ParserInfo *pi) {
    mark(pi);
    int rc;
    rc = assign(pi);
    if (!rc) goto end;
    rc = match(END, pi);
end:
    release(pi);
    return rc;
}

static void mark(ParserInfo *pi) {
    push(pi->marker, pi->p);
}

static void release(ParserInfo *pi) {
    pi->p = pop(pi->marker);
}

static int assign(ParserInfo *pi) {
    ParseTree *current_save;
    if (!is_backtrack(pi)) {
        RuleNode *rule = gen_rule_node("assign"); 
        pi->tree_current = add_child(pi->tree_current, RULE, rule);
        current_save = pi->tree_current;
    }

    int rc;
    rc = list(pi);
    if (!is_backtrack(pi)) pi->tree_current = current_save;
    if (!rc) return 0;
    rc = match(EQUALS, pi);
    if (!is_backtrack(pi)) pi->tree_current = current_save;
    if (!rc) return 0;
    rc = list(pi);
    return rc;
}

static int list(ParserInfo *pi) {
    ParseTree *current_save;
    if (!is_backtrack(pi)) {
        RuleNode *rule = gen_rule_node("list"); 
        pi->tree_current = add_child(pi->tree_current, RULE, rule);
        current_save = pi->tree_current;
    }

    int list_pack_memo = pi->p;
    if (is_backtrack(pi) && get_value(pi->list_pack, pi->p) != -1) {
        pi->p = get_value(pi->list_pack, pi->p);
        return 1;
    }
    int rc;
    rc = match(LBRACK, pi); 
    if (!rc) return 0;
    if (!is_backtrack(pi)) pi->tree_current = current_save;
    rc = elements(pi); 
    if (!rc) return 0;
    if (!is_backtrack(pi)) pi->tree_current = current_save;
    rc = match(RBRACK, pi);
    if (rc && is_backtrack(pi)) {
        add_pack(&(pi->list_pack), list_pack_memo, pi->p);
    }
    return rc;
}

static int elements(ParserInfo *pi) {
    ParseTree *current_save;
    if (!is_backtrack(pi)) {
        RuleNode *rule = gen_rule_node("elements"); 
        pi->tree_current = add_child(pi->tree_current, RULE, rule);
        current_save = pi->tree_current;
    }

    int rc;
    rc = element(pi);
    if (!rc) return rc;
    if (!is_backtrack(pi)) pi->tree_current = current_save;
    while (gettype(1, pi) == COMMA) {
        rc = match(COMMA, pi);
        if (!rc) return rc;
        if (!is_backtrack(pi)) pi->tree_current = current_save;
        rc = element(pi);
    }
    return rc;
}

static int element(ParserInfo *pi) {
    ParseTree *current_save;
    if (!is_backtrack(pi)) {
        RuleNode *rule = gen_rule_node("element"); 
        pi->tree_current = add_child(pi->tree_current, RULE, rule);
        current_save = pi->tree_current;
    }

    int rc;
    if (gettype(1, pi) == NAME && gettype(2, pi) == EQUALS) {
        rc = match(NAME, pi);
        if (!rc) return 0;
        if (!is_backtrack(pi)) pi->tree_current = current_save;
        rc = match(EQUALS, pi);
        if (!rc) return 0;
        if (!is_backtrack(pi)) pi->tree_current = current_save;
        rc = match(NAME, pi);
    } else if (gettype(1, pi) == NAME) {
        rc = match(NAME, pi);
    } else if (gettype(1, pi) == LBRACK) {
        rc = list(pi);
    } else {
        rc = 0;
    }
    return rc;
}

static int match(int type, ParserInfo *pi) {
    if (type == gettype(1, pi)) {
        if (!is_backtrack(pi)) {
            TokenNode *token_node = gen_token_node(get_token(pi->head, pi->p));
            pi->tree_current = add_child(pi->tree_current, TOKEN, token_node);
        }

        // next token
        (pi->p)++;
        if (pi->p == token_size(pi->head) && !is_backtrack(pi)) {
            pi->p = 0;
            clear_token(pi->head);
            clear_pack(pi->list_pack);
        }
        sync(1, pi);
        return 1;
    } else {
        return 0;
    }
}

static int is_backtrack(ParserInfo *pi) {
    if (pi->marker->p > 0) {
        return 1;
    } else {
        return 0;
    }
}

static void sync(int n, ParserInfo *pi) {
//printf("token_size : %d\n", token_size(pi->head));
    if (pi->p + n - 1 > token_size(pi->head) - 1) {
        n = (pi->p + n - 1) - (token_size(pi->head) - 1);
        for (int i = 0; i < n; i++) {
            Token t = next_token(&(pi->input_ptr));
            add_token(&(pi->head), t);
        }
    }
}

static int gettype(int n, ParserInfo *pi) {
    sync(n, pi);
    Token *token = get_token(pi->head, pi->p + n - 1);
    return token->type;
}
