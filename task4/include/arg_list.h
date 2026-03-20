//
// Created by nosokvkokose on 20.03.26.
//

#ifndef ARG_LIST_H
#define ARG_LIST_H

#define MAX_LONG_OPTION_LEN 16

typedef struct {
    char token[MAX_LONG_OPTION_LEN];
    char* value;
} ArgParam;

typedef struct {
    ArgParam* items;
    int size;
    int capacity;
} ArgList;

void add_arg(ArgList* list, ArgParam* arg);

void free_arg_list(ArgList* list);

#endif //ARG_LIST_H
