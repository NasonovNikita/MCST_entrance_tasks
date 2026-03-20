//
// Created by nosokvkokose on 20.03.26.
//

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG_OPTION_LEN 16

constexpr char SHORT_OPTIONS[] = ":mcst";

typedef struct {
    char token[MAX_LONG_OPTION_LEN];
    char* value;
} ArgParam;

typedef struct {
    ArgParam* items;
    int size;
    int capacity;
} ArgList;

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

static struct option long_options[] = {
    {"elbrus", required_argument, 0, 'e'},
    {0, 0, 0, 0}  // Conventional end
};

const char* elbrus_args[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c", NULL};

bool is_elbrus_arg(const char* arg) {
    for (size_t i = 0; elbrus_args[i] != NULL; i++) {
        if (strcmp(arg, elbrus_args[i]) == 0) {
            return true;
        }
    }

    return false;
}

int main(const int argc, char *argv[]) {
    int c;
    ArgList short_options_list = {NULL, 0, 0};
    ArgList long_options_list = {NULL, 0, 0};
    ArgList non_options_list = {NULL, 0, 0};

    opterr = 0;  // Ensure we print own errors
    while ((c = getopt_long(argc, argv, SHORT_OPTIONS, long_options, NULL)) != -1) {
        switch (c) {
            case 'e': {
                if (!is_elbrus_arg(optarg)) {
                    fprintf(stderr, "Incorrect argument for option: '%s'\n", optarg);
                    return 1;
                }

                ArgParam arg;
                strncpy(arg.token, "elbrus", MAX_LONG_OPTION_LEN - 1);
                arg.value = optarg;
                add_arg(&long_options_list, &arg);
                break;
            }
            case '?':
                if (optopt) {  // Short option
                    fprintf(stderr, "Incorrect option: '%c'\n", optopt);
                } else {  // Long option
                    fprintf(stderr, "Incorrect option: '%s'\n", argv[optind - 1]);
                }
                return 1;
            case ':':
                fprintf(stderr, "Missing argument for option: '%s'\n", argv[optind - 1]);
                return 1;
                break;
            default:  // Regular short options
                ArgParam arg;
                arg.token[0] = c;
                arg.token[1] = '\0';
                arg.value = NULL;
                add_arg(&short_options_list, &arg);
                break;
        }
    }  // Parse options

    // Parse non-options
    while (optind < argc) {
        ArgParam arg;
        arg.value = argv[optind++];
        add_arg(&non_options_list, &arg);
    }

    // Prints

    printf("Short options: ");
    for (int i = 0; i < short_options_list.size; i++) {
        printf("'%s' ", short_options_list.items[i].token);
    }
    printf("\n");

    printf("Long options: ");
    for (int i = 0; i < long_options_list.size; i++) {
        printf("'%s=%s' ", long_options_list.items[i].token, long_options_list.items[i].value);
    }
    printf("\n");

    printf("Non-options: ");
    for (int i = 0; i < non_options_list.size; i++) {
        printf("'%s' ", non_options_list.items[i].value);
    }
    printf("\n");

    // Free memory

    free_arg_list(&short_options_list);
    free_arg_list(&long_options_list);
    free_arg_list(&non_options_list);

    return 0;
}
