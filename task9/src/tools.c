//
// Created by nosokvkokose on 06.04.26.
//

#include "tools.h"

#include <stdio.h>
#include <stdlib.h>


size_t scan_arr(int **arr_ptr)  {
    size_t capacity = 1;
    size_t count = 0;
    *arr_ptr = malloc(capacity * sizeof(int));

    int num;
    while (scanf("%d", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;
            *arr_ptr = realloc(*arr_ptr, capacity * sizeof(int));
        }
        (*arr_ptr)[count] = num;
        count++;

        // Check next character
        const int next_char = getchar();
        if (next_char == '\n') {
            break;  // Stop on newline
        } else if (next_char == EOF) {
            break;  // Stop on EOF
        } else {
            ungetc(next_char, stdin);  // Put back for next scanf
        }
    }
    if (count == 0) {
        fprintf(stderr, "No numbers found in input\n");
        free(*arr_ptr);
        *arr_ptr = NULL;
        return 0;
    }

    if (count < capacity) {
        int *temp = realloc(*arr_ptr, count * sizeof(int));
        if (temp) {
            *arr_ptr = temp;
        }
    }

#ifdef DEBUG
    printf("Scanned array:\n");
    print_arr(*arr_ptr, count);
#endif

    return count;
}

void print_arr(const int *arr, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
