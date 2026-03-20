//
// Created by nosokvkokose on 20.03.26.
//

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_list.h"


constexpr char SHORT_OPTIONS[] = ":mcst";

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

static ArgList short_options_list = {NULL, 0, 0};
static ArgList long_options_list = {NULL, 0, 0};
static ArgList non_options_list = {NULL, 0, 0};

void parse_arg(const int c, char* argv[]) {
    switch (c) {
        case 'e': {
            if (!is_elbrus_arg(optarg)) {
                fprintf(stderr, "Incorrect argument for option: '%s'\n", optarg);
                exit(1);
            }

            ArgParam arg = {0};
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
            exit(1);
        case ':':
            fprintf(stderr, "Missing argument for option: '%s'\n", argv[optind - 1]);
            exit(1);
        default:  // Regular short options
            ArgParam arg = {0};
            arg.token[0] = c;
            arg.token[1] = '\0';
            arg.value = NULL;
            add_arg(&short_options_list, &arg);
            break;
    }
}

void print_options() {
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
}

int main(const int argc, char *argv[]) {
    int c;

    opterr = 0;  // Ensure we print own errors
    while ((c = getopt_long(argc, argv, SHORT_OPTIONS, long_options, NULL)) != -1) {
        parse_arg(c, argv);
    }  // Parse options

    // Parse non-options
    while (optind < argc) {
        ArgParam arg = {0};
        arg.value = argv[optind++];
        add_arg(&non_options_list, &arg);
    }

    // Prints
    print_options();

    // Free memory

    free_arg_list(&short_options_list);
    free_arg_list(&long_options_list);
    free_arg_list(&non_options_list);

    return 0;
}
