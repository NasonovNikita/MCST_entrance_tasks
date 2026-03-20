//
// Created by nosokvkokose on 20.03.26.
//

#include "arg_list.h"

#include <stdlib.h>

void add_arg(ArgList* list, ArgParam* arg) {
    if (list->size == list->capacity) {
        list->capacity = (list->capacity == 0) ? 1 : list->capacity * 2;
        list->items = realloc(list->items, list->capacity * sizeof(ArgParam));
    }
    list->items[list->size++] = *arg;
}

void free_arg_list(ArgList* list) {
    free(list->items);
}
