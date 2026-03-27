//
// Created by nosokvkokose on 26.03.26.
//

#ifndef PARSER_H
#define PARSER_H

#define VARIABLES_COUNT 26

typedef enum {
    AND,
    OR,
    NOT,
    VAL
} node_type;

typedef struct node_t node_t;

struct node_t {
    node_t *left;
    node_t *right;
    node_type type;
    char* val;
};

// Parses a logical expression with AND, OR, NOT, brackets, and variables A-Z
node_t parse(const char* expression);

bool evaluate(node_t *tree, bool values[static VARIABLES_COUNT]);

void free_tree(node_t *tree);

#endif //PARSER_H
