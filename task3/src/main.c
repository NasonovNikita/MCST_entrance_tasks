//
// Created by nosokvkokose on 12.03.26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators.h"

// Saves array from file to arr, returns size of array
int scan_arr(char*** arr_ptr, FILE* file);  // TODO

#ifdef DEBUG
void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
#endif


int main(const int argc, char* argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s <input file> <output file> <sort type>\n", argv[0]);
            printf("Sort types:\n");
            printf("plain - byte comparison\n");
            printf("lex - lexicographical comparison\n");
            printf("rplain - reverse byte comparison\n");
            printf("rlex - reverse lexicographical comparison\n");
            return 0;
        }
    }

    if (argc != 4) {
        printf("Usage: %s <input file> <output file> <sort type>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }
    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output file\n");
        fclose(input);
        return 1;
    }

    char** arr = NULL;
    int size = scan_arr(&arr, input);

    comparator compare_func;
    if (strcmp(argv[3], "plain") == 0) {
        compare_func = compare_plain;
    } else if (strcmp(argv[3], "lex") == 0) {
        compare_func = compare_lex;
    } else if (strcmp(argv[3], "rplain") == 0) {
        compare_func = compare_rplain;
    } else if (strcmp(argv[3], "rlex") == 0) {
        compare_func = compare_rlex;
    } else {
        fprintf(stderr, "Invalid sort type\n");
        fclose(input);
        free(arr);
        return 1;
    }

    qsort(arr, size, sizeof(int), compare_func);

    for (int i = 0; i < size; i++) {
        fprintf(output, "%s\n", arr[i]);
    }

    fclose(input);
    free(arr);

    return 0;
}
