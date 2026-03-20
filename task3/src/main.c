//
// Created by nosokvkokose on 12.03.26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators.h"

// Saves array from file to arr, returns size of array
int scan_arr(char*** arr_ptr, FILE* file) {
    int capacity = 1;
    int count = 0;
    *arr_ptr = malloc(capacity * sizeof(char*));

    char* string;
    while (fscanf(file, "%ms", &string) == 1) {  // %ms auto mallocs
        if (count >= capacity) {
            capacity *= 2;
            *arr_ptr = realloc(*arr_ptr, capacity * sizeof(char*));
        }
        (*arr_ptr)[count] = string;
        count++;

#ifdef DEBUG
        printf("Filling arr: count %d, capacity %d, elem %s\n", count, capacity, string);
#endif
    }

    if (count < capacity) {
        *arr_ptr = realloc(*arr_ptr, count * sizeof(char*));
    }

    return count;
}

#ifdef DEBUG
void print_arr(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}
#endif


int main(const int argc, char* argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s <input file> <output file> <sort type>\n"
                "Sort types:\nplain - byte comparison\n"
                "lex - lexicographical comparison\n"
                "rplain - reverse byte comparison\n"
                "rlex - reverse lexicographical comparison\n",
                argv[0]);

            return 0;
        }
    }

    if (argc != 4) {
        printf("Usage: %s <input file> <output file> <sort type>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        return 1;
    }
    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", argv[2]);
        fclose(input);
        return 1;
    }

    char** arr_ptr = NULL;
    int size = scan_arr(&arr_ptr, input);
#ifdef DEBUG
    print_arr(arr_ptr, size);
#endif

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
        free(arr_ptr);
        return 1;
    }

#ifdef DEBUG
    printf("Sorting array\n");
#endif

    qsort(arr_ptr, size, sizeof(char*), compare_func);

#ifdef DEBUG
    printf("Saving array\n");
    print_arr(arr_ptr, size);
#endif

    for (int i = 0; i < size; i++) {
        fprintf(output, "%s\n", arr_ptr[i]);
    }

    fclose(input);
    for (int i = 0; i < size; i++) {
        free(arr_ptr[i]);
    }
    free(arr_ptr);

    return 0;
}
